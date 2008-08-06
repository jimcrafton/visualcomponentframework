
/*
 Copyright 2000-2007 The VCF Project, Orhun Birsoy.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXUIShellPeer.h"

namespace VCF {


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
	return true;
}

String OSXUIShellPeer::shellGetDirectory()
{
	NSArray *paths = NSSearchPathForDirectoriesInDomains( NSDesktopDirectory, NSUserDomainMask, YES );
	CFTextString tmp;
	tmp = [paths objectAtIndex:0];
	return tmp;
}

OSHandleID OSXUIShellPeer::shellGetHandleID()
{
	NSWorkspace* workSpace = [NSWorkspace sharedWorkspace];
	return (OSHandleID)workSpace;
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
	NSRect r = [[NSScreen mainScreen] frame];
	return r.size.width;
}

uint32 OSXUIShellPeer::shellGetHeight()
{
	NSRect r = [[NSScreen mainScreen] frame];
	return r.size.height;
}

VCF::Rect OSXUIShellPeer::shellGetUsableBounds()
{
	NSRect r = [[NSScreen mainScreen] frame];
	
	return Rect(r.origin.x, r.origin.y, r.origin.x+r.size.width, r.origin.y+r.size.height);
}

VCF::Point OSXUIShellPeer::getCurrentMousePosition()
{
	NSPoint pt = [NSEvent mouseLocation];
	return Point(pt.x,pt.y);
}

void OSXUIShellPeer::shellTranslateToScreenCoords( Control* control, Point* pt )
{
	NSView* view = (NSView*)control->getPeer()->getHandleID();
	NSPoint localPt;
	localPt.x = pt->x_;
	localPt.y = pt->y_;
	NSPoint screenPt = [view convertPoint: localPt toView:nil];
	pt->x_ = screenPt.x;
	pt->y_ = screenPt.y;
}

void OSXUIShellPeer::shellTranslateFromScreenCoords( Control* control, Point* pt )
{
	NSView* view = (NSView*)control->getPeer()->getHandleID();
	NSPoint screenPt;
	screenPt.x = pt->x_;
	screenPt.y = pt->y_;
	NSPoint localPt = [view convertPoint: screenPt fromView:nil];
	pt->x_ = localPt.x;
	pt->y_ = localPt.y;
}
		
void OSXUIShellPeer::performFileOp( int operationType, const std::vector<String>& srcFiles, const std::vector<String>& destFiles )
{
	NSMutableArray* fileTypes = [[NSMutableArray alloc] init];	

	std::vector<String>::const_iterator it = srcFiles.begin();
	while ( it != srcFiles.end() ) {
		const String& s = *it;
		
		++it;
	}
		
	switch ( operationType ) {
		case UIShell::foCopy : {
		//NSWorkspaceCopyOperation
		}
		break;
		
		case UIShell::foMove : {
		//NSWorkspaceMoveOperation
		}
		break;
		
		case UIShell::foDelete : {
		//NSWorkspaceRecycleOperation
		}
		break;
		
		case UIShell::foRename : {
		
		}
		break;
	}
	
	[fileTypes release];
}

void OSXUIShellPeer::launch( const String& fileName, const String& parameters )
{
	CFTextString tmp(fileName);
	[[NSWorkspace sharedWorkspace] openFile:tmp];
}

void OSXUIShellPeer::openTrash()
{

}

void OSXUIShellPeer::emptyTrash()
{

}

void OSXUIShellPeer::createFileShortcut( const String& originalFileName, const String& shortcutFileName )
{
	CFTextString src(originalFileName);
	CFTextString dest(shortcutFileName);
	[[NSFileManager defaultManager] createSymbolicLinkAtPath:dest pathContent:src];
	
}

MIMEType OSXUIShellPeer::getMIMEType( const String& fileName )
{
	CFTextString src(fileName);
	NSError* err = nil;
	NSString* type  = [[NSWorkspace sharedWorkspace] typeOfFile:src  error:&err];
	CFTextString tmp;
	tmp = type;
	return MIMEType();
}

void OSXUIShellPeer::createFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}

void OSXUIShellPeer::removeFileAssociation( const FileAssociationInfo& info, bool forAllUsers )
{

}


};


/**
$Id$
 */
