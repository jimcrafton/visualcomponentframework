#ifndef _VCF_REGEXX_H__
#define _VCF_REGEXX_H__
//regexx.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


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





namespace VCF {

namespace RegExx {

  /** Class to store atoms.
   *
   *  @author Gustavo Niemeyer
   *
   *Note: this class is not derived form VCF::Object because there is
   *simply no good reason to. It adds nothing to the functionality of hte
   *class.
   */
  class RegexxMatchAtom
  {

  public:

    inline
    RegexxMatchAtom(String& stringToUse,
		    String::size_type start,
		    String::size_type length)
      : str_(stringToUse), start_(start), length_(length)
    {}

    inline RegexxMatchAtom& operator=(const RegexxMatchAtom& rxxma)  {
      str_ = rxxma.str_;
      start_ = rxxma.start_;
      length_ = rxxma.length_;
      return *this;
    }

    /// Retrieves the atom string.
    inline String str() const {
		return str_.substr(start_,length_);
	}

    /// Returns the position in the original string where the atom starts.
    inline const String::size_type& start() const{
		return start_;
	}

    /// Length of the atom string.
    inline const String::size_type& length() const   {
		return length_;
	}

    /// Operator to transform a RegexxMatchAtom into a string.
    inline operator String() const {
		return str_.substr(start_,length_);
	}

    /// Operator to compare a RegexxMatchAtom with a string.
    inline bool operator==(const String& s) const {
		return ( str_.substr(start_,length_) == s );
	}

  private:

    String &str_;
    String::size_type start_;
    String::size_type length_;

  };

  /** Class to store matches.
   *
   *  @author Gustavo Niemeyer
   *Note: this class is not derived form VCF::Object because there is
   *simply no good reason to. It adds nothing to the functionality of hte
   *class.
   */
  class RegexxMatch
  {

  public:

    inline RegexxMatch(String& stringToUse, String::size_type start, String::size_type length)
      : str_(stringToUse), start_(start), length_(length)
    {}

    inline RegexxMatch& operator=(const RegexxMatch& rxxm)  {
      str_ = rxxm.str_;
      start_ = rxxm.start_;
      length_ = rxxm.length_;
      return *this;
    }

    /// Retrieves the match string.
    inline String str() const {
		return str_.substr(start_,length_);
	}

    /// Returns the position in the original string where the match starts.
    inline const String::size_type& start() const {
		return start_;
	}

    /// Length of the match string.
    inline const String::size_type& length() const{
		return length_;
	}

    /// Operator to transform a RegexxMatch into a string.
    inline operator String() const {
		return str_.substr(start_,length_);
	}

    /// Operator to compare a RegexxMatch with a string.
    inline bool operator==(const String& s) const {
		return (str_.substr(start_,length_)==s);
	}

    /// Vector of atoms found in this match.
    std::vector<RegexxMatchAtom> atom;

  private:

    String &str_;
    String::size_type start_;
    String::size_type length_;

  };

  /** The main Regexx class.
   *
   * Regexx is a complete regular expressions C++ solution.
   * It implements easy expression execution, global searching,
   * replace with atom substitution, easy match and atom strings
   * retrieving. It's also included in the package functions to
   * split strings with strings or regular expressions.
   *
   * @author Gustavo Niemeyer
   *
   *Note: this class is not derived form VCF::Object because there is
   *simply no good reason to. It adds nothing to the functionality of hte
   *class.
   **/

  class Regexx
  {

  public:

    /// These are the flags you can use with exec() and replace().
    enum flags {

      /// Global searching, otherwise Regexx stops after the first match.
      global  = 1,

      /// Ignore case.
      nocase  = 2,

      /** Do not store matches. If you don't want to retrieve the matched
       *  strings and atoms, use this. It's a lot faster. Note that you
       *  can retrieve the number of matches with matches(), operator int()
       *  or the return value of exec(). Ignored if used
       *  with replace().
       */
      nomatch = 4,

      /** Do not store atoms. If you don't want to retrieve the matched
       *  atoms, use this. It's a faster. If you are using nomatch, you
       *  don't need this.
       */
      noatom  = 8,

      /** If you're going to use the same regular expression several times
       *  or if you're going to apply it in a big text, use this flag.
       **/
      study   = 16,

      /** Match-any-character operators don't match the newline. A non
       *  matching list ([^...]) not containing a newline does not match
       *  a newline. Match-beggining-of-line operator (^) matches the empty
       *  string immediately after a newline, regardless of whether
       *  Regexx::notbol is set or not. Match-end-of-line operator ($)
       *  matches the empty string immediately before a newline, regardless
       *  of wheter Regexx::noteol is set or not.
       **/
      newline = 32,

      /** The match-beginig-of-line operator always fails to match (see
       *  Regexx::newline). This flag can be used when different portions of
       *  a string are passed to Regexx and the beggining of the string
       *  should not be interpreted as the beggining of the line.
       **/
      notbol  = 64,

      /// The match-end-of-line operator always fails to match.
      noteol  = 128

    };


    /** This exception is thrown when there are errors while compiling
     *  expressions.
     */
    class CompileException : public BasicException {
    public:
      CompileException(const String& message) : BasicException(message) {}
    };

    /// Constructor
    inline
    Regexx()
      : compiled_(false), study_(false), extra_(NULL), matches_(0)
    {}

    /// Destructor
    inline ~Regexx() {
		if( compiled_ ) {
			free(preg_);
			if ( study_ ) {
				free(extra_);
			}
		}
	}

    /** Constructor with regular expression execution.
     *
     *  This constructor allows you to run one-line regular expressions.
     *  Since there is a operator int(), you can use it expecting a
     *  return value or inside a boolean context.
     *
     *  @see operator int()
     */
    inline Regexx(const String& stringToUse, const String& expression, int flags = 0) throw(Regexx::CompileException)
      : compiled_(false), study_(false), extra_(NULL), matches_(0)
	{
		exec( stringToUse, expression, flags);
	}

    /** Constructor with regular expression string replacing.
     *
     *  This constructor allows you to run one-line regular expression
     *  string replacing. Since there is a operator string(), you can use
     *  it expecting a return value or inside a boolean context.
     *
     *  @see operator string()
     */
    inline
    Regexx(const String& stringToUse, const String& expression, const String& repstr, int flags = 0) throw(Regexx::CompileException)
      : compiled_(false), study_(false), extra_(NULL), matches_(0)
	{
		replace(stringToUse,expression,repstr,flags);
	}

    /** Set the regular expression to use with exec() and replace().
     *
     *  Use this function only if you are going to use the exec() and/or
     *  replace functions that don't provide the regular expression.
     *
     *  @return Self reference.
     */
    inline Regexx&    expr(const String& expression);

    /// Retrieve the current regular expression.
    inline const String& expr() const {
		return expr_;
	}

    /** Set the string to use with exec() and replace().
     *
     *  Use this function only if you are going to use the exec() and/or
     *  replace functions that don't provide the string.
     *
     *  @return Self reference.
     */
    inline Regexx& str(const String& stringToUse);

    /// Retrieve the current string.
    inline const String& str() const {
		return str_;
	}

    /** Execute a regular expression.
     *
     *  To use this function you have to store the string and regular
     *  expression with the str() and expr() functions before. It also works
     *  if you want to reexecute a regular expression that you've
     *  executed before.
     *
     *  @return Number of matches.
     */
    const unsigned int& exec(int flags = 0) throw(Regexx::CompileException);

    /** Execute a regular expression.
     *
     *  To use this function you have to store the string with the str()
     *  function before. It also works if you want to reexecute a regular
     *  expression that you've executed before.
     *
     *  @return Number of matches.
     */
    inline const unsigned int& exec(const String& expression, int flags = 0) throw(Regexx::CompileException);

    /** Execute a regular expression.
     *  @return Number of matches.
     */
    inline const unsigned int& exec(const String& stringToUse, const String& expression, int flags = 0) throw(Regexx::CompileException);

    /** Replace string with regular expression.
     *
     *  To use this function you have to store the string and regular
     *  expression with the str() and expr() functions before. It also works
     *  if you want to reexecute a regular expression that you've
     *  executed before.
     *
     *  @param repstr Replace string. You can reference atoms in this
     *                 string with '%0'-'%9'. If you want to include a '%'
     *                 character you have to escape it with another '%'.
     *  @return Replaced string.
     */
    const String& replace(const String& repstr, int flags = 0) throw(CompileException);

    /** Replace string with regular expression.
     *
     *  To use this function you have to store the string with the str()
     *  function before. It also works if you want to reexecute a regular
     *  expression that you've executed before.
     *
     *  @param repstr Replace string. You can reference atoms in this
     *                 string with '%0'-'%9'. If you want to include a '%'
     *                 character you have to escape it with another '%'.
     *  @return Replaced string.
     */
    inline const String& replace(const String& expression, const String& repstr, int flags = 0) throw(Regexx::CompileException);

    /** Replace string with regular expression.
     *  @return Replaced string.
     */
    inline const String& replace(const String& stringToUse, const String& expression,
									const String& repstr, int flags = 0)  throw(Regexx::CompileException);

    /** Customized replace string with regular expression.
     *
     *  The first parameter to this function is a function/class with
     *  a RegexxMatch as the only parameter. This function/class will be
     *  executed for each match of the regular expression and the match
     *  will be replaced by the string returned by the function/class.
     *
     *  To use this function you have to store the string and regular
     *  expression with the str() and expr() functions before. It also works
     *  if you want to reexecute a regular expression that you've
     *  executed before.
     *
     *  @param func Function/Class to be executed for each match.
     *  @return Replaced string.
     */
    inline const String& replacef(String (*func)(const RegexxMatch&) , int flags = 0) throw(Regexx::CompileException);

    /** Customized replace string with regular expression.
     *
     *  The first parameter to this function is a function/class with
     *  a RegexxMatch as the only parameter. This function/class will be
     *  executed for each match of the regular expression and the match
     *  will be replaced by the string returned by the function/class.
     *
     *  To use this function you have to store the string with the str()
     *  function before. It also works if you want to reexecute a regular
     *  expression that you've executed before.
     *
     *  @param func Function/Class to be executed for each match.
     *  @return Replaced string.
     */
    inline const String& replacef(const String& expression,
									String (*func)(const RegexxMatch&), int flags = 0) throw(Regexx::CompileException);

    /** Customized replace string with regular expression.
     *
     *  The first parameter to this function is a function/class with
     *  a RegexxMatch as the only parameter. This function/class will be
     *  executed for each match of the regular expression and the match
     *  will be replaced by the string returned by the function/class.
     *
     *  @param func Function/Class to be executed for each match.
     *  @return Replaced string.
     */
    inline const String& replacef(const String& stringToUse, const String& expression,
									String (*func)(const RegexxMatch&), int flags = 0) throw(Regexx::CompileException);

    /** Returns the number of matches of the last exec()/replace()/replacef().
     *
     *  It works even if you use the nomatch flag.
     *
     */
    inline const unsigned int& matches() const {
		return matches_;
	}

    /** Returns the number of matches of the last exec()/replace()/replacef().
     *
     *  It works even if you use the nomatch flag.
     *
     */
    inline operator unsigned int() const {
		return matches_;
	}

    /// Returns the string of the last replace() or replacef().
    inline const String& replaced() const  {
		return replaced_;
	}

    /// Returns the string of the last replace() or replacef().
    inline operator  String() const {
		return replaced_;
	}

    /** The vector of matches.
     *
     *  Unless you set the nomatch flag, every found match is stored in
     *  this vector.
     *
     */
    std::vector<RegexxMatch> match;

  private:

    bool compiled_;
    bool study_;
    String expr_;
    String str_;
    int capturecount_;

    unsigned int matches_;
    String replaced_;

    void* preg_;
    void* extra_;

  };

  inline Regexx& Regexx::expr(const String& expression)
  {
	  if(compiled_) {
		  free(preg_);
		  compiled_ = false;
		  if(study_) {
			  free(extra_);
			  study_ = false;
			  extra_ = NULL;
		  }
	  }
	  expr_ = expression;
	  return *this;
  }

  inline Regexx& Regexx::str(const String& stringToUse)
  {
	  str_ = stringToUse;
	  return *this;
  }

  inline const unsigned int& Regexx::exec(const String& expression, int flags) throw(Regexx::CompileException)
  {
	  expr(expression);
	  return exec(flags);
  }

  inline const unsigned int& Regexx::exec(const String& stringToUse, const String& expression, int flags) throw(Regexx::CompileException)
  {
	  str(stringToUse);
	  expr(expression);
	  return exec(flags);
  }


  inline const String& Regexx::replace(const String& expression, const String& repstr, int flags) throw(Regexx::CompileException)
  {
	  expr(expression);
	  return replace(repstr,flags);
  }

  inline const String& Regexx::replace(const String& stringToUse, const String& expression,
										const String& repstr, int flags) throw(Regexx::CompileException)
  {
	  str(stringToUse);
	  expr(expression);
	  return replace(repstr,flags);
  }

  inline const String& Regexx::replacef(String (*func)(const RegexxMatch&), int flags ) throw(Regexx::CompileException)
  {
	  exec( flags & ~nomatch );
	  replaced_ = str_;
	  std::vector<RegexxMatch>::reverse_iterator m;
	  for(m = match.rbegin(); m != match.rend(); m++)
		  replaced_.replace(m->start(),m->length(),func(*m));
	  return replaced_;
  }

  inline const String& Regexx::replacef(const String& expression,
										String (*func)(const RegexxMatch&), int flags ) throw(Regexx::CompileException)
  {
	  expr(expression);
	  return replacef(func,flags);
  }

  inline const String& Regexx::replacef(const String& stringToUse, const String& expression,
										String (*func)(const RegexxMatch&), int flags ) throw(Regexx::CompileException)
  {
	  str(stringToUse);
	  expr(expression);
	  return replacef(func,flags);
  }


  std::vector<String> split(const String& where, const String& _str);

  std::vector<String> splitex(const String& exp, const String& _str);

} //end of RegExx namespace

} //end of VCF namespace


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:16  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:07:14  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


#endif // _VCF_REGEXX_H__


