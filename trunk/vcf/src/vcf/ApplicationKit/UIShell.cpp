//UIShell.cpp

/*
Copyright 2000-2007 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//UIShell.h
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/UIShellPeer.h"



using namespace VCF;

UIShell* UIShell::getUIShell()
{
	return UIShell::shellInstance;
}


UIShell* UIShell::create()
{
	if ( NULL == UIShell::shellInstance ) {
		UIShell::shellInstance = new UIShell();
		UIShell::shellInstance->init();
	}

	return UIShell::shellInstance;
}

UIShell::UIShell()
{
	context_ = NULL;
	peer_ = NULL;
}

UIShell::~UIShell()
{
	/**may be NULL if the init function was never called,
	*which is theoretically possible if no one uses the UIShell object
	*Maybe the Toolkit should init the deskotp ?
	*/
	if ( NULL != context_ ) {
		context_->getPeer()->setContextID( 0 );
		delete context_;
	}
	context_ = NULL;

	delete peer_;
	peer_ = NULL;
}

void UIShell::init()
{
	if ( context_ == NULL ) {
		peer_ = UIToolkit::createUIShellPeer( this );
		if ( NULL == peer_ ) {
			throw InvalidPeer( MAKE_ERROR_MSG_2("UIToolkit returned a NULL UIShellPeer, UIToolkit::createUIShellPeer() is probably not implemented correctly") );
		}
		context_ = new GraphicsContext( peer_->shellGetGraphicsContextHandleID() );
	}
}

void UIShell::beginPainting( Rect* clippingRect )
{
	peer_->shellBeginPainting( clippingRect );
}

void UIShell::endPainting()
{
	peer_->shellEndPainting();
}

bool UIShell::supportsVirtualDirectories()
{
	return peer_->shellSupportsVirtualDirectories();
}


bool UIShell::hasFileSystemDirectory()
{
	return peer_->shellHasFileSystemDirectory();
}

String UIShell::getDirectory()
{
	return peer_->shellGetDirectory();
}

uint32 UIShell::getWidth()
{
	return peer_->shellGetWidth();
}

uint32 UIShell::getHeight()
{
	return peer_->shellGetHeight();
}

Rect UIShell::getUsableBounds()
{
	return peer_->shellGetUsableBounds();
}

Point UIShell::getCurrentMousePosition()
{
	return peer_->getCurrentMousePosition();
}


void UIShell::performFileOp( FileOps operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{
	peer_->performFileOp( operationType, srcFiles, destFiles );
}

void UIShell::copyFiles( const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{
	performFileOp( foCopy, srcFiles, destFiles );
}

void UIShell::moveFiles( const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{
	performFileOp( foMove, srcFiles, destFiles );
}

void UIShell::deleteFiles( const std::vector<String>& srcFiles )
{
	std::vector<String> dummy;
	performFileOp( foDelete, srcFiles, dummy );
}

void UIShell::launch( const String& fileName, const String& parameters )
{
	peer_->launch(fileName,parameters);
}

void UIShell::copyFile( const String& srcFile, const String& destFile )
{
	std::vector<String> src(1);
	src[0] = srcFile;
	std::vector<String> dest(1);
	dest[0] = destFile;
	copyFiles(src,dest);
}

void UIShell::moveFile( const String& srcFile, const String& destFile )
{
	std::vector<String> src(1);
	src[0] = srcFile;
	std::vector<String> dest(1);
	dest[0] = destFile;
	moveFiles(src,dest);
}

void UIShell::deleteFile( const String& srcFile )
{
	std::vector<String> src(1);
	src[0] = srcFile;
	deleteFiles(src);
}


void UIShell::openTrash()
{
	peer_->openTrash();
}

void UIShell::emptyTrash()
{
	peer_->emptyTrash();
}

void UIShell::createFileShortcut( const String& originalFileName, const String& shortcutFileName )
{
	peer_->createFileShortcut( originalFileName, shortcutFileName );
}

MIMEType UIShell::getMIMEType( const String& fileName )
{
	return peer_->getMIMEType( fileName );
}

void UIShell::createFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{
	peer_->createFileAssociation( info, forAllUsers );
}


void UIShell::removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{
	peer_->removeFileAssociation( info, forAllUsers );
}

/**
$Id: UIShell.cpp 2807 2006-06-27 20:25:49Z kdmix $
*/
