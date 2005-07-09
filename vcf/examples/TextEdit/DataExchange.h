#if     _MSC_VER > 1000
#pragma once
#endif

#ifndef _DATAEXCHANGE_H__
#define _DATAEXCHANGE_H__





template <typename DataType, typename ControlType>
class DataExchangeImpl : public VCF::ObjectWithEvents/*, public DataExchange*/ {
public:
	typedef ControlType Control;
	typedef typename ControlType::BaseType ControlBase;

	typedef DataExchangeImpl<DataType,ControlType> DataExchangeType;

	DataExchangeImpl() : control_(NULL), value_(DataType()){

	}

	virtual ~DataExchangeImpl() {
		control_ = NULL;
	}

	operator DataType () {
		update( true );
		return value_;
	}

	DataExchangeImpl<DataType,ControlType>& operator= ( const DataType& val ) {
		value_ = val;
		update( false );
		return *this;
	}

	operator ControlType* () {
		return control_;
	}

	void onDestroy( VCF::ComponentEvent* e ) {
		update(true);
		control_ = NULL;
	}

	

	DataExchangeImpl<DataType,ControlType>& operator= ( ControlBase* val ) {
		control_ = reinterpret_cast<ControlType*>( val );
		if ( NULL != control_ ) {
			EventHandler* ev = getEventHandler( "DataExchangeType::onDestroy" );
			if ( NULL == ev ) {
				ev = new ComponentEventHandler<DataExchangeType>(this, &DataExchangeType::onDestroy, "DataExchangeType::onDestroy" );
			}
			control_->ComponentDeleted += ev;
			update( false );
		}
		return *this;
	}

	DataExchangeImpl<DataType,ControlType>& operator= ( ControlType* val ) {
		control_ = val;
		if ( NULL != control_ ) {
			EventHandler* ev = getEventHandler( "DataExchangeType::onDestroy" );
			if ( NULL == ev ) {
				ev = new ComponentEventHandler<DataExchangeType>(this, &DataExchangeType::onDestroy, "DataExchangeType::onDestroy" );
			}
			control_->ComponentDeleted += ev;
			update( false );
		}
		return *this;
	}

	ControlType* operator ->() {
		return control_;
	}	

	void update( bool dataFromControl ) {
		if ( NULL != control_ ) {
			if ( dataFromControl ) {
				value_ = control_->getDataValue();
			}
			else {
				control_->setDataValue( value_ );
			}
		}
	}	
	
protected:
	ControlType* control_;	
	DataType value_;
};



template <typename Base>
class BoolToggleButtonControl : public Base {
public:
	typedef Base BaseType;

	bool getDataValue() {
		return Base::isChecked();
	}

	void setDataValue( bool val ) {
		Base::setChecked( val );
	}
};


template <typename Base>
class StringComboBoxControl : public Base {
public:
	typedef Base BaseType;

	VCF::String getDataValue() {
		return Base::getCurrentText();
	}

	void setDataValue( const VCF::String& val ) {
		Base::setCurrentText( val );
	}
};


template <typename Base>
class StringEditControl : public Base {
public:
	typedef Base BaseType;

	VCF::String getDataValue() {
		return Base::getTextModel()->getText();
	}

	void setDataValue( const VCF::String& val ) {
		Base::getTextModel()->setText( val );
	}
};


template <typename Base, typename Val>
class NumberEditControl : public Base {
public:
	typedef Base BaseType;

	Val getDataValue() {
		VariantData d( Val() );
		d.setFromString( Base::getTextModel()->getText() );		
		return d;
	}

	void setDataValue( const Val& val ) {
		
		Base::getTextModel()->setText( StringUtils::toString(val) );
	}
};


template <typename Base>
class StringsComboBoxControl : public Base {
public:
	typedef Base BaseType;
	std::vector<VCF::String> getDataValue() {

		std::vector<VCF::String> result;
		VCF::ListModel* lm = Base::getListModel();
		VCF::Enumerator<VCF::ListItem*>* items = lm->getItems();

		while ( items->hasMoreElements() ) {
			VCF::ListItem* item = items->nextElement();
			result.push_back( item->getCaption() );
		}		

		std::vector<VCF::String>::iterator found = std::find( result.begin(), result.end(), Base::getCurrentText() );
		if ( found == result.end() ) {
			result.insert( result.begin(), Base::getCurrentText() );
		}
		return result;
	}

	void setDataValue( const std::vector<VCF::String>& val ) {
		VCF::ListModel* lm = Base::getListModel();
		Base::getViewModel()->empty();
		if (!val.empty() ) {			

			std::vector<VCF::String>::const_iterator it = val.begin();
			while ( it != val.end() ) {
				if ( !(*it).empty() ) {
					ListItem* item = new DefaultListItem();
					item->setCaption( *it );
					lm->addItem( item );
				}
				it ++;
			}
			Base::setCurrentText( val[0] );
		}
	}
};


template <typename Base>
class StringsListBoxControl : public Base {
public:
	typedef Base BaseType;
	std::vector<VCF::String> getDataValue() {

		std::vector<VCF::String> result;
		VCF::ListModel* lm = Base::getListModel();
		VCF::Enumerator<VCF::ListItem*>* items = lm->getItems();

		while ( items->hasMoreElements() ) {
			VCF::ListItem* item = items->nextElement();
			result.push_back( item->getCaption() );
		}
		
		return result;
	}

	void setDataValue( const std::vector<VCF::String>& val ) {
		VCF::ListModel* lm = Base::getListModel();
		Base::getViewModel()->empty();
		if (!val.empty() ) {			

			std::vector<VCF::String>::const_iterator it = val.begin();
			while ( it != val.end() ) {
				if ( !(*it).empty() ) {
					ListItem* item = new DefaultListItem();
					item->setCaption( *it );
					lm->addItem( item );
				}
				it ++;
			}			
		}
	}
};



template <typename Base>
class IntegerListviewControl : public Base {
public:
	typedef Base BaseType;
	long getDataValue() {

		long result = 0;
		VCF::ListModel* lm = Base::getListModel();
		VCF::Enumerator<VCF::ListItem*>* items = lm->getItems();
		VCF::ListItem* selectedItem = Base::getSelectedItem();
		
		if ( NULL == selectedItem ) {
			return -1;
		}

		while ( items->hasMoreElements() ) {
			VCF::ListItem* item = items->nextElement();
			if ( selectedItem == item ) {
				break;
			}
			result ++;
		}
		
		return result;
	}

	void setDataValue( const long& val ) {
		VCF::ListModel* lm = Base::getListModel();
		VCF::Enumerator<VCF::ListItem*>* items = lm->getItems();

		long index = 0;
		while ( items->hasMoreElements() ) {
			VCF::ListItem* item = items->nextElement();
			if ( index == val ) {
				Base::selectItem( item );
				break;
			}
			index ++;
		}
	}
};



template <typename Base>
class StringKeyValueListviewControl : public Base {
public:
	typedef Base BaseType;
	typedef std::pair<VCF::String,VCF::String> KeyValue;
	typedef std::vector<KeyValue> KeyValueVector;
	KeyValueVector getDataValue() {

		KeyValueVector result;
		
		VCF::ListModel* lm = Base::getListModel();
		VCF::Enumerator<VCF::ListItem*>* items = lm->getItems();		
		
		while ( items->hasMoreElements() ) {
			VCF::ListItem* item = items->nextElement();
			
			KeyValue val( item->getCaption(),item->getSubItem(0)->getCaption() );

			result.push_back(val);			
		}
		
		return result;
	}

	void setDataValue( const KeyValueVector& val ) {
		VCF::ListModel* lm = Base::getListModel();
		Base::getViewModel()->empty();
		
		KeyValueVector::const_iterator it = val.begin();
		while ( it != val.end() ) {
			const KeyValue& kv = *it;
			VCF::ListItem* item = Base::addItem( kv.first );
			item->addSubItem( kv.second, NULL );

			it ++;
		}		
	}
};

typedef DataExchangeImpl<bool, BoolToggleButtonControl<VCF::CheckBoxControl> > StdBoolType;
typedef DataExchangeImpl<bool, BoolToggleButtonControl<VCF::RadioButtonControl> > StdExclusiveBoolType;

typedef DataExchangeImpl<VCF::String, StringComboBoxControl<VCF::ComboBoxControl> > StdStringChoiceType;

typedef DataExchangeImpl<std::vector<VCF::String>, StringsComboBoxControl<VCF::ComboBoxControl> > StdStringsChoiceType;

typedef DataExchangeImpl<VCF::String, StringEditControl<VCF::TextControl> > StdStringEditType;

typedef DataExchangeImpl<std::vector<VCF::String>, StringsListBoxControl<VCF::ListBoxControl> > StdStringsType;

typedef DataExchangeImpl<int, NumberEditControl<VCF::TextControl,int> > StdIntEditType;
typedef DataExchangeImpl<double, NumberEditControl<VCF::TextControl,double> > StdDoubleEditType;

typedef DataExchangeImpl<long,IntegerListviewControl<VCF::ListViewControl> > StdIntListViewType;
typedef DataExchangeImpl<std::vector<std::pair<VCF::String,VCF::String> >, StringKeyValueListviewControl<VCF::ListViewControl> > StdStringKeyValType;

#endif //_DATAEXCHANGE_H__


