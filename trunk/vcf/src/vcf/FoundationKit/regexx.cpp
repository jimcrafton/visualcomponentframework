//regexx.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/*************************************************************************/
/*                                                                       */
/*  Regexx - Regular Expressions C++ solution.                           */
/*                                                                       */
/*  http://projects.nn.com.br/                                           */
/*                                                                       */
/*  Copyright (C) 2000 Gustavo Niemeyer <gustavo@nn.com.br>              */
/*                                                                       */
/*  This library is free software; you can redistribute it and/or        */
/*  modify it under the terms of the GNU Library General Public          */
/*  License as published by the Free Software Foundation; either         */
/*  version 2 of the License, or (at your option) any later version.     */
/*                                                                       */
/*  This library is distributed in the hope that it will be useful,      */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of       */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU    */
/*  Library General Public License for more details.                     */
/*                                                                       */
/*  You should have received a copy of the GNU Library General Public    */
/*  License along with this library; if not, write to the                */
/*  Free Software Foundation, Inc., 59 Temple Place - Suite 330,         */
/*  Boston, MA  02111-1307, USA.                                         */
/*                                                                       */
/*************************************************************************/

// $Revision$
// $Date$

/**
*Modified on June 1 2002, for use in the VCF
*by Jim Crafton
*got rid of dependency on ostream
*placed inside of VCF namespace
*made it conform to VCF nameing standards
*/

#include "vcf/FoundationKit/FoundationKit.h"

#include "vcf/FoundationKit/regexx.h"
#include "thirdparty/common/pcre/pcre.h"


using namespace VCF;
using namespace VCF::RegExx;

const unsigned int& Regexx::exec(int _flags) throw(Regexx::CompileException)
{
    AnsiString tmpStr = str_;
    AnsiString tmpExpr = expr_;
	if(!compiled_) {
		const char *errptr;
		int erroffset;
		int cflags =
			((_flags&nocase)?PCRE_CASELESS:0)
			| ((_flags&newline)?PCRE_MULTILINE:0);
		preg_ = pcre_compile(tmpExpr.c_str(),cflags,&errptr,&erroffset,0);
		if(preg_ == NULL) {
			throw CompileException(errptr);
		}
		pcre_fullinfo(preg_, NULL, PCRE_INFO_CAPTURECOUNT, (void*)&capturecount_);
		compiled_ = true;
	}

	if(!study_ && (_flags&study)) {
		const char *errptr;
		extra_ = pcre_study(preg_, 0, &errptr);
		if(errptr != NULL)
			throw CompileException(errptr);
		study_ = true;
	}

	match.clear();

	int eflags = ((_flags&notbol)?PCRE_NOTBOL:0) | ((_flags&noteol)?PCRE_NOTEOL:0);

	int ssv[33];
	int ssc;
	matches_ = 0;

	ssc = pcre_exec(preg_,extra_,tmpStr.c_str(),tmpStr.length(),0,eflags,ssv,33);
	bool ret = (ssc > 0);

	if(_flags&global) {
		if(_flags&nomatch)
			while(ret) {
				matches_++;
				ret = (pcre_exec(preg_,extra_,tmpStr.c_str(),tmpStr.length(),ssv[1],eflags,ssv,33) > 0);
			}
			else if(_flags&noatom)
				while(ret) {
					matches_++;
					match.push_back(RegexxMatch(str_,ssv[0],ssv[1]-ssv[0]));
					ret = (pcre_exec(preg_,extra_,tmpStr.c_str(),tmpStr.length(),ssv[1],eflags,ssv,33) > 0);
				}
				else
					while(ret) {
						matches_++;
						match.push_back(RegexxMatch(str_,ssv[0],ssv[1]-ssv[0]));
						match.back().atom.reserve(capturecount_);
						for(int i = 1; i < ssc; i++) {
							if (ssv[i*2] != -1)
								match.back().atom.push_back(RegexxMatchAtom(str_,ssv[i*2],ssv[(i*2)+1]-ssv[i*2]));
							else
								match.back().atom.push_back(RegexxMatchAtom(str_,0,0));
						}
						ret = (pcre_exec(preg_,extra_,tmpStr.c_str(),tmpStr.length(),ssv[1],eflags,ssv,33) > 0);
					}
	}
	else {
		if(_flags&nomatch) {
			if(ret)
				matches_=1;
		}
		else if(_flags&noatom) {
			if(ret) {
				matches_=1;
				match.push_back(RegexxMatch(str_,ssv[0],ssv[1]-ssv[0]));
			}
		}
		else {
			if(ret) {
				matches_=1;
				match.push_back(RegexxMatch(str_,ssv[0],ssv[1]-ssv[0]));
				match.back().atom.reserve(capturecount_);
				for(int i = 1; i < ssc; i++) {
					if (ssv[i*2] != -1)
						match.back().atom.push_back(RegexxMatchAtom(str_,ssv[i*2],ssv[(i*2)+1]-ssv[i*2]));
					else
						match.back().atom.push_back(RegexxMatchAtom(str_,0,0));
				}
				ret = (pcre_exec(preg_,extra_,tmpStr.c_str(),tmpStr.length(),ssv[1],eflags,ssv,33) > 0);
			}
		}
	}
	return matches_;
}

const String& Regexx::replace(const String& _repstr, int _flags) throw(Regexx::CompileException)
{
	exec(_flags&~nomatch);
	std::vector< std::pair<unsigned int,String::size_type> > v;
	v.reserve(capturecount_);
	String::size_type pos = _repstr.find("%");
	while(pos != String::npos) {
		if(_repstr[pos-1] != '%'
			&& _repstr[pos+1] >= '0'
			&& _repstr[pos+1] <= '9') {
			v.push_back(std::pair<unsigned int,String::size_type>(_repstr[pos+1]-'0',pos));
		}
		pos = _repstr.find("%",pos+1);
	}
	replaced_ = str_;
	std::vector<RegexxMatch>::reverse_iterator m;
	std::vector< std::pair<unsigned int,String::size_type> >::reverse_iterator i;
	for(m = match.rbegin(); m != match.rend(); m++) {
		String tmprep = _repstr;
		for(i = v.rbegin(); i != v.rend(); i++) {
			if(i->first < m->atom.size())
				tmprep.replace(i->second,2,m->atom[i->first]);
			else
				tmprep.erase(i->second,2);
		}
		replaced_.replace(m->start(),m->length(),tmprep);
	}
	return replaced_;
}


std::vector<String> split(const String& where, const String& str)
{
	std::vector<String> v;
	String::size_type lastpos = 0;
	String::size_type pos = str.find(where);
	while(pos != String::npos) {
		v.push_back(str.substr(lastpos,pos-lastpos));
		lastpos = pos+where.length();
		pos = str.find(where,lastpos);
	}
	v.push_back(str.substr(lastpos));
	return v;
}

std::vector<String> splitex(const String& regex, const String& str)
{
	std::vector<String> v;
	Regexx rxx;
	rxx.expr(regex);
	rxx.str(str);
	v.reserve(rxx.exec());
	std::vector<RegexxMatch>::const_iterator i;
	String::size_type lastpos = 0;
	for(i = rxx.match.begin(); i != rxx.match.end(); i++) {
		v.push_back(str.substr(lastpos,i->start()-lastpos));
		lastpos = i->start()+i->length();
	}
	v.push_back(str.substr(lastpos,i->start()));
	return v;
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.6  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.5  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.3  2004/04/30 05:44:34  ddiego
*added OSX changes for unicode migration
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


