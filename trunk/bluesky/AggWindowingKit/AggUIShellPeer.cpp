
/*
Copyright 2000-2006 The VCF Project, Orhun Birsoy.
Please see License.txt in the top level directory
where you installed the VCF.
*/

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "AggUIShellPeer.h"

using namespace VCF;

AggUIShellPeer::AggUIShellPeer( UIShell* shell )
{

}

AggUIShellPeer::~AggUIShellPeer()
{

}

void AggUIShellPeer::shellBeginPainting( Rect* clippingRect )
{

}

void AggUIShellPeer::shellEndPainting()
{
	
}

bool AggUIShellPeer::shellSupportsVirtualDirectories()
{
	
	return false;
}

bool AggUIShellPeer::shellHasFileSystemDirectory()
{
	
	return false;
}

String AggUIShellPeer::shellGetDirectory()
{
	
	return "";
}

OSHandleID AggUIShellPeer::shellGetHandleID()
{
	
	return 0;
}

OSHandleID AggUIShellPeer::shellGetGraphicsContextHandleID()
{
	
	return 0;
}

void AggUIShellPeer::shellSetUIShell( UIShell* shell )
{
	
}

uint32 AggUIShellPeer::shellGetWidth()
{
	
	return 0;
}

uint32 AggUIShellPeer::shellGetHeight()
{
	
	return 0;
}

Rect AggUIShellPeer::shellGetUsableBounds()
{
	
	return Rect();
}

Point AggUIShellPeer::getCurrentMousePosition()
{
	
	return Point();
}

void AggUIShellPeer::performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{

}

void AggUIShellPeer::launch( const String& fileName, const String& parameters )
{

}

void AggUIShellPeer::openTrash()
{

}

void AggUIShellPeer::emptyTrash()
{

}

void AggUIShellPeer::createFileShortcut( const String& originalFileName, const String& shortcutFileName )
{

}

MIMEType AggUIShellPeer::getMIMEType( const String& fileName )
{
	return MIMEType();
}

void AggUIShellPeer::createFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}

void AggUIShellPeer::removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}

/**
$Id$
*/

