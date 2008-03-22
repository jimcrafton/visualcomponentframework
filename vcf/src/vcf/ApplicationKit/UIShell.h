#ifndef _VCF_UISHELL_H__
#define _VCF_UISHELL_H__
//UIShell.h

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

#include "vcf/FoundationKit/MIMEType.h"

namespace VCF  {

class GraphicsContext;
class UIShellPeer;
class UIToolkit;
class ApplicationKit;


class FileAssociationInfo {
public:
	String extension;
	MIMEType mimeType;
	String documentClass;
	String documentDescription;
	String documentIconPath;
	String launchingProgram;
};

/**
\class UIShell UIShell.h "vcf/ApplicationKit/UIShell.h"
The desktop represents the Windowing systems bottom most
control or "window" and is usually the first window the 
User sees when the system starts up. The UIShell is also 
sometimes refered to as the Shell, as in Microsoft Windows. 
A desktop may or may not allow files, i.e. it in fact is
an actual location on the filesystem.
*/
class APPLICATIONKIT_API UIShell : public VCF::Object {
public:
	GraphicsContext* getContext() {
		return context_;
	}

	/**
	*Prepares the desktop for painting.
	*MUST be called before calling getContext(), or errors
	*may occur
	*@param Rect* specifies an optional rectangular region to clip
	*the drawing to. The rectangles coords are screen coords.
	*/
	void beginPainting( Rect* clippingRect = NULL);

	/**
	*called after finished painting on the desktop
	*allows for native Windowing system cleanup to happen
	*/
	void endPainting();

	bool supportsVirtualDirectories();


	bool hasFileSystemDirectory();

	String getDirectory();

	UIShellPeer* getUIShellPeer() {
		return peer_;
	}

	static UIShell* getUIShell();

	uint32 getWidth();

	uint32 getHeight();

	Rect getUsableBounds();

	Point getCurrentMousePosition();

	enum FileOps{
		foCopy = 1,
		foMove,
		foDelete,
		foRename
	};

	void performFileOp( FileOps operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles );

	void copyFiles( const std::vector<String>& srcFiles, const std::vector<String>& destFiles );
	void moveFiles( const std::vector<String>& srcFiles, const std::vector<String>& destFiles );
	void deleteFiles( const std::vector<String>& srcFiles );

	void copyFile( const String& srcFile, const String& destFile );
	void moveFile( const String& srcFile, const String& destFile );
	void deleteFile( const String& srcFile );

	void launch( const String& fileName, const String& parameters );

	void openTrash();
	void emptyTrash();

	void createFileShortcut( const String& originalFileName, const String& shortcutFileName );

	MIMEType getMIMEType( const String& fileName );

	void createFileAssociation( const FileAssociationInfo& info, bool forAllUsers );

	void removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers );

	friend class UIToolkit;
	friend class ApplicationKit;
protected:
	UIShell();

	virtual ~UIShell();

	/**
	*called by the UIToolkit. repeated calls after the first initialization
	*do nothing
	*/	
	void init();
	static UIShell* create();
	static UIShell* shellInstance;
	GraphicsContext* context_;
	bool paintingInitialized_;
	UIShellPeer* peer_;
private:
};


}; //end of namespace VCF


#endif // _VCF_UISHELL_H__

/**
$Id: UIShell.h 2807 2006-06-27 20:25:49Z kdmix $
*/
