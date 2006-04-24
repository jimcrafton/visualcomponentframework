//WorkingWithEnumerators.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/FoundationKit/FoundationKit.h"

using namespace VCF;


/**
This example will exaplain how to use the
VCF::Enumerator class.
An Emuerator is simply a virtual class that wraps
around a collection and provides a standard interface
for iterating through the collection, without worrying
about the specifics of the collection type.

For example you might have a collection class based on a
std::vector. If you exposed the collection type directly, then
any changes you made to would have to be reflected in all cases
where you iterate through the collection. However, if you
use an Enumerator, this wraps the collection type, and you can then
transparently change the collection type, say from a
std::vector, to a std::list, and any code using the Enumerator
will remain unaffected.
*/


/**
Our first example will show how to use an Enumerator
as a result of making a call to a VCF class.
We'll call the ClassRegistry, and get a list of
all the classes that have been registered with it.
*/
void example1()
{
	/**
	This returns you an Enumerator of classes.
	The Enumerator is a template class, and in this
	case it represents a collection of type VCF::Class
	objects.
	*/
	Enumerator<Class*>* classes = ClassRegistry::getClasses();

	/**
	The typical usage is in a while loop,
	where the test condition is whether or
	not the Enumerator in question has any
	more elements. This is achieved by calling
	the Enumerator's hasMoreElements() method,
	which will return true as long as there
	are more elements to enumerater through.
	*/

	while ( classes->hasMoreElements() ) {
		/**
		To get the current element in the
		enumeration, call the Enumerator's
		nextElement() method, which will return a
		reference to the current element.
		In our case the enumeration type is a
		Class pointer, so we'll receive a pointer
		to a current VCF::Class instance.
		*/
		Class* clazz = classes->nextElement();

		/**
		print out the class name
		*/
		System::println( clazz->getClassName() );
	}
}


/**
The next example will show how to reset the Enumerator
*/
void example2()
{
	/**
	Get the classes enumerator
	Whenever you call a method that returns an Enumerator,
	it is safe to assume that the Enumerator is current
	"rewound" to the beginning of it's collection.
	*/
	Enumerator<Class*>* classes = ClassRegistry::getClasses();

	/**
	Lets look at the first item
	*/
	System::print( "The first item is : " );
	Class* clazz = classes->nextElement();

	System::println( clazz->getClassName() );

	/**
	and now the second item
	*/
	clazz = classes->nextElement();

	System::print( "The second item is : " );
	System::println( clazz->getClassName() );

	while ( classes->hasMoreElements() ) {
		/**
		get the next element
		*/
		Class* clazz = classes->nextElement();

		/**
		print out the class name
		*/
		System::println( clazz->getClassName() );
	}

	/**
	Now let's "reset" the enumerator - this will set the current item
	in the enumerator back to the beginning.
	*/


	classes->reset();

	System::println( "classes Enumerator reset." );

	/**
	Now print out the list again.
	*/
	while ( classes->hasMoreElements() ) {
		/**
		get the next element
		*/
		Class* clazz = classes->nextElement();

		/**
		print out the class name
		*/
		System::println( clazz->getClassName() );
	}
}


/**
This example will demonstrate enumerating backwards
in an enumeration. By default when you call Enumerator::reset()
or Enumerator::hasMoreElements() the behaviour is to assume
that you're moving forward through the collection.
This will demonstrate the reverse of that
*/
void example3()
{
	Enumerator<Class*>* classes = ClassRegistry::getClasses();

	/**
	loop backwards. To do this, reset the enumerator, passing
	in true, to indicate you want to go backwards
	*/
	classes->reset( true );

	/**
	Now print out the list.
	Note that we *must* use true in our call to
	hasMoreElements() to match the backwards reset
	above.
	*/
	while ( classes->hasMoreElements(true) ) {
		/**
		get the next element
		*/
		Class* clazz = classes->prevElement();

		/**
		print out the class name
		*/
		System::println( clazz->getClassName() );
	}

}

/**
Here we see an example of how to create an enumerator.
*/

void example4()
{
	/**
	First we define a vector of strings
	*/
	std::vector<String> strings;
	/**
	Then we define a EnumeratorContainer, a wrapper around the
	string vector
	*/
	EnumeratorContainer<std::vector<String>,String> stringContainer;

	/**
	The the container is initialized by passing in the string vector
	*/
	stringContainer.initContainer( strings );


	/**
	Add 4 strings
	*/
	strings.push_back( "1" );
	strings.push_back( "2" );
	strings.push_back( "3" );
	strings.push_back( "4" );

	/**
	Now retrieve the enumerator pointer from the container.
	*/
	Enumerator<String>* stringEnum = stringContainer.getEnumerator();


	/**
	Enumerate all the elements going forward
	*/
	while ( stringEnum->hasMoreElements() ) {
		/**
		get the next element
		*/
		String s = stringEnum->nextElement();


		System::println( s );
	}

	/**
	Reset all the elements going backward
	*/
	stringEnum->reset( true );

	/**
	Enumerate all the elements going backward
	*/
	while ( stringEnum->hasMoreElements(true) ) {
		/**
		get the next element
		*/
		String s = stringEnum->prevElement();


		System::println( s );
	}

}

int main( int argc, char** argv ){

	FoundationKit::init( argc, argv );

	example1();

	example2();

	example3();

	example4();

	FoundationKit::terminate();
	return 0;
}


/**
*CVS Log info
*$Log$
*Revision 1.3  2004/08/07 02:47:42  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.2.4.4  2004/04/29 03:40:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*/


