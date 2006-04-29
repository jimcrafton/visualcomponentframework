#ifndef _VCF_WIN32COMPONENT_H__
#define _VCF_WIN32COMPONENT_H__
//Win32Component.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF
{

class Win32Component : public AbstractWin32Component
{
public:
	Win32Component( Control* component );

	virtual ~Win32Component();

	virtual void create( Control* owningControl );
};


};


#endif // _VCF_WIN32COMPONENT_H__

/**
$Id$
*/
