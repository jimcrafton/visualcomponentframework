#ifndef _VCF_AGGUISHELLPEER_H__
#define _VCF_AGGUISHELLPEER_H__

/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/UIShellPeer.h"

namespace VCF {

	class AggUIShellPeer : public UIShellPeer {
	public:
		AggUIShellPeer( UIShell* shell );

		virtual ~AggUIShellPeer();

		virtual void shellBeginPainting( Rect* clippingRect );

		virtual void shellEndPainting();

		virtual bool shellSupportsVirtualDirectories();

		virtual bool shellHasFileSystemDirectory();

		virtual String shellGetDirectory();

		virtual OSHandleID shellGetHandleID();

		virtual OSHandleID shellGetGraphicsContextHandleID();

		virtual void shellSetUIShell( UIShell* shell );

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

#endif //_VCF_AGGUISHELLPEER_H__

/**
$Id$
*/

