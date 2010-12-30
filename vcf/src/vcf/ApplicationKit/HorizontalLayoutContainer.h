
#ifndef _HORIZONTALLAYOUTCONTAINER_H__
#define _HORIZONTALLAYOUTCONTAINER_H__


/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/



#if _MSC_VER > 1000
#   pragma once
#endif



//container properties
//that may use component contants
//when be written to a Visual Form file.
#define	CONTAINER_MAXROWHEIGHT		"maxrowheight"
#define	CONTAINER_ROWSPACERHEIGHT	"rowspacerheight"



namespace VCF {

#define HORIZONTALLAYOUTCONTAINER_CLASSID		"11aab5e2-36d2-47c7-9391-c40b185d6b9e"

/**
\class HorizontalLayoutContainer HorizontalLayoutContainer.h "vcf/ApplicationKit/HorizontalLayoutContainer.h"
*/
class HorizontalLayoutContainer : public StandardContainer {
public:

	HorizontalLayoutContainer() :
		maximizeLastRow_(false),
		equalizeHeights_(false),
		averageHeights_(false),
		keepControlsWidth_(false){

		setBorderWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) );

		setNumberOfColumns(2);

		setColumnWidth( 0, 100 );

		setColumnWidth( 1, 100 );

		setColumnTweenWidth( 0, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );


		setMaxRowHeight( UIToolkit::getUIMetricValue( UIMetricsManager::mtLabelHeight ) );

		setRowSpacerHeight( UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) );
	}

	HorizontalLayoutContainer( Component* owner ):
		StandardContainer(owner),
		maximizeLastRow_(false)
	{

		setBorderWidth( UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) );

		setNumberOfColumns(2);

		setColumnWidth( 0, 100 );

		setColumnWidth( 1, 100 );

		setColumnTweenWidth( 0, UIToolkit::getUIMetricValue( UIMetricsManager::mtControlHorizontalSpacing ) );


		setMaxRowHeight( UIToolkit::getUIMetricValue( UIMetricsManager::mtLabelHeight ) );

		setRowSpacerHeight( UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) );

	}


	void setNumberOfColumns( const uint32& numColumns ) {

		if ( columns_.size() != numColumns ) {

			columns_.clear();
			columnTweens_.clear();

			columns_.resize( numColumns, 0.0 );

			columnTweens_.resize( numColumns-1, 0.0 );
		}
	}

	uint32 getNumberOfColumns() {
		return columns_.size();
	}

	void setColumnWidth( const uint32& index, const double& width ) {		
		if ( (index+1) > columns_.size() ) {
			size_t missing = (index+1) - columns_.size();
		
			columns_.resize( missing + columns_.size() );
			columnTweens_.resize( columns_.size()-1, 0.0 );
		}		
		
		columns_[index] = width;
	}

	double getColumnWidth( const uint32& index )  {
		return columns_[index];
	}
	
	void insertColumnWidth( const uint32& index, const double& val ) {
		columns_.insert( columns_.begin() + index, val );
	}

	void removeColumnWidth( const uint32& index ) {
		columns_.erase( columns_.begin() + index );
	}



	void setColumnTweenWidth( const uint32& index, const double& width ) {
		int missing = (index+1) - columnTweens_.size();
				
		if ( missing > 0 ) {
			columnTweens_.resize( missing + columnTweens_.size() );
		}	

		columnTweens_[index] = width;
	}

	double getColumnTweenWidth( const uint32& index )  {
		return columnTweens_[index];
	}


	void insertColumnTweenWidth( const uint32& index, const double& val ) {
		columnTweens_.insert( columnTweens_.begin() + index, val );
	}

	void removeColumnTweenWidth( const uint32& index ) {
		columnTweens_.erase( columnTweens_.begin() + index );
	}
	
	uint32 getColumnTweenCount()  {
		return columnTweens_.size();
	}

	void setMaxRowHeight( const double& val ) {
		maxRowHeight_ = val;
	}

	double getMaxRowHeight() {
		return maxRowHeight_;
	}

	/**
	Set if we want all the row heights to be the same
	as the hightest one. The default is false;
	This flag excludes setEqualizeHeights().
	*/
	void setEqualizeHeights( const bool& equalize ) {
		equalizeHeights_ = equalize;
	}

	bool getEqualizeHeights() {
		return equalizeHeights_;
	}

	/**
	Set if we want all the row heights to be the same
	as the average height that fills the parent control. The default is false;
	*/
	void setAverageHeights( const bool& average ) {
		averageHeights_ = average;
	}

	bool getAverageHeights() {
		return averageHeights_;
	}

	/**
	Set if we want the controls to keep their width or,
	as it is by default, resize their width to the one of
	the column where they are located.
	*/
	void setKeepControlsWidth( const bool& keep ) {
		keepControlsWidth_ = keep;
	}

	bool getKeepControlsWidth() {
		return keepControlsWidth_;
	}

	double getMinimumVisibleHeight() {

		double result = 0.0;
		std::vector<Control*>::iterator it = controls_.begin();
		int colCount = columns_.size();

		int col = 0;

		result = maxRowHeight_;

		while ( it != controls_.end() ) {
			Control* control = *it;
			col ++;
			if ( col >= colCount ) {
				col = 0;
				result += (maxRowHeight_ + rowSpacerHeight_);
			}
			it ++;
		}

		return result;
	}


	virtual void resizeChildren( Control* control ) {
		VCF::Rect clientBounds = controlContainer_->getClientBounds();

		if ( clientBounds.isEmpty() ) {
			return; //nothing to do, so just exit the function
		}

		clientBounds.setRect( clientBounds.left_ + leftBorderWidth_,
			clientBounds.top_ + topBorderHeight_,
			clientBounds.right_ - rightBorderWidth_,
			clientBounds.bottom_ - bottomBorderHeight_ );


		std::vector<Control*>::iterator it = controls_.begin();

		int colCount = columns_.size();
		int tweenCount = columnTweens_.size();

		int col = 0;
		int tween = 0;
		VCF::Rect cell = clientBounds;
		cell.right_ = cell.left_ + columns_[col];

		//cell.bottom_ = cell.top_ + maxRowHeight_;



		

		int rowCount = (controls_.size() / columns_.size()) + (controls_.size() % columns_.size());
		int row = 0;

		//calculate row heights so that things don't get "scrunched" together
		std::vector<double> rowHeights(rowCount);
		double h = 0;//maxRowHeight_;
		while ( it != controls_.end() ) {
			Control* control = *it;

			if ( control->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			h = maxVal<>( h, maxVal<>( control->getHeight(), control->getPreferredHeight() ) );

			if ( h > maxRowHeight_ ) {
				maxRowHeight_ = h;
			}
			col ++;

 			// this stays here: we do not always have all the controls in all the columns.
			rowHeights[row] = h;

			if ( col >= colCount ) {
				col = 0;

				h = 0;
				row ++;
			}

			++ it;
		}

		if ( equalizeHeights_ ) {
			row = 0;
			std::vector<double>::iterator it = rowHeights.begin();
			while ( it != rowHeights.end() ) {
				rowHeights[row] = maxRowHeight_;
				row ++;
				++ it;
			}
		}
		else if ( averageHeights_ && ( 0 < row ) ) {
			maxRowHeight_ = ( clientBounds.getHeight() - (rowSpacerHeight_*(row-1)) ) / row;
			row = 0;
			std::vector<double>::iterator it = rowHeights.begin();
			while ( it != rowHeights.end() ) {
				rowHeights[row] = maxRowHeight_;
				row ++;
				++ it;
			}
		}

		row = 0;
		col = 0;

		it = controls_.begin();

		while ( it != controls_.end() ) {

			Control* control = *it;


			if ( control->isIgnoredForLayout() ) {
				it ++;
				continue;
			}

			if ( !keepControlsWidth_ &&  ( col == (colCount-1) ) ) {

				cell.right_ = clientBounds.right_;
			}

			cell.bottom_ = cell.top_ + rowHeights[row];

			if ( (row == (rowCount-1)) && maximizeLastRow_ ) {
				cell.bottom_ = clientBounds.bottom_;
			}

			control->setBounds( &cell );


			col ++;



			if ( col >= colCount ) {
				col = 0;
				tween = 0;

				cell.offset( 0, rowHeights[row] + rowSpacerHeight_ );

				cell.left_ = clientBounds.left_;

				cell.right_ = cell.left_ + columns_[col];

				row ++;
			}
			else {
				cell.offset( cell.getWidth() + columnTweens_[tween], 0 );
				tween ++;
			}


			++ it;
		}
	}	

	bool getMaximizeLastRow() {
		return maximizeLastRow_;
	}

	void setMaximizeLastRow( const bool& val ) {
		maximizeLastRow_ = val;
	}

	void setRowSpacerHeight( const double& val ) {
		rowSpacerHeight_ = val;
	}

	double getRowSpacerHeight() {
		return rowSpacerHeight_;
	}



		
	bool generatePropertyValue( const String& fullPropertyName, Property* property, VariantData* value, String& strValue )	{
		String lcPropName = StringUtils::lowerCase(fullPropertyName);
		if ( lcPropName == CONTAINER_MAXROWHEIGHT ) {
			if ( maxRowHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
				strValue = CC_WINDOW_BORDER;
				return true;
			}
			else if ( maxRowHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
				strValue = CC_CONTAINER_BORDER;
				return true;
			}
			else if ( maxRowHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) ) {
				strValue = CC_CONTROL_VSPACE;
				return true;
			}
			else if ( maxRowHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer ) ) {
				strValue = CC_INFO_TOPSPACE;
				return true;
			}
			else if ( maxRowHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlBottomSpacer ) ) {
				strValue = CC_INFO_BOTTOMSPACE;
				return true;
			}		
		}
		else if ( lcPropName == CONTAINER_ROWSPACERHEIGHT ) {
			if ( rowSpacerHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtWindowBorderDelta ) ) {
				strValue = CC_WINDOW_BORDER;
				return true;
			}
			else if ( rowSpacerHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtContainerBorderDelta ) ) {
				strValue = CC_CONTAINER_BORDER;
				return true;
			}
			else if ( rowSpacerHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtControlVerticalSpacing ) ) {
				strValue = CC_CONTROL_VSPACE;
				return true;
			}
			else if ( rowSpacerHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlTopSpacer ) ) {
				strValue = CC_INFO_TOPSPACE;
				return true;
			}
			else if ( rowSpacerHeight_ == UIToolkit::getUIMetricValue( UIMetricsManager::mtInformationControlBottomSpacer ) ) {
				strValue = CC_INFO_BOTTOMSPACE;
				return true;
			}		
		}

		return StandardContainer::generatePropertyValue( fullPropertyName, property, value, strValue );
	}

protected:

	std::vector<double> columns_;
	std::vector<double> columnTweens_;

	double maxRowHeight_;
	double rowSpacerHeight_;
	bool maximizeLastRow_;
	bool equalizeHeights_;
	bool averageHeights_;
	bool keepControlsWidth_;
};


}; // namespace VCF


#endif //_HORIZONTALLAYOUTCONTAINER_H__

/**
$Id$
*/
