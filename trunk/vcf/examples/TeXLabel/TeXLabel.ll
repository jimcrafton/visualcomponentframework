
%{
#include <vcf/FoundationKit/FoundationKit.h>
#include <vcf/ApplicationKit/ApplicationKit.h>

#include "TeXTypes.hpp"
#include "TeXLabel.tab.hpp"

%}


%%

"\\hat"	{
	yylval.ch = L'\x0302';
	return ACCENT;
}
"\\grave"	{
	yylval.ch = L'\x0300';
	return ACCENT;
}
"\\bar"	{
	yylval.ch = L'\x0304';
	return ACCENT;
}
"\\check"	{
	yylval.ch = L'\x030c';
	return ACCENT;
}
"\\dot"	{
	yylval.ch = L'\x0307';
	return ACCENT;
}
"\\vec"	{
	yylval.ch = L'\x20d7';
	return ACCENT;
}
"\\tilde"	{
	yylval.ch = L'\x0303';
	return ACCENT;
}
"\\ddot"	{
	yylval.ch = L'\x0308';
	return ACCENT;
}
"\\widehat"	{
	yylval.ch = L'\x0302';  // FIXME
	return ACCENT;
}
"\\acute"	{
	yylval.ch = L'\x0301';
	return ACCENT;
}
"\\breve"	{
	yylval.ch = L'\x0306';
	return ACCENT;
}
"\\widetilde"	{
	yylval.ch = L'\x0303';  // FIXME
	return ACCENT;
}

"\\alpha"  {
	yylval.ch = L'\x03b1';
	return TEXCHAR;
}
"\\beta"  {
	yylval.ch = L'\x03b2';
	return TEXCHAR;
}
"\\gamma"  {
	yylval.ch = L'\x03b3';
	return TEXCHAR;
}
"\\delta"  {
	yylval.ch = L'\x03b4';
	return TEXCHAR;
}
"\\epsilon"  {
	yylval.ch = L'\x03b5';
	return TEXCHAR;
}
"\\varepsilon"  {
	yylval.ch = L'\x025b';
	return TEXCHAR;
}
"\\zeta"  {
	yylval.ch = L'\x03b6';
	return TEXCHAR;
}
"\\eta"  {
	yylval.ch = L'\x03b7';
	return TEXCHAR;
}
"\\theta"  {
	yylval.ch = L'\x03b8';
	return TEXCHAR;
}
"\\vartheta"  {
	yylval.ch = L'\x03d1';
	return TEXCHAR;
}
"\\iota"  {
	yylval.ch = L'\x03b9';
	return TEXCHAR;
}
"\\kappa"  {
	yylval.ch = L'\x03ba';
	return TEXCHAR;
}
"\\lambda"  {
	yylval.ch = L'\x03bb';
	return TEXCHAR;
}
"\\mu"  {
	yylval.ch = L'\x03bc';
	return TEXCHAR;
}
"\\nu"  {
	yylval.ch = L'\x03bd';
	return TEXCHAR;
}
"\\xi"  {
	yylval.ch = L'\x03be';
	return TEXCHAR;
}
"\\pi"  {
	yylval.ch = L'\x03c0';
	return TEXCHAR;
}
"\\varpi"  {
	yylval.ch = L'\x03d6';
	return TEXCHAR;
}
"\\rho"  {
	yylval.ch = L'\x03c1';
	return TEXCHAR;
}
"\\varrho"  {
	yylval.ch = L'\x03f1';
	return TEXCHAR;
}
"\\sigma"  {
	yylval.ch = L'\x03c3';
	return TEXCHAR;
}
"\\varsigma"  {
	yylval.ch = L'\x03d8';
	return TEXCHAR;
}
"\\tau"  {
	yylval.ch = L'\x03c4';
	return TEXCHAR;
}
"\\upsilon"  {
	yylval.ch = L'\x03c5';
	return TEXCHAR;
}
"\\phi"  {
	yylval.ch = L'\x03d5';  // is this really \varphi?
	return TEXCHAR;
}
"\\varphi"  {
	yylval.ch = L'\x03c6';  // is this really \phi?
	return TEXCHAR;
}
"\\chi"  {
	yylval.ch = L'\x03c7';
	return TEXCHAR;
}
"\\psi"  {
	yylval.ch = L'\x03c8';
	return TEXCHAR;
}
"\\omega"  {
	yylval.ch = L'\x03c9';
	return TEXCHAR;
}

"\\Gamma"  {
	yylval.ch = L'\x0393';
	return TEXCHAR;
}
"\\Delta"  {
	yylval.ch = L'\x0394';
	return TEXCHAR;
}
"\\Theta"  {
	yylval.ch = L'\x0398';
	return TEXCHAR;
}
"\\Lambda"  {
	yylval.ch = L'\x039b';
	return TEXCHAR;
}
"\\Xi"  {
	yylval.ch = L'\x039e';
	return TEXCHAR;
}
"\\Pi"  {
	yylval.ch = L'\x03a0';
	return TEXCHAR;
}
"\\Sigma"  {
	yylval.ch = L'\x03a3';
	return TEXCHAR;
}
"\\Upsilon"  {
	yylval.ch = L'\x03d2';
	return TEXCHAR;
}
"\\Phi"  {
	yylval.ch = L'\x03a6';
	return TEXCHAR;
}
"\\Psi"  {
	yylval.ch = L'\x03a8';
	return TEXCHAR;
}
"\\Omega"  {
	yylval.ch = L'\x03a9';
	return TEXCHAR;
}

"\\circ"	{
	yylval.ch = L'\x25cb'; //2218';
	return TEXCHAR;
}

"\\inf"|"\\infty"	{
	yylval.ch = L'\x221e';
	return TEXCHAR;
}
"\\dag"|"\\dagger"	{
	yylval.ch = L'\x2020';
	return TEXCHAR;
}
"\\cdot"	{
	yylval.ch = L'\x0387';
	return TEXCHAR;
}

"``"	{
	yylval.ch = L'\x201c';
	return TEXCHAR;
}
"''"	{
	yylval.ch = L'\x201d';
	return TEXCHAR;
}
"`"	{
	yylval.ch = L'\x2018';
	return TEXCHAR;
}
"'"	{
	yylval.ch = L'\x2019';
	return TEXCHAR;
}

"\\\\"	{
	yylval.ch = '\\';
	return TEXCHAR;
}
"\\{"	{
	yylval.ch = '{';
	return TEXCHAR;
}
"\\}"	{
	yylval.ch = '}';
	return TEXCHAR;
}
"\\^"	{
	yylval.ch = '^';
	return TEXCHAR;
}
"\\_"	{
	yylval.ch = '_';
	return TEXCHAR;
}
"\\`"	{
	yylval.ch = '`';
	return TEXCHAR;
}
"\\'"	{
	yylval.ch = '\'';
	return TEXCHAR;
}

"\\bf"|"\\textbf"	{
	yylval.flag = FM_BOLD;
	return FACE_MODIFIER;
}
"\\em"|"\\emph"	{
	yylval.flag = FM_EMPH;
	return FACE_MODIFIER;
}
"\\it"	{
	yylval.flag = FM_ITALIC;
	return FACE_MODIFIER;
}
"\\underline"	{
	yylval.flag = FM_UNDERLINE;
	return FACE_MODIFIER;
}
"\\overline"	{
	yylval.flag = FM_OVERLINE;
	return FACE_MODIFIER;
}
"\\sout"	{
	yylval.flag = FM_STRIKE;
	return FACE_MODIFIER;
}

[{}^_]	{ return *yytext; }

.|\n	{
	yylval.ch = *yytext;
	return TEXCHAR;
}

%%

int yywrap()
{
	return 1;
}


void SetTeXLabel(const char *caption)
{
	// macro?  Can't link to this function from TeXLabel.cpp
	yy_scan_string(caption);
}

// Link error without this.
int isatty(int)
{
	return 0;
}
