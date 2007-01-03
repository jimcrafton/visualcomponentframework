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

			case pdUInt : {
				marshallingStream->write( String("+i") );
				marshallingStream->write( (long)(*arg) );
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

			case pdUShort : {
				marshallingStream->write( String("+h") );
				marshallingStream->write( (ushort)(*arg) );
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

VariantData Proxy::invoke( const VCF::String& methodName, const uint32& argCount, VariantData** arguments )
{
 	VariantData result;

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
$Id$
*/
