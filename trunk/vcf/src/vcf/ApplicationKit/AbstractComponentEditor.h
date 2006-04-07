#ifndef _VCF_ABSTRACTCOMPONENTEDITOR_H__
#define _VCF_ABSTRACTCOMPONENTEDITOR_H__
//AbstractComponentEditor.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#ifndef _VCF_COMPONENTEDITOR_H__
#include "vcf/ApplicationKit/ComponentEditor.h"
#endif 


namespace VCF  {

/**
\class AbstractComponentEditor AbstractComponentEditor.h "vcf/ApplicationKit/AbstractComponentEditor.h"
*Basic implementation of the ComponentEditor interface.
*Useful when creating custom component editors.
*/
class APPLICATIONKIT_API AbstractComponentEditor : public VCF::Object, public ComponentEditor {
public:
	AbstractComponentEditor();

	virtual ~AbstractComponentEditor();

	virtual void initialize();

	virtual int getAttributes( const ulong32& index );

	virtual int getCommandParentIndex( const ulong32& index );

	virtual Command* createCommand( const ulong32& index );

	virtual ulong32 getCommandCount();

	virtual int getDefaultCommandIndex() {
		return defaultCommandIndex_;
	}

	virtual Component* getComponent() {
		return component_;
	}

	virtual void setComponent( Component* component );

	virtual void copy();

	void setCommandCount( ulong32 val );

	void setAttributes( const ulong32& index, const int& attribute );

	void setParentIndex( const ulong32& index, const int& parentIndex );
protected:
	int defaultCommandIndex_;
	std::vector<int> attributes_;
	std::vector<int> parentIndices_;

	Component* component_;
};

/**
\class AbstractControlEditor AbstractComponentEditor.h "vcf/ApplicationKit/AbstractComponentEditor.h"
*Class AbstractComponentEditor documentation
*/
class APPLICATIONKIT_API AbstractControlEditor : public AbstractComponentEditor, public ControlEditor {
public:
	AbstractControlEditor();

	virtual ~AbstractControlEditor();

	virtual bool isParentValid( Control* parent );

	virtual Control* getControl();

	virtual void setControl( Control* control );

	virtual void mouseDown( MouseEvent* event );

	virtual void mouseMove( MouseEvent* event );

	virtual void mouseUp( MouseEvent* event );

	virtual void mouseDblClick( MouseEvent* event );
protected:

private:
};

}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:21  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.2  2006/03/14 02:25:46  ddiego
*large amounts of source docs updated.
*
*Revision 1.2.6.1  2005/08/28 05:14:17  ddiego
*small changes to component editor class.
*
*Revision 1.2  2004/08/07 02:49:05  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/06/06 07:05:29  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 03:43:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:12  ddiego
*migration towards new directory structure
*
*Revision 1.7.4.1  2004/04/26 21:58:17  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.7  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.6.4.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.6.4.1  2003/09/12 00:09:31  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.6  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.5.22.1  2003/03/12 03:09:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.5  2002/02/15 03:18:39  ddiego
*minor niggles to make the VCF Builder compiles
*
*Revision 1.4  2002/02/14 05:04:45  ddiego
*documentation...
*
*Revision 1.3  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ABSTRACTCOMPONENTEDITOR_H__


