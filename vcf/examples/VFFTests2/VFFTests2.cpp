////VFFTests2.cpp

#include "vcf/FoundationKit/FoundationKit.h"
#include "vcf/FoundationKit/VFFOutputStream.h"
#include "vcf/FoundationKit/VFFInputStream.h"

#include "vcf/FoundationKit/RTTIMacros.h"


using namespace VCF;

class Stuff : public Object {
public:
	_class_rtti_( Stuff, "VCF::Object", "5464565465465465" )		
		_property_(int,"width",getWidth,setWidth,"")
		_property_(double,"color",getColor,setColor,"")
	_class_rtti_end_

	int getWidth() {
		return width;
	}
	void setWidth( const int& val ) {
		width = val;
	}

	double getColor() {
		return color;
	}
	void setColor( const double& val ) {
		color = val;
	}

	int width;
	double color;
};


class CollT1 : public Component {
public:
	_class_rtti_( CollT1, "VCF::Component", "093845lrotelrtkjl" )
		_property_array_( int, "items", getItem,setItem,addItem,insertItem,removeItem,getItemSize, "" )				
		//_property_collection_( double, String, "stuff", getStuff,setStuff,addStuff,insertStuff,removeStuff,getStuffSize, "" )
		_property_obj_array_( Stuff, "stuff", getStuff,setStuff,addStuff,insertStuff,removeStuff,getStuffSize, "" )
	_class_rtti_end_



	std::vector<int> items;

	std::vector<Stuff*> stuff;

	void addItem( int val ) {
		items.push_back( val );
	}

	void insertItem( const uint32& i, int val ){
		items.insert( items.begin() + i, val );
	}

	uint32 getItemSize() {
		return items.size();
	}

	void removeItem( const uint32& i ) {
		items.erase( items.begin() + i );
	}

	int getItem( const uint32& i ) {
		return items[i];
	}

	void setItem( const uint32& i, int val, bool addMissingValues ) {

		if ( addMissingValues && ((i+1) > items.size()) ) {
			size_t missing = (i+1) - items.size();
			if ( missing > 0 ) {
				items.resize( missing + items.size() );
			}
		}

		items[i] = val;
	}



	void addStuff( Stuff* val ) {
		stuff.push_back( val );
	}

	void insertStuff( const uint32& i, Stuff* val ){
		stuff.insert( stuff.begin() + i, val );
	}

	uint32 getStuffSize() {
		return stuff.size();
	}

	void removeStuff( const uint32& i ) {
		stuff.erase( stuff.begin()+i );
	}

	Stuff* getStuff( const uint32& i ) {
		return stuff.at(i);
	}

	void setStuff( const uint32& i, Stuff* val, bool addMissingValues ) {
		if ( addMissingValues && ((i+1) > stuff.size()) ) {
			size_t missing = (i+1) - stuff.size();
			if ( missing > 0 ) {
				stuff.resize( missing + stuff.size() );
			}
		}

		stuff[i] = val;
	}
};


int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	REGISTER_CLASSINFO(CollT1);
	REGISTER_CLASSINFO(Stuff);
	

	String compStr = "object t1 : CollT1 items[0] = 10 items[1] = 123 end";
	{
		VFFInputStream vis( compStr );
		Component* c = vis.readNewComponent();

		if ( c ) {

			CollT1* t1 = (CollT1*)c;
			for (int i=0;i< t1->items.size();i++ ) {
				System::println( String("Item #") + i + " = " + t1->items[i] );
			}


			c->free();
		}
	}

	compStr = "object t1 : CollT1 stuff[0].width = 100 end";
	{
		VFFInputStream vis( compStr );
		Component* c = vis.readNewComponent();

		if ( c ) {

			CollT1* t1 = (CollT1*)c;
			for (int i=0;i< t1->items.size();i++ ) {
				System::println( String("Item #") + i + " = " + t1->items[i] );
			}

			System::println( String("Num of items ") + t1->stuff.size() );

			c->free();
		}
	}


	FoundationKit::terminate();
	return 0;
}


