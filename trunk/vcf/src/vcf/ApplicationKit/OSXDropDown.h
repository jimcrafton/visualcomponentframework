#ifndef _VCF_OSXDROPDOWN_H__
#define _VCF_OSXDROPDOWN_H__
/*
 Copyright 2000-3004 The VCF Project.
 Please see License.txt in the top level directory
 where you installed the VCF.
 */


namespace VCF {
	class OSXDropDown : public OSXControl, public DropDownPeer {
	public:
		OSXDropDown( Control* control );
		virtual ~OSXDropDown();
		
		virtual void create( Control* owningControl );
				
		virtual Rect getBounds();
		virtual void setBounds( VCF::Rect* rect );
		
		virtual void enableEditBox( bool val );
		virtual bool editBoxEnabled();
		
		virtual void setEditText( const String& text );
		virtual String getEditText();
		
		virtual void setDropDownWidth( double val );
		virtual double getDropDownWidth();
		
		virtual void setDropDownCount( const uint32& dropDownCount );
		virtual uint32 getDropDownCount();
		
		
		virtual void selectItem( const uint32& index );
		
		virtual uint32 getSelectedItem();
		
		virtual void setFocusedItem( const uint32& index );
		
		virtual uint32 getFocusedItem();
		
		virtual bool isItemSelected( const uint32& index );
		
		virtual Rect getItemRect( const uint32& index );	
		
		virtual Rect getItemImageRect( const uint32& index );
		
		virtual uint32 hitTest( const Point& point );	
		
		virtual Enumerator<uint32>* getSelectedItems();
		
		virtual void rangeSelect( const Rect& selectionRect );	
		
		virtual bool allowsMultiSelect();
		
		virtual void setAllowsMultiSelect( const bool& allowsMultiSelect );	
		
		virtual void setLargeImageList( ImageList* imageList );
		
		virtual void setSmallImageList( ImageList* imageList );
		
		virtual void setFont( Font* font );
				
	protected:
		void onCtrlModelChanged( Event* e );
		void onListModelChanged( Event* e );
		
		Array<uint32> selectedItems_;
		
		
	};
	
};


#endif //_VCF_OSXDROPDOWN_H__