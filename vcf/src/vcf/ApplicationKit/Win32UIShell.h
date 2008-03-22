#ifndef _VCF_WIN32UISHELL_H__
#define _VCF_WIN32UISHELL_H__
//Win32UIShell.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/ApplicationKit/UIShellPeer.h"



namespace VCF  {

/**
*Class Win32UIShell documentation
*/
class Win32UIShell : public Object, public UIShellPeer {
public:
	Win32UIShell( UIShell* shell );

	virtual ~Win32UIShell();

	/**
	*Prepares the shell for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies a rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	virtual void shellBeginPainting( Rect* clippingRect );

	/**
	*called after finished painting on the shell
	*allows for native Windowing system cleanup to happen
	*/
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
protected:
	UIShell* shell_;
	HRGN hClipRgn_;
private:
};


}; //end of namespace VCF


#endif // _VCF_WIN32UISHELL_H__

/**
$Id: Win32UIShell.h 2807 2006-06-27 20:25:49Z kdmix $
*/
