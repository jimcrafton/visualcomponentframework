//Proxy.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#include "vcf/RemoteObjectKit/RemoteObjectKit.h"


using namespace VCFRemote;
using namespace VCF;

Proxy::Proxy( Object* localObjectInstance )
{
	this->className_ = "";
	this->classID_ = "";
	this->localObjectInstance_ = localObjectInstance;
	this->isRemote_ = (localObjectInstance_ == NULL);
	if ( NULL != localObjectInstance_ ) {
		Class* clazz = localObjectInstance_->getClass();
		this->className_ = clazz->getClassName();
		this->classID_ = clazz->getID();
		this->instanceID_.setMemAddress( (int)localObjectInstance_ );
	}
}

Proxy::~Proxy()
{
	if ( NULL != localObjectInstance_ ) {
		delete localObjectInstance_;
		localObjectInstance_ = NULL;
	}
}

void Proxy::marshallArguments( const VCF::uint32& argCount,
								VCF::VariantData** arguments,
								VCF::OutputStream* marshallingStream )
{
	/**marshall data as follows
	*number of arguments being sent - int
	*data signature - string
	*data
	*at the moment this does not handle arrays of data
	*/
	marshallingStream->write( (int)argCount );

	for ( int i = 0;i<argCount;i++ ) {
		VariantData* arg = arguments[i];
		switch ( arg->type ) {
			case pdInt : {
				marshallingStream->write( String("i") );
				marshallingStream->write( (int)(*arg) );
			}
			break;

			case pdLong : {
				marshallingStream->write( String("l") );
				marshallingStream->write( (long)(*arg) );
			}
			break;

			case pdULong : {
				marshallingStream->write( String("+l") );
				marshallingStream->write( (long)(*arg) );
			}
			break;

			case pdShort : {
				marshallingStream->write( String("h") );
				marshallingStream->write( (short)(*arg) );
			}
			break;

			case pdChar : {
				marshallingStream->write( String("c") );
				marshallingStream->write( (char)(*arg) );
			}
			break;

			case pdDouble : {
				marshallingStream->write( String("d") );
				marshallingStream->write( (double)(*arg) );
			}
			break;

			case pdFloat : {
				marshallingStream->write( String("f") );
				marshallingStream->write( (float)(*arg) );
			}
			break;

			case pdBool : {
				marshallingStream->write( String("b") );
				marshallingStream->write( (bool)(*arg) );
			}
			break;

			case pdString : {
				marshallingStream->write( String("s") );
				marshallingStream->write( (String)(*arg) );
			}
			break;

			case pdObject : {
				Object* obj = *arg;
				Persistable* persistentObj = dynamic_cast<Persistable*>(obj);
				if ( NULL != persistentObj ) {
					marshallingStream->write( String("o") );
					marshallingStream->write( obj->getClassName() );
					marshallingStream->write( persistentObj );
				}
				else {
					//throw exception
				}
			}
			break;
		}
	}
}

VariantData* Proxy::invoke( const VCF::String& methodName, const uint32& argCount, VariantData** arguments )
{
 	VariantData* result = NULL;

	if ( NULL != localObjectInstance_ ) {
		Class* clazz = localObjectInstance_->getClass();
		Method* methodToInvoke = clazz->getMethod( methodName );
		if ( NULL != methodToInvoke ) {
			result = methodToInvoke->invoke( arguments );
		}
	}
	else  {
		BasicOutputStream memStream;

		OutputStream* marshallingStream = &memStream;
		Proxy* thisPtr = this;
		marshallingStream->write( thisPtr );
		marshallingStream->write( methodName );
		//marshall data to the stream
		marshallArguments( argCount, arguments, marshallingStream );
		//data marshalled to marshallingStream

		ClassServerInstance classSvrInst;
		result = classSvrInst.invoke( marshallingStream );
	}
	return result;
}


VCF::String Proxy::getClassName()
{
	return className_;
}

VCF::String Proxy::getClassID()
{
	return classID_;
}

Proxy* Proxy::createInstance( const VCF::String& className )
{
	Proxy* result = NULL;

	ClassServerInstance classSvrInst;

	result = classSvrInst.createInstance( className );

	return result;
}

Proxy* Proxy::createInstanceByClassID( const VCF::String& classID )
{
	Proxy* result = NULL;

	ClassServerInstance classSvrInst;

	result = classSvrInst.createInstanceByClassID( classID );

	return result;
}

void Proxy::saveToStream( VCF::OutputStream * stream )
{
	stream->write( classID_ );
	stream->write( className_ );
	stream->write( isRemote_ );
	stream->write( &instanceID_ );
}

void Proxy::loadFromStream( VCF::InputStream * stream )
{
	stream->read( classID_ );
	stream->read( className_ );
	stream->read( isRemote_ );
	stream->read( static_cast<Persistable*>(&instanceID_) );
}


/**
*CVS Log info
*$Log$
*Revision 1.2  2004/08/07 02:49:20  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.3  2004/07/30 17:31:56  kiklop74
*Added first release of Borland midifications for VCF
*
*Revision 1.1.2.2  2004/04/29 04:12:58  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:45:50  ddiego
*migration towards new directory structure
*
*Revision 1.9  2003/05/17 20:37:51  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.2.1  2003/03/12 03:13:33  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2003/02/26 04:30:57  ddiego
*merge of code in the devmain-0-5-9 branch into the current tree.
*most additions are in the area of the current linux port, but the major
*addition to this release is the addition of a Condition class (currently
*still under development) and the change over to using the Delegate class
*exclusively from the older event handler macros.
*
*Revision 1.7.14.1  2003/01/08 00:20:05  marcelloptr
*mispellings and newlines at the end of all source files
*
*Revision 1.7  2002/05/09 03:10:46  ddiego
*merged over code from development branch devmain-0-5-1a into the main CVS trunk
*
*Revision 1.6.4.1  2002/04/03 19:37:17  zzack
*include style changed
*
*Revision 1.6  2002/01/24 01:46:50  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


