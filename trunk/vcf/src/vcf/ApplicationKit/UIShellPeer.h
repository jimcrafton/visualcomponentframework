#ifndef _VCF_UISHELLPEER_H__
#define _VCF_UISHELLPEER_H__
//UIShellPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

class UIShell;
class FileAssociationInfo;


/**
\class UIShellPeer UIShellPeer.h "vcf/ApplicationKit/UIShellPeer.h"
*Class UIShellPeer interface documentation
*/
class APPLICATIONKIT_API UIShellPeer : public Interface {
public:
	virtual ~UIShellPeer(){};

	/**
	*Prepares the shell for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies a rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	virtual void shellBeginPainting( Rect* clippingRect ) = 0;

	/**
	*called after finished painting on the shell
	*allows for native Windowing system cleanup to happen
	*/
	virtual void shellEndPainting() = 0;

	virtual bool shellSupportsVirtualDirectories() = 0;

	virtual bool shellHasFileSystemDirectory() = 0;

	virtual String shellGetDirectory() = 0;


	virtual OSHandleID shellGetHandleID() = 0;

	virtual OSHandleID shellGetGraphicsContextHandleID() = 0;

	virtual void shellSetUIShell( UIShell* shell ) = 0;

	virtual uint32 shellGetWidth() = 0;

	virtual uint32 shellGetHeight() = 0;

	virtual Rect shellGetUsableBounds() = 0;

	virtual Point getCurrentMousePosition() = 0;

	virtual void performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles ) = 0;

	virtual void launch( const String& fileName, const String& parameters ) = 0;

	virtual void openTrash() = 0;
	virtual void emptyTrash() = 0;

	virtual void createFileShortcut( const String& originalFileName, const String& shortcutFileName ) = 0;

	virtual MIMEType getMIMEType( const String& fileName ) = 0;

	virtual void createFileAssociation( const FileAssociationInfo& info ) = 0;
};


}; //end of namespace VCF


#endif // _VCF_UISHELLPEER_H__

/**
$Id: UIShellPeer.h 2807 2006-06-27 20:25:49Z kdmix $
*/
