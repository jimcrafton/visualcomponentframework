#ifndef _VCF_ENUMOBJECT_H__
#define _VCF_ENUMOBJECT_H__
//EnumObject.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#pragma warning (disable : 4786) //vector warnings about string too long...

namespace VCFCOM{

/**
*Template class to make it easy to create IEnumXXX objects
*/



template <class T> class EnumObject {
	public:
		EnumObject(){
			currentPos_ = 0;
		};

		EnumObject( const EnumObject& enumObj ){
			items_ = enumObj.items_;
			currentPos_ = enumObj.currentPos_;
			unsigned long skipped = currentPos_;
			if ( skipped > 0 ) {
				itemIterator_ = items_.begin();
				while (  (itemIterator_ != items_.end()) && (skipped > 0) ){
					itemIterator_++;
					skipped--;
				}
			}
		};


		virtual ~EnumObject(){};

		/**
		*Use this function to add data to initialize the enum object
		*/
		virtual void add( T item ){
			items_.push_back( item );
			//StringUtils::traceWithArgs( "added %s, now have %d items\n",
			//							typeid(T).name(), items_.size() );
		};

		void initList() throw ( VCF::CantCreateObjectException ){

			itemIterator_ = items_.begin();
		};

		/**
		*IEnumXXX members
		*documentation from the Win32 SDK (MSDN October 1999)
		*/
		/**
		*Retrieves the next elementsRequested items in the enumeration sequence.
		*If there are fewer than the requested number of elements left in the sequence,
		*it retrieves the remaining elements. The number of elements actually retrieved
		*is returned through elementsFetched (unless the caller passed in NULL for that parameter).
		*@param ULONG elementsRequested - number of elements to fetch
		*@param T *elementList - an array of elements of type <T>
		*@param ULONG *elementsFetched - the numbers of items in the elementList array
		*/
        HRESULT _Next( ULONG elementsRequested, T *elementList, ULONG *elementsFetched ){

			HRESULT result = S_FALSE;
			unsigned long fetchCount = 0;
			//apparently *SOME* apps will send in a NULL elementsFetched
			//(i.e. MS DataObjectViewer) so we can't return
			//an error here, instead jsut ignore the elementsFetched
			//and don't assign a value to it
			if ( NULL == elementsFetched ){
				if ( elementsRequested > 0 ){

				}
			}

			if ( (NULL == elementList) || (itemIterator_ == items_.end()) ){
				if ( NULL != elementsFetched ) {
					*elementsFetched = 0;
				}

				result = S_FALSE;
			}
			else {
				while ( (itemIterator_ != items_.end()) && (elementsRequested > 0) ){
					currentPos_ ++;
					*elementList = *itemIterator_;
					elementList++;
					itemIterator_++;

					fetchCount++;
					elementsRequested--;
				}
				if ( NULL != elementsFetched ) {

					*elementsFetched = fetchCount;
				}
				result = S_OK;
			}

			return result;
		};

		/**
		*Skips over the next specified number of elements in the enumeration sequence.
		*@param ULONG elementsToSkip - the number of items to skip over
		*/
        HRESULT _Skip( ULONG elementsToSkip ){


			HRESULT result = S_FALSE;
			if ( itemIterator_ != items_.end() ){
				while ( (itemIterator_ != items_.end()) && (elementsToSkip > 0) ){
					elementsToSkip--;
					itemIterator_++;
					currentPos_++;
				}
				result = S_OK;
			}
			return result;
		};

		/**
		*Resets the enumeration sequence to the beginning.
		*/
        HRESULT _Reset(void){

			itemIterator_ = items_.begin();
			return S_OK;
		};


	protected:
		#if defined(VCF_MINGW)  /* mingw doesn't understand vector<_typename_ T> */
		std::vector<T> items_;
		_typename_ std::vector<T>::iterator itemIterator_;
		#else
		std::vector<_typename_ T> items_;
		_typename_ std::vector<_typename_ T>::iterator itemIterator_;
		#endif
		unsigned long currentPos_;

};

};


#endif // _VCF_ENUMOBJECT_H__

/**
$Id$
*/
