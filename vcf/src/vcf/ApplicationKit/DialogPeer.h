#ifndef _VCF_DIALOGPEER_H__
#define _VCF_DIALOGPEER_H__
//DialogPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{

/** @interface */
class APPLICATIONKIT_API DialogPeer : public VCF::Interface {
public:
	virtual ~DialogPeer(){};

	virtual void showMessage( const String& message, const String& caption ) = 0;

	virtual UIToolkit::ModalReturnType showMessage( const String& message, const String& caption,
													const long& messageButtons,	const Dialog::MessageStyle& messageStyle ) = 0;													
													
};

};


#endif // _VCF_DIALOGPEER_H__

/**
$Id$
*/
