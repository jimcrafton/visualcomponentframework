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


/**
*CVS Log info
*$Log$
*Revision 1.3  2006/04/07 02:35:23  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.2.6.1  2005/10/07 19:31:53  ddiego
*merged patch 1315995 and 1315991 into dev repos.
*
*Revision 1.2  2004/08/07 02:49:08  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.2  2004/04/29 03:43:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 00:28:16  ddiego
*migration towards new directory structure
*
*Revision 1.4.2.1  2004/04/26 21:58:42  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.4  2004/04/03 15:48:41  ddiego
*Merged over code from the 0-6-3 branch.
*

*Revision 1.2.4.1  2004/03/21 00:39:22  ddiego
*merged vc7.1 changes into dev branch
*
*Revision 1.3  2004/02/15 21:55:36  ddiego
*Added changes for vc7.1 compiler, many thanks to Raghavendra Chandrashekara for helping with this.
*
*Revision 1.2  2003/08/09 02:56:44  ddiego
*merge over from the devmain-0-6-1 branch
*Changes
*Features:
*-Added additional implementation to better support the MVC architecture in
*the VCF
*
*-Added a Document/View architecure that is similar to MFC's or NextSteps's
*Doc/View architectures
*
*-Integrated the Anti Grain Graphics library into the GraphicsKit. There is
*now basic support for it in terms of drawing vector shapes
*(fills and strokes). Image support will come in the next release
*
*-Added several documented graphics tutorials
*
*Bugfixes:
*
*[ 775744 ] wrong buttons on a dialog
*[ 585239 ] Painting weirdness in a modal dialog ?
*[ 585238 ] Modal dialog which makes a modal Dialog
*[ 509004 ] Opening a modal Dialog causes flicker
*[ 524878 ] onDropped not called for MLTcontrol
*
*Plus an issue with some focus and getting the right popup window to activate
*has also been fixed
*
*Revision 1.1.2.2  2003/05/25 20:35:29  ddiego
*fixed another bug related to drag drop. This time in allowing the
*IEnumFORMATETC impl to ignore NULL value passed in instead of
*returning an error.
*
*Revision 1.1.2.1  2003/05/25 19:07:11  ddiego
*fixed bug [ 524878 ] onDropped not called for MLTcontrol. This
*was due to errors in the drag-drop implementation for WIn32 and is
*now fixed.
*Also cleaned up the drag-drop implementation and moved/deleted a number of
*irrelevant files for COM support. The vcf/include/com and vcf/src/COM
*directories are now gotten rid of.
*
*Revision 1.8  2003/05/17 20:36:59  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.7.2.2  2003/03/23 03:23:43  marcelloptr
*3 empty lines at the end of the files
*
*Revision 1.7.2.1  2003/03/12 03:09:11  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.7  2003/02/26 04:30:35  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.6.14.3  2003/01/08 00:19:42  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.6.14.2  2002/12/27 23:04:29  marcelloptr
*Improved macros for automatic import/export of libraries. - Warning fixes. - Other Minor Changes.
*
*Revision 1.6.14.1  2002/12/02 00:38:34  ddiego
*more fixes to get the ApplicationKit to compile under mingw. Everything now
*compiles OK at this point.
*
*Revision 1.6  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.5.4.2  2002/04/27 15:52:16  ddiego
*Changed a bunch of files include and made it a bit faster and added better include
*guards in the common headers
*
*Revision 1.5.4.1  2002/04/08 20:55:29  zzack
*changed include style
*
*Revision 1.5  2002/01/24 01:46:45  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_ENUMOBJECT_H__


