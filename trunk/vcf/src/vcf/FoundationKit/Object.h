#ifndef _VCF_OBJECT_H__
#define _VCF_OBJECT_H__
//Object.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF{


class Class;
class Mutex;

#define OBJECT_CLASSID		"ED88C099-26AB-11d4-B539-00C04F0196DA"

/**
*Base class for entire Visual Component Framework.
*New as of July 5,2001, Object will also support
*refcounting for those who need this kind of support.
*There are several places in the ApplicationKit that will need to make use
*of this fairly soon.
*<p>
*Also Object supports a new technique for destroying Object derived instances.
*In general, in C++, when creating a destroying an object instance on the heap (free-store)
*you would use the operator delete() function. This is being phased out in the VCF
*for a variety of reasons, in favor of a different scheme.
*Destroying the memory now happens in two ways: The first is the equivalent of the operator delete()
*call. This involves calling the objects free() method, which will call the virtual destroy() method
*before calling operator delete() on itself;
*The second way an object can be destroyed is if it's refcount drops to 0, at which point the object's
*free() method will be invoked. Calling the object's release() method decrements the reference count
*on the object.
*By default if an obejct is created on the heap via new, and no one addref()'s it, then a
*single call to the release() method will free up it's memory.
*</p>
*<p>
*<code>destroy()</code> is a virtual method, where common shared cleanup may take place. Because this
*is called before the delete() method, it is still safe to call virtual methods and have them
*execute correctly (in C++ virtual calls inside of a constructor or destructor are not allowed
*and if made then the behaviour is undefined).
*<p>
*Classes which are heap based (such as all of the UI classes that derive from Component) should
*define their destructor as having protected access. In addition the majority of the cleanup code
*should be placed in the overridden <code>destroy()</code> method as opposed to the class destructor.
*Anything that requires method calls to other object or the class itself (particularly if the method
*is a virtual one) should be moved to the
*</p>
*<p>
*Semantics of the addRef/release usage are as follows:
*An object's refcount indicates "ownership " of the object. In other words, the "owner" of the
*object is responsible for releasing it's hold on the object, thus decrementing the objects
*refcount, which, when reduced to 0, causes the object to be deleted. This is also known as
*a strong reference to an object, as opposed to a weak reference where the "owner" doesn't
*claim any responsibility over the object.
*
*Note that this whole scheme is aimed at heap based objects. Many objects that are created on the stack
*do not need this. For example, common utility objects like Rect or Point do not need this - they
*can be created on the stack.
*/
class FOUNDATIONKIT_API Object {
public:
	Object();

	virtual ~Object();

	virtual void init();

	/**
	*call this method to free up the memory of the class
	*for heap based objects
	*/
	void free();

	/**
	*increments the reference count of the object
	*@param Object* the optional owner of the new referenced object
	*for use in future, more sophisticated refcounting schemes
	*@return unsigned long the current reference count of the object
	*/
	virtual unsigned long addRef(Object* owner=NULL);

	/**
	*decrements the reference count of the object
	*@param Object* the optional owner of the new referenced object
	*for use in future, more sophisticated refcounting schemes
	*when the refCount_ drops to 0 the object is destroyed
	*/
	virtual unsigned long release(Object* owner=NULL);

	/**
	*returns the number of outstanding references for this object
	*/
	unsigned long getRefCount(){
		return refCount_;
	}

    /**
     * returns a string representation of the object
     */
    virtual String toString();

    /**
     * returns the class name of the object.
     */
    String getClassName();

	/**
	This determines if object is equal to this
	the equivalent of operator ==()
	*/
	virtual bool isEqual( Object* object ) const {
		return ( object == this );
	};

	/**
	Copies the data from source to this object.
	This is the equivalent of operator=()
	*/
	virtual void copy( Object* source ) {};

	/**
	Makes a complete clone of this object.
	A typical implementation might be:
	<pre>
	virtual Object* clone( bool deep ) {
		return new MyObject( *this );
	}
	</pre>
	In which the implementer simply creates a new instance on the heap
	and calls the copy constructor.
	Objects which support cloning <b>should</b> also have a copy
	constructor defined as well.

	@param bool deep if deep is true then any object instances
	that this object owns should probably be cloned as well, with
	full new copies made. Otherwise it would be acceptable to simply
	copy the pointer values. The default value is for deep cloning to
	be false.
	@return Object a new instance that should be an copy of this. If
	the object doesn't support cloning the return will value will be NULL.
	*/
	virtual Object* clone( bool deep=false ) {
		return NULL;
	};

	/**
	*returns the RTTI Class instance associated object
	*of this type
	*/
	Class* getClass() ;

	/**
	*returns a hash value that represents the object instance
	*/
	virtual unsigned long hash();

	/**
	*Ptr is a smart pointer class for use with refcounted objects.
	*This class should <b><i>NEVER</i></b> be created on the heap,
	*instead create instances on the stack.
	*/
	template <class OBJECT_TYPE> class Ptr {
	public:
		Ptr(){
			ptr_ = NULL;
		}

		/**
		*constructor for the Ptr passing in a
		*new instance of an OBJECT_TYPE
		*/
		Ptr( OBJECT_TYPE* o ){
			ptr_ = o;
		}

		/**
		*allows access to the underlying pointer
		*/
		OBJECT_TYPE* operator ->() {
			return ptr_;
		}

		/**
		*conversion operator
		*@return OBJECT_TYPE returns the underlying pointer
		*/
		operator OBJECT_TYPE* () {
			return ptr_;
		}

		/**
		*equality operator.
		*Compares the object passed in with the internal
		*object.
		**@param OBJECT_TYPE the object to compare with. Current
		*comparison is only a simple pointer comparison. This may
		*become more sophisticated.
		*/
		bool operator ==( OBJECT_TYPE* object ) const	{
			return 	ptr_ == object;
		}

		/**
		*assignment operator.
		*assigns a new object value to the Ptr instance.
		*/
		Ptr& operator= ( OBJECT_TYPE* o ) {
			ptr_ = o;
			return *this;
		}

		bool operator !()	{
			return (NULL == ptr_ ) ? true: false;
		}

		OBJECT_TYPE& operator *() {
			return *ptr_;
		}

		OBJECT_TYPE** operator &( ) {
			return &ptr_;
		}

		virtual ~Ptr(){
			if ( NULL != ptr_ ){
				ptr_->release();
			}
		}
	private:
		OBJECT_TYPE* ptr_;
	};


	/**
	indicates whether or not debug memory should be tracked. Note
	that debug memory is tracked <b>only</b> in debug builds
	(meaning the VCF has been compiled with the _DEBUG symbol
	defined). Memory tracking is turned off for release builds.
	@param bool if this is true, then memory will be tracked, and when
	the FoundationKit::terminate() is called, the system will
	check how many outstanding objects (i.e. any class instance that
	derives from VCF::Object directly or indirectly) there are.
	It will then perform a diagnostic dump, displaying the memory
	address and the class name of the object instance
	*/
	static void trackDebugMemory( const bool& trackMemory );

	/**
	returns whether or not debug memory tracking is on
	@return bool true if debug memory tracking is turned on, otherwise
	false
	*/
	static bool isDebugMemoryTracked();

	/**
	returns the total number of objects currently allocated. Only
	meaningful for _DEBUG builds with memory tracking turned on.
	@return ulong32 if debug memory tracking is turned on, and the
	_DEBUG symbol is defined, then this value will be the total count
	of object instances that are currently allocated. For any other
	conditions it will return 0.
	*/
	static ulong32 objectAllocationCount();
#ifdef _VCF_DEBUG_NEW
	public:

	static Mutex* accessMutex_;

	static void dumpDebugInfo();

	//we're gonna declare operator new here so we can track
	//VCF related memory leaks
	void* operator new( size_t allocationSize );

	void operator delete( void* objectPointer );

	void* operator new( size_t allocationSize, void* p ) {
		return ::operator new(  allocationSize, p );
	}

#if !defined(VCF_GCC) && !defined(VCF_BCC)
	void operator delete( void* objectPointer, void* p ) {
		::operator delete( objectPointer, p );
	}
#endif


	protected:

	class DebugInfo {
	public:
		DebugInfo() : objectAllocationSize_(0), objAddress_(0) {

		}
		size_t objectAllocationSize_;
		unsigned long objAddress_;
	};

	static std::map<unsigned long,DebugInfo> debugAllocationMap;
	static bool trackingDebugMemory;

#endif //_VCF_DEBUG_NEW

protected:
	/**
	*called by the free() method. Should be overriden
	*and any clean up code performed here
	*/
	virtual void destroy();

	unsigned long refCount_;
private:

};

};


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:14  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/30 17:28:40  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.3  2004/06/06 07:05:32  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:12  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:40  ddiego
*migration towards new directory structure
*
*Revision 1.22.4.1  2004/04/26 21:58:20  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.22  2003/12/18 05:15:57  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.21.2.3  2003/12/02 22:11:01  ddiego
*some minor changes to support Actions. Still not done yet.
*
*Revision 1.21.2.2  2003/10/23 04:24:50  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.21.2.1  2003/09/16 02:41:54  ddiego
*added a small fix for adding a mutex to prevent multithreaded programs from
*crashing in debug mode.
*
*Revision 1.21  2003/08/09 02:56:42  ddiego
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
*Revision 1.20.2.1  2003/06/13 03:02:35  ddiego
*bug fixes for
*585238:	Modal dialog which makes a modal Dialog
*585239:	Painting weirdness in a modal dialog
*also some clean up of miscellaneous debug trace statements
*and implemented task
*79266 - change DebugInfo to be stack based
*
*Revision 1.20  2003/05/17 20:37:03  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.19.2.1  2003/03/12 03:09:40  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.19  2003/02/26 04:30:38  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.18.12.1  2002/11/28 05:12:04  ddiego
*modifications to allow the VCF to compile with MinGW. This also cleans up
*some warnings with GCC - should improve the linux side as well.
*In addition this checkin includes new files for building the VCF under
*the DevC++ IDE. these are in the vcf/build/devcpp directory.
*
*Revision 1.18  2002/06/01 21:44:20  ddiego
*fixed goof in Object.h from port to linux - made a mistake in one of the operator delete
*overloads - correected now
*
*Revision 1.17  2002/05/26 21:19:54  ddiego
*added and fixed xmake makefiles for FoundationKit and for the RTTI test
*so that this now runs under linux (should work fine for Solaris as well).
*Made some changes to Object for removing one of the operator delete() when
*using GCC
*Other minor changes to files to ensure that they end with a carriage return
*
*Revision 1.16  2002/05/09 03:10:42  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.15.4.3  2002/04/27 15:42:45  ddiego
*removed ApplicationKit.h and optimized header includes as
*well as adding better include guard support
*
*Revision 1.15.4.2  2002/03/26 02:35:33  ddiego
*fixes include removing the __declspec(export) from the various template based
*classes in the VCF. Aparrently this causes problems in VC7.
*Also include a feature for memory tracking in debug mode.
*
*Revision 1.15.4.1  2002/03/20 21:56:55  zzack
*Changed Include Style of FoundationKit
*
*Revision 1.15  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*                                                                        _DEBUG
*/


#endif // _VCF_OBJECT_H__


