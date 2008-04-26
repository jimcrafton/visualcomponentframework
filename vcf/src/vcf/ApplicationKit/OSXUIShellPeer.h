#ifndef _VCF_OSXUISHELLPEER_H__
#define _VCF_OSXUISHELLPEER_H__

/*
 Copyright 2000-2007 The VCF Project, Orhun Birsoy.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/UIShellPeer.h"

namespace VCF {
    
class OSXUIShellPeer : public UIShellPeer {
public:
		OSXUIShellPeer( UIShell* shell );
        
		virtual ~OSXUIShellPeer();
        
		virtual void shellBeginPainting( Rect* clippingRect );

		virtual void shellEndPainting();

		virtual bool shellSupportsVirtualDirectories();

		virtual bool shellHasFileSystemDirectory();

		virtual String shellGetDirectory();

		virtual OSHandleID shellGetGraphicsContextHandleID();

		virtual OSHandleID shellGetHandleID();

		virtual void shellSetUIShell( UIShell* shell );

		virtual void shellTranslateToScreenCoords( Control* control, Point* pt );

		virtual void shellTranslateFromScreenCoords( Control* control, Point* pt );

		virtual uint32 shellGetWidth();

		virtual uint32 shellGetHeight();

		virtual Rect shellGetUsableBounds();

		virtual Point getCurrentMousePosition();

		virtual void performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles );

		virtual void launch( const String& fileName, const String& parameters );

		virtual void openTrash();
		virtual void emptyTrash();

		virtual void createFileShortcut( const String& originalFileName, const String& shortcutFileName );

		virtual MIMEType getMIMEType( const String& fileName );

		virtual void createFileAssociation( const FileAssociationInfo& info, bool forAllUsers );
		virtual void removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers );
        
	};
};

#endif //_VCF_OSXUISHELLPEER_H__

/**
$Id$
 */
