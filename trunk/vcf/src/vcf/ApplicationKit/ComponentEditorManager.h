#ifndef _VCF_COMPONENTEDITORMANAGER_H__
#define _VCF_COMPONENTEDITORMANAGER_H__
//ComponentEditorManager.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class ComponentEditor;


#define REGISTER_FOR_ALL_COMPONENTS		"*"

/**
*The ComponentEditorManager is used
*to regulate the different component editors that are available
*/
class APPLICATIONKIT_API ComponentEditorManager : public VCF::Object {
public:
	ComponentEditorManager();

	virtual ~ComponentEditorManager();

	/**
	*find a suitable Component editor for a given
	*classname.
	*/
	static ComponentEditor* findComponentEditor( const String& className );

	static void registerComponentEditor( ComponentEditor* componentEditor, const String& className );

	/**
	*initializes the Component editor manager for use - must be called at start up
	*/
	static void initComponentEditorManager();

	/**
	*frees any memory used by initComponentEditorManager(). Must be called before the
	*runtime shuts down
	*/
	static void closeComponentEditorManager();
protected:
	static ComponentEditorManager* componentEditorMgr;

	std::map<String,ComponentEditor*> componentEditorMap_;
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:06  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:15  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.4.4.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4  2003/05/17 20:37:01  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.3.22.1  2003/03/12 03:09:24  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_COMPONENTEDITORMANAGER_H__


