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

	virtual int getAttributes( const uint32& index );

	virtual int getCommandParentIndex( const uint32& index );

	virtual Command* createCommand( const uint32& index );

	virtual uint32 getCommandCount();

	virtual int getDefaultCommandIndex() {
		return defaultCommandIndex_;
	}

	virtual Component* getComponent() {
		return component_;
	}

	virtual void setComponent( Component* component );

	virtual void copy();

	void setCommandCount( uint32 val );

	void setAttributes( const uint32& index, const int& attribute );

	void setParentIndex( const uint32& index, const int& parentIndex );
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


#endif // _VCF_ABSTRACTCOMPONENTEDITOR_H__

/**
$Id$
*/
