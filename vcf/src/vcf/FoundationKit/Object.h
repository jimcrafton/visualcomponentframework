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
\class Object Object.h "vcf/FoundationKit/Object.h"
Base class for the entire Visual Component Framework.
*/
class FOUNDATIONKIT_API Object {
public:

	virtual ~Object();	

    /**
    returns a string representation of the object
     */
    virtual String toString() const;

	/**
	provides a simple to initialize the object from a string.
	*/
	virtual void setFromString( const String& val ) {}

    /**
    returns the class name of the object.
    */
    String getClassName() const;

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
	\code
	virtual Object* clone( bool deep ) {
		return new MyObject( this );
	}
	\endcode
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
	virtual Object* clone( bool deep=false ) const {
		return NULL;
	};

    Object& operator=(const Object &rhs) { return *this; }
	/**
	returns the RTTI Class instance associated object
	of this type
	*/
	Class* getClass() const ;

	/**
	returns a hash value that represents the object instance
	*/
	virtual uintptr hash() const ;

	/**
	Returns the size of this instance. This may be signifigantly bigger
	than, say, sizeof(Object). For example, if your class derives from
	Object, and has list of other objects, (such as a Component), and various
	other bits, then these may not all show up in the value returned 
	by sizeof(). Take a vector, a vector of ints or a vector of Object uses
	up 16 bytes, as reported by sizeof(). But the \em actual memory used
	will be quite different, partially dependent on how many items are 
	in the vector. Hence the existence of this function, which allows 
	people to implement something that does a better job of reporting 
	how much memory the object in quest is actually using. The default 
	implementation simply returns sizeof(Object).
	*/
	virtual uint64 sizeOf() const {
		return sizeof(Object);
	}
	

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
	@return uint32 if debug memory tracking is turned on, and the
	_DEBUG symbol is defined, then this value will be the total count
	of object instances that are currently allocated. For any other
	conditions it will return 0.
	*/
	static uint32 objectAllocationCount();

	uint32 totalAllocatedObjectMemory();
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
		uintptr objAddress_;
	};

	static std::map<uint32,DebugInfo> debugAllocationMap;
	static bool trackingDebugMemory;

#endif //_VCF_DEBUG_NEW

protected:
	
private:

};

/**
\class HeapObject Object.h "vcf/FoundationKit/Object.h"
Object with refcounting methods that originally belonged to Object class.  This enables
the Object class to live peacefully on the stack.  HeapObject should always be created
on the heap!
*/
class FOUNDATIONKIT_API HeapObject: public Object, public RefCounted {
public:
	HeapObject();
    HeapObject(const HeapObject &obj);
	HeapObject& operator= (const HeapObject &obj){return *this;} // don't copy the refcount

	/**
	*increments the reference count of the object
	@return long the current reference count of the object
	*/
    virtual long addRef();

	/**
	decrements the reference count of the object
	@return long the current reference count of the object, if 0 is returned then object has been deleted
	*/
    virtual long release();

	/**
	returns the number of outstanding references for this object
	*/
    virtual long getRefCount() const{
		return refCount_;
	}

	/**
    returns a string representation of the object
     */
	virtual String toString() const;

protected:

	AtomicCount refCount_;
};

}


#endif // _VCF_OBJECT_H__

/**
$Id$
*/
