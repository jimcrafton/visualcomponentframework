//OSXClipboard.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


//OSXClipboard.h

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/OSXClipboard.h"




using namespace VCF;


#define kUTTypePlainText CFSTR("public.plain-text")
#define kUTTypeRTF CFSTR("public.rtf")
#define kUTTypeFileURL CFSTR("public.file-url")
#define kUTTypePNG CFSTR("public.png")


String UTItoMimeType( CFStringRef uti )
{
	String result;

	if ( UTTypeEqual( uti, kUTTypePlainText ) ) {
		result = "text/plain";
	}

	return result;
}




OSXClipboard::OSXClipboard()
{
	PasteboardRef tmp;
	if ( noErr == PasteboardCreate( kPasteboardClipboard, &globalPasteBoard_ ) ) {
		//globalPasteBoard_ = tmp;
	}
	else {
		throw RuntimeException( MAKE_ERROR_MSG_2("Failed to attach to global pasteboard!") );
	}
}

OSXClipboard::~OSXClipboard()
{
	PasteboardResolvePromises( globalPasteBoard_ );
}

void OSXClipboard::copy( VCF::DataObject* data )
{
	CFTextString flavor;
	Enumerator<String>* dataTypes = data->getSupportedDataTypes();
	while ( dataTypes->hasMoreElements() ) {
		CFTextString type;
		type = dataTypes->nextElement();
		/*
		if ( type == STRING_DATA_TYPE ) {
			flavor = kUTTypePlainText;
		}
		else if ( type == RTF_DATA_TYPE ) {
			flavor = kUTTypeRTF;
		}
		else if ( type == INTEGER_DATA_TYPE ) {
			//flavor = kUTTypeRTF;
		}
		else if ( type == OBJECT_DATA_TYPE ) {
			//flavor = kUTTypeRTF;
		}
		else if ( type == FILE_DATA_TYPE ) {
			flavor = kUTTypeFileURL;
		}
		else if ( type == BYTE_STREAM_DATA_TYPE ) {
			//flavor = kUTTypeFileURL;
		}
		else if ( type == IMAGE_DATA_TYPE ) {
			flavor = kUTTypePNG; //assume PNG for default image type
		}
		else if ( type == COMPONENT_DATA_TYPE ) {
			//we need a custom type!!!
			//flavor = kUTTypePlainText; //assume PNG for default image type
		}
		*/
		
		flavor = UTTypeCreatePreferredIdentifierForTag( kUTTagClassMIMEType, type, NULL );

		BasicOutputStream memStream;
		if ( data->saveToStream( type, &memStream ) ) {
			memStream.seek( 0, stSeekFromStart );

			CFRefObject<CFDataRef> dataRef = CFDataCreate( NULL, (const UInt8*)memStream.getBuffer(), memStream.getSize() );

			PasteboardPutItemFlavor( globalPasteBoard_, data, flavor, dataRef, 0 );
		}
	}	
}

VCF::DataObject* OSXClipboard::paste( const String& dataType )
{
	VCF::DataObject* result = NULL;

	PasteboardSynchronize( globalPasteBoard_ );

	//currently we are using mime-types 
	//map the mimetype to the Apple UTTI

	ItemCount itemCount = 0;
	if ( noErr == PasteboardGetItemCount( globalPasteBoard_, &itemCount ) ) {
		PasteboardItemID itemID = 0;
		for ( UInt32 index = 0;index<itemCount;index++ ) {
			//index is 1 based!
			PasteboardGetItemIdentifier( globalPasteBoard_, index+1, &itemID );

			
			CFRefObject<CFArrayRef> flavArray;
			if ( noErr == PasteboardCopyItemFlavors(  globalPasteBoard_, itemID, &flavArray ) ) {
				int count = CFArrayGetCount(flavArray);
				for ( int flavIndex = 0;flavIndex<count;flavIndex++ ) {
					CFStringRef flavorType;
					flavorType = (CFStringRef)CFArrayGetValueAtIndex( flavArray, flavIndex );

					PasteboardFlavorFlags flags = 0;
					PasteboardGetItemFlavorFlags( globalPasteBoard_, itemID, flavorType, &flags );
					
					if ( dataType == UTItoMimeType( flavorType ) ) {
						CFRefObject<CFDataRef> dataRef;
						if ( noErr == PasteboardCopyItemFlavorData( globalPasteBoard_, itemID, flavorType, &dataRef ) ) {
							result = new VCF::DataObject();
							const UInt8 * buf = CFDataGetBytePtr(dataRef);
							CFIndex length = CFDataGetLength(dataRef);
							result->addSupportedDataType( dataType, new BinaryPersistable( buf, length ) );
						}
						break;
					}
				}
			}
		}
	}

	return result;
}



bool OSXClipboard::hasDataType( const String& dataType )
{
	bool result = false;

	PasteboardSynchronize( globalPasteBoard_ );

	//currently we are using mime-types 
	//map the mimetype to the Apple UTTI

	ItemCount itemCount = 0;
	if ( noErr == PasteboardGetItemCount( globalPasteBoard_, &itemCount ) ) {
		PasteboardItemID itemID = 0;
		for ( UInt32 index = 0;index<itemCount;index++ ) {
			//index is 1 based!
			PasteboardGetItemIdentifier( globalPasteBoard_, index+1, &itemID );

			
			CFRefObject<CFArrayRef> flavArray;
			if ( noErr == PasteboardCopyItemFlavors(  globalPasteBoard_, itemID, &flavArray ) ) {
				int count = CFArrayGetCount(flavArray);
				for ( int flavIndex = 0;flavIndex<count;flavIndex++ ) {
					CFStringRef flavorType;
					flavorType = (CFStringRef)CFArrayGetValueAtIndex( flavArray, flavIndex );

					PasteboardFlavorFlags flags = 0;
					PasteboardGetItemFlavorFlags( globalPasteBoard_, itemID, flavorType, &flags );

					if ( dataType == UTItoMimeType( flavorType ) ) {
						result = true;
						break;
					}
				}
			}
		}
	}
	
	return result;
}

DataObject* OSXClipboard::createDataObjectFromPasteBoard( PasteboardRef pasteBoard )
{
	DataObject* result = new DataObject();
	
	//sync the paste board
	PasteboardSynchronize( pasteBoard );
	
	ItemCount itemCount = 0;
	if ( noErr == PasteboardGetItemCount( pasteBoard, &itemCount ) ) {
		PasteboardItemID itemID = 0;
		for ( UInt32 index = 0;index<itemCount;index++ ) {
			//index is 1 based!
			PasteboardGetItemIdentifier( pasteBoard, index+1, &itemID );

			
			CFRefObject<CFArrayRef> flavArray;
			if ( noErr == PasteboardCopyItemFlavors(  pasteBoard, itemID, &flavArray ) ) {
				int count = CFArrayGetCount(flavArray);
				for ( int flavIndex = 0;flavIndex<count;flavIndex++ ) {
					CFStringRef flavorType;
					flavorType = (CFStringRef)CFArrayGetValueAtIndex( flavArray, flavIndex );

					PasteboardFlavorFlags flags = 0;
					PasteboardGetItemFlavorFlags( pasteBoard, itemID, flavorType, &flags );
					
					String dataType = UTItoMimeType( flavorType );
					
					CFRefObject<CFDataRef> dataRef;
					if ( noErr == PasteboardCopyItemFlavorData( pasteBoard, itemID, flavorType, &dataRef ) ) {
						const UInt8 * buf = CFDataGetBytePtr(dataRef);
						CFIndex length = CFDataGetLength(dataRef);
						result->addSupportedDataType( dataType, new BinaryPersistable( buf, length ) );
					}
				}
			}
		}
	}
	
	return result;
}

/**
*CVS Log info
*$Log$
*Revision 1.2  2005/07/09 23:14:53  ddiego
*merging in changes from devmain-0-6-7 branch.
*
*Revision 1.1.2.3  2005/06/27 03:28:54  ddiego
*more osx work.
*
*Revision 1.1.2.2  2005/06/23 01:26:55  ddiego
*build updates
*
*Revision 1.1.2.1  2005/06/15 15:41:13  ddiego
*minor osx stuff
*/


