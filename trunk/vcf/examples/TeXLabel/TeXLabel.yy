
%{


#include <vcf/ApplicationKit/ApplicationKit.h>
#include "TeXTypes.hpp"

#define YYPARSE_PARAM markup_tree

int yylex();
void yyerror(const char *);

 
%}

%token TEXCHAR
%token FACE_MODIFIER
%token ACCENT

%union {
	VCF::VCFChar ch;
	int flag;
	Tex *markup;
}

%type<ch> TEXCHAR ACCENT
%type<flag> FACE_MODIFIER face_modifier 
%type<markup> tex tex_markup group string

%start complete_markup

%%


complete_markup
	: tex
	{
		*static_cast<Tex **>(markup_tree) = $1;
	}
	;
	
group
	: '{' face_modifier tex '}'
	{
		$$ = new Group($3, (FaceModifiers)$2);
	}
	| face_modifier group
	{
		$$ = new Group($2, (FaceModifiers)$1);
	}	
	;
string
	: TEXCHAR
	{
		$$ = new String();
		dynamic_cast<String *>($$)->value_ = $1;
	}
	| string TEXCHAR
	{
		$$ = $1;
		dynamic_cast<String *>($$)->value_ += $2;
	}
	| ACCENT '{' TEXCHAR '}'
	{
		$$ = new String();
		dynamic_cast<String *>($$)->value_ = $3;
		dynamic_cast<String *>($$)->value_ += $1;
	}
	| string ACCENT '{' TEXCHAR '}'
	{
		$$ = $1;
		dynamic_cast<String *>($$)->value_ += $4;
		dynamic_cast<String *>($$)->value_ += $2;
	}
	;

tex
	: tex_markup
	{
		$$ = $1;
	}
	| tex_markup tex
	{
		$$ = new Pair($1, $2);
	}
	|
	{
		$$ = NULL;
	}
	;
	
tex_markup
	: group
	| string
	| tex_markup '^' group
	{
		$$ = new Pair($1, new SuperScript($3));
	}
	| tex_markup '_' group
	{
		$$ = new Pair($1, new SubScript($3));
	}
	;
	
face_modifier
	: FACE_MODIFIER
	{
		$$ = $1;
	}
	| face_modifier FACE_MODIFIER
	{
		$$ = $1 | $2;
	}
	|
	{
		$$ = 0;
	}
	;
	
%%

void yyerror(const char *msg)
{
	VCF::Dialog::showMessage(VCF::String("Parse error: `") + msg + "`.");
}

void DisplayTex(VCF::Rect& bounds, VCF::GraphicsContext *ctx, Tex *markup, VCF::Font *f)
{
	markup->paint(ctx, bounds, f);
}
	
