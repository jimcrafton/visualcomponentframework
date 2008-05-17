
/*
 Copyright 2000-2007 The VCF Project, Orhun Birsoy.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXUIShellPeer.h"

using namespace VCF;

OSXUIShellPeer::OSXUIShellPeer( UIShell* shell )
{
}

OSXUIShellPeer::~OSXUIShellPeer()
{
}

void OSXUIShellPeer::shellBeginPainting( Rect* clippingRect )
{
}

void OSXUIShellPeer::shellEndPainting()
{
}

bool OSXUIShellPeer::shellSupportsVirtualDirectories()
{
	return false;
}

bool OSXUIShellPeer::shellHasFileSystemDirectory()
{
	return false;
}

String OSXUIShellPeer::shellGetDirectory()
{
	return "";
}

OSHandleID OSXUIShellPeer::shellGetHandleID()
{
	return 0;
}

OSHandleID OSXUIShellPeer::shellGetGraphicsContextHandleID()
{
	return 0;
}

void OSXUIShellPeer::shellSetUIShell( UIShell* shell )
{
}

uint32 OSXUIShellPeer::shellGetWidth()
{
	return 0;
}

uint32 OSXUIShellPeer::shellGetHeight()
{
	return 0;
}

VCF::Rect OSXUIShellPeer::shellGetUsableBounds()
{
	return Rect();
}

VCF::Point OSXUIShellPeer::getCurrentMousePosition()
{
	return Point();
}

void OSXUIShellPeer::performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{

}

void OSXUIShellPeer::launch( const String& fileName, const String& parameters )
{

}

void OSXUIShellPeer::openTrash()
{

}

void OSXUIShellPeer::emptyTrash()
{

}

void OSXUIShellPeer::createFileShortcut( const String& originalFileName, const String& shortcutFileName )
{

}

MIMEType OSXUIShellPeer::getMIMEType( const String& fileName )
{
	return MIMEType();
}

void OSXUIShellPeer::createFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}

void OSXUIShellPeer::removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}

/**
$Id$
 */
