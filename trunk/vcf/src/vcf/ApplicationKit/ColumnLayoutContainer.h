#ifndef _VCF_COLUMNLAYOUTCONTAINER_H__
#define _VCF_COLUMNLAYOUTCONTAINER_H__
//ColumnLayoutContainer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {


#define COLUMNLAYOUTCONTAINER_CLASSID		"3df1d3a5-d362-4d33-8b49-2ce693c72006"

/**
\class ColumnLayoutContainer ColumnLayoutContainer.h "vcf/ApplicationKit/ColumnLayoutContainer.h"
*/
class ColumnLayoutContainer : public StandardContainer {
public:
	ColumnLayoutContainer(): columnCount_(0) {
		setBorderWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) );
	}

	ColumnLayoutContainer(Component* owner): StandardContainer(owner), columnCount_(0) {
		setBorderWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) );
	}

	enum {
		ColumnWidthResize = -1
	};


	virtual void resizeChildren( Control* control ) {
		Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
								clientBounds.top_ + topBorderHeight_,
								clientBounds.right_ - rightBorderWidth_,
								clientBounds.bottom_ - bottomBorderHeight_ );

		int col = 0;

		int width = clientBounds.getWidth();
		Rect controlBounds = clientBounds;

		std::vector<int> rows;
		double maxHeight = 0;
		std::vector<Control*>::iterator it = controls_.begin();

		int row = 0;
		rows.push_back( maxHeight );

		while ( it != controls_.end() ) {
			if ( (*it)->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			maxHeight = maxVal<>(maxHeight,(*it)->getHeight());

			if ( col >= columnCount_ ) {
				col = 0;
				row ++;
				rows.push_back( maxHeight );
			}
			else {
				rows[row] = maxHeight;
			}

			col ++;

			it ++;
		}


		row = 0;
		col = 0;
		it = controls_.begin();
		while ( it != controls_.end() ) {
			if ( (*it)->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			if ( ((columnCount_-1) == col) &&
					(ColumnWidthResize == columnWidths_[col]) ) {

				controlBounds.right_ = clientBounds.right_;
			}
			else{
				controlBounds.right_ = controlBounds.left_ + columnWidths_[col];
			}

			controlBounds.bottom_ = controlBounds.top_ + rows[row];

			(*it)->setBounds( &controlBounds );


			controlBounds.left_ = controlBounds.right_;
			controlBounds.left_ +=
				UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing );

			col ++;
			if ( col >= columnCount_ ) {
				controlBounds.top_ = controlBounds.bottom_;
				controlBounds.top_ +=
					UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing );


				controlBounds.left_ = clientBounds.left_;
				controlBounds.right_ = clientBounds.left_;

				col = 0;
				row ++;
			}
			it ++;
		}
	}

	int getColumnWidth(  const uint32& i ) {
		return columnWidths_[i];
	}

	void setColumnWidth( const uint32& i, int val, bool addMissingValues ) {

		if ( addMissingValues && ((i+1) > columnWidths_.size()) ) {
			size_t missing = (i+1) - columnWidths_.size();
			if ( missing > 0 ) {
				columnWidths_.resize( missing + columnWidths_.size() );
				columnCount_ = columnWidths_.size();
			}
		}

		columnWidths_[i] = val;
	}


	void addColumnWidth( int val ){
		columnWidths_.push_back( val );
		columnCount_ = columnWidths_.size();
	}

	void insertColumnWidth( const uint32& i, int val ){
		columnWidths_.insert( columnWidths_.begin() + i, val );
		columnCount_ = columnWidths_.size();
	}

	void removeColumnWidth( const uint32& i ) {
		columnWidths_.erase( columnWidths_.begin() + i );
		columnCount_ = columnWidths_.size();
	}

	uint32 getColumnCount() {
		return columnWidths_.size();
	}

	void setColumnCount( int val ) {
		columnCount_ = val;
		columnWidths_.resize(columnCount_,ColumnLayoutContainer::ColumnWidthResize);
	}

	void setColumnWidth( int col, int val ) {
		columnWidths_[col] = val;
	}


	int columnCount_ ;
	std::vector<int> columnWidths_;

};


};


#endif // _VCF_COLUMNLAYOUTCONTAINER_H__

/**
$Id$
*/
