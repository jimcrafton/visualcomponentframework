//OSXListview.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/ApplicationKitPrivate.h"
#include "vcf/ApplicationKit/ListViewControl.h"

#include "vcf/ApplicationKit/OSXControl.h"

#include "vcf/ApplicationKit/OSXListview.h"

#define OSX_LISTVIEW_CTRL_PRIMARY_COL		'PRIM'






@implementation OSXListviewDataSrc


- (void)setModel:(VCF::ListModel*)aModel
{
	model = aModel;
}

- (NSInteger)numberOfRowsInTableView:(NSTableView *)aTableView
{	
	NSInteger result = 0;
	if ( NULL != model ) {
		result = model->getCount();
	}
	return result;
}

- (id)tableView:(NSTableView *)aTableView objectValueForTableColumn:(NSTableColumn *)aTableColumn row:(NSInteger)rowIndex
{
	id result = nil;
	if ( NULL != model ) {
		NSString* str;
		VCF::CFTextString tmp;
		tmp = model->getAsString( rowIndex );
		str = tmp;
		[str retain];
		result = str;
	}
	return result;
}

@end




@interface VCFListView : NSTableView
{

}
@end



@implementation VCFListView

- (BOOL)isFlipped
{
	return YES;
}


- (void)drawRect:(NSRect)rect
{
	[super drawRect:rect];
	
	VCF::OSXControl* peer = VCF::OSXControl::getPeerForView( self );
	
	if ( NULL != peer ) {		
		//peer->internal_paint( rect );
	}	
}
 
- (void)setFrame:(NSRect)rect
{
	[super setFrame:rect];
	
	VCF::OSXControl::handleSetFrame( self, rect );
}

- (void)mouseDown:(NSEvent *)theEvent
{
	[super mouseDown:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
	
}

- (void)mouseUp:(NSEvent *)theEvent
{
	[super mouseUp:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );	
}


- (void)rightMouseDown:(NSEvent *)theEvent
{
	[super rightMouseDown:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}

- (void)rightMouseUp:(NSEvent *)theEvent
{
	[super rightMouseUp:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}


- (void)mouseMoved:(NSEvent *)theEvent
{
	[super mouseMoved:theEvent];
	
	VCF::OSXControl::handleEventForView( self, theEvent );
}
@end

@implementation OSXListviewTableDelegate

- (BOOL)textShouldBeginEditing:(NSText *)textObject
{
	return listView->getAllowLabelEditing() ? YES : NO;
}

- (void)setListView:(VCF::OSXListview* ) aListView
{
	listView = aListView;
}
@end



namespace VCF {

OSXListview::OSXListview( ListViewControl* listviewControl ):
	OSXControl( listviewControl ),
	listviewControl_( listviewControl ),
	dataSrc_(nil),
	tableView_(nil),
	tableDelegate_(nil),
	allowLabelEditing_(false)
{
	addCallback( new ClassProcedure1<Event*,OSXListview>(this, &OSXListview::onControlModelChanged), "OSXListview::onControlModelChanged" );		
	addCallback( new ClassProcedure1<Event*,OSXListview>(this, &OSXListview::onListModelChanged), "OSXListview::onListModelChanged" );	
	addCallback( new ClassProcedure1<Event*,OSXListview>(this, &OSXListview::onColumnModelAdded), "OSXListview::onColumnModelAdded" );	
	addCallback( new ClassProcedure1<Event*,OSXListview>(this, &OSXListview::onColumnModelRemoved), "OSXListview::onColumnModelRemoved" );	
	addCallback( new ClassProcedure1<Event*,OSXListview>(this, &OSXListview::onColumnModelChanged), "OSXListview::onColumnModelChanged" );	
	
	
	dataSrc_ = [[OSXListviewDataSrc alloc] init];
	tableDelegate_ = [[OSXListviewTableDelegate alloc] init];
	[tableDelegate_ setListView:this];
}

OSXListview::~OSXListview()
{
	[dataSrc_ release];
}

void OSXListview::onControlModelChanged( Event* e )
{
	Model* model = listviewControl_->getModel();
	
	[dataSrc_ setModel: (ListModel*)model];
	
	if ( NULL != model ) {
		model->ModelChanged += getCallback( "OSXListview::onListModelChanged" );
		ListModel* lm = (ListModel*)model;
		//lm->add( "item 1" );

		model =  listviewControl_->getColumnModel();
		model->ModelChanged += getCallback( "OSXListview::onColumnModelChanged" );

		ColumnModel* cm = (ColumnModel*)model;
		cm->ItemAdded += getCallback( "OSXListview::onColumnModelAdded" );

		cm->ItemRemoved += getCallback( "OSXListview::onColumnModelRemoved" );
			
	}
	
	[tableView_ reloadData];
}

void OSXListview::onListModelChanged( Event* e )
{
	[tableView_ reloadData];
}

void OSXListview::onColumnModelAdded( Event* e )
{
	ListModelEvent* lme = (ListModelEvent*)e;	
	NSNumber* colID = [NSNumber numberWithUnsignedInt: lme->index];
	NSTableColumn* col = [[NSTableColumn alloc] initWithIdentifier:colID];
	[col setWidth: 100.0];
	
	[tableView_ addTableColumn:col];
}

void OSXListview::onColumnModelRemoved( Event* e )
{

}

void OSXListview::onColumnModelChanged( Event* e )
{
	[tableView_ reloadData];
}
	
void OSXListview::create( Control* owningControl )
{
	NSRect r;
	r.origin.x = 0;
	r.origin.y = 0;
	r.size.width = 1;
	r.size.height = 1;
	
	VCFListView* list = [[VCFListView alloc] initWithFrame:r];
	[list setDataSource: dataSrc_];
	
	NSNumber* colID = [NSNumber numberWithUnsignedInt: 1];
	NSTableColumn* col = [[NSTableColumn alloc] initWithIdentifier:colID];
	[col setWidth: 100.0];
	
	[list addTableColumn:col];
	
	[list setUsesAlternatingRowBackgroundColors:YES];
	
	NSScrollView* scrollView = [[NSScrollView alloc] initWithFrame:r];
	//[scrollView setBorderType:NSNoBorder];
	
	[scrollView setHasHorizontalScroller:YES];
	[scrollView setHasVerticalScroller:YES];
	
	
	[scrollView setAutohidesScrollers:YES];
	[scrollView setScrollsDynamically:YES];
	
	[scrollView setDocumentView:list];
	
	tableView_ = list;
	view_ = scrollView;
	
	[tableView_ setDelegate: tableDelegate_];
	
	OSXControl::setViewForPeer( tableView_, this );
	
	owningControl->ControlModelChanged += getCallback( "OSXListview::onControlModelChanged" );
	
	OSXControl::create( owningControl );
}

void OSXListview::selectItem( const uint32& index )
{
	NSIndexSet* indexes = [NSIndexSet indexSetWithIndex:index];	
	[tableView_ selectRowIndexes: indexes byExtendingSelection:NO];
	[indexes release];
}

uint32 OSXListview::getSelectedItem()
{
	return [tableView_ selectedRow];
}

void OSXListview::setFocusedItem( const uint32& index )
{
	NSIndexSet* indexes = [NSIndexSet indexSetWithIndex:index];	
	[tableView_ selectRowIndexes: indexes byExtendingSelection:NO];
	[indexes release];
}

uint32 OSXListview::getFocusedItem()
{
	return [tableView_ selectedRow];
}

bool OSXListview::isItemSelected( const uint32& index )
{
	return [tableView_ isRowSelected:index];
}

Rect OSXListview::getItemRect( const uint32& index )
{
	NSRect r = [tableView_ rectOfRow:index];
	
	return Rect(r.origin.x,r.origin.y,r.origin.x+r.size.width,r.origin.y+r.size.height);
}

Rect OSXListview::getItemImageRect( const uint32& index )
{
	NSRect r = [tableView_ rectOfRow:index];
	
	return Rect(r.origin.x,r.origin.y,r.origin.x+r.size.width,r.origin.y+r.size.height);
}

uint32 OSXListview::hitTest( const Point& point )
{
	NSPoint pt;
	pt.x = point.x_;
	pt.y = point.y_;
	return [tableView_ rowAtPoint:pt];
}

Enumerator<uint32>* OSXListview::getSelectedItems()
{
	selectedItems_.clear();
	NSIndexSet* indexes = [tableView_ selectedRowIndexes];
	
	uint32 count = [indexes count];
	std::vector<NSUInteger> idxs(count);
	
	[indexes getIndexes: &idxs[0] maxCount:count inIndexRange:nil];
	
	selectedItems_.resize(count);
	
	for (uint32 i=0;i<[	indexes count];i++ ) {
		selectedItems_[i] = idxs[i];
	}
	
	return selectedItems_.getEnumerator();
}

void OSXListview::rangeSelect( const Rect& selectionRect )
{

}

bool OSXListview::allowsMultiSelect()
{
	return [tableView_ allowsMultipleSelection] ? true : false;
}

void OSXListview::setAllowsMultiSelect( const bool& allowsMultiSelect )
{
	[tableView_ setAllowsMultipleSelection: allowsMultiSelect ? YES : NO ];
}

void OSXListview::setLargeImageList( ImageList* imageList )
{

}

void OSXListview::setSmallImageList( ImageList* imageList )
{

}


bool OSXListview::ensureVisible(const uint32& index, bool partialOK )
{
	[tableView_ scrollRowToVisible: index];
	return false;
}
	
void OSXListview::setColumnWidth( const uint32& index, const double& width, ColumnAutosizeType type )
{
	NSArray* columns = [tableView_ tableColumns];
	NSTableColumn* col = [columns objectAtIndex: index];
	if ( nil != col ) {
		[col setWidth: width];
	}
}

double OSXListview::getColumnWidth( const uint32& index )
{
	NSArray* columns = [tableView_ tableColumns];
	NSTableColumn* col = [columns objectAtIndex: index];
	if ( nil != col ) {
		return [col width];
	}
	return 0.0;
}

TextAlignmentType OSXListview::getColumnTextAlignment( const uint32& index )
{
	return TextAlignmentType();
}

void OSXListview::setColumnTextAlignment( const uint32& index, const TextAlignmentType& val )
{

}

IconStyleType OSXListview::getIconStyle()
{
	return IconStyleType();
}

void OSXListview::setIconStyle( const IconStyleType& iconStyle )
{

}

IconAlignType OSXListview::getIconAlignment()
{
	return IconAlignType();
}

void OSXListview::setIconAlignment( const IconAlignType& iconAlignType )
{

}

bool OSXListview::getAllowLabelEditing()
{
	return allowLabelEditing_;
}

void OSXListview::setAllowLabelEditing( const bool& allowLabelEditing )
{
	allowLabelEditing_ = allowLabelEditing;
}

int32 OSXListview::getDisplayOptions()
{
	int32 result = lvdoDefault;
	NSUInteger mask = [tableView_ gridStyleMask];
	if ( mask != NSTableViewGridNone ) {
		result |= lvdoGridLines;
	}
	return result;
}	

void OSXListview::setDisplayOptions( const int32& displayOptions )
{
//lvdoDefault = 0,
//	lvdoHotTracking = 1,
//	lvdoFullRowSelect = 2,
//	lvdoGridLines = 4

	NSUInteger mask = [tableView_ gridStyleMask];
	if ( displayOptions & lvdoGridLines ) {
		mask = NSTableViewSolidVerticalGridLineMask | NSTableViewSolidHorizontalGridLineMask;
	}
	else if ( !(displayOptions & lvdoGridLines) ) {
		mask = NSTableViewGridNone;
	}
	[tableView_ setGridStyleMask:mask];
}

};


/**
$Id$
*/
