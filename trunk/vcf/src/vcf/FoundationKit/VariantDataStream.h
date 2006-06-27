#ifndef _VCF_VARIANTDATASTREAM_H__
#define _VCF_VARIANTDATASTREAM_H__
//VariantDataStream.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {

/**
\class VariantDataInputStream VariantDataStream.h "vcf/FoundationKit/VariantDataStream.h"
*The VariantDataInputStream is used to read
*a VariantData object from an InputStream source.
*/
class FOUNDATIONKIT_API VariantDataInputStream : public InputStream {

public:
	VariantDataInputStream( InputStream* sourceInputStream ){
		inStream_ = sourceInputStream;
	};

	virtual ~VariantDataInputStream(){};

	virtual void seek(const uint32& offset, const SeekType& offsetFrom)	{
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		inStream_->seek( offset, offsetFrom );
	}

	virtual uint32 getSize() {
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		return inStream_->getSize();
	}

	virtual char* getBuffer() {
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		return inStream_->getBuffer();
	}

	virtual uint32 getCurrentSeekPos() {
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		return inStream_->getCurrentSeekPos();
	}

	virtual uint32 read( unsigned char* bytesToRead, uint32 sizeOfBytes ) {
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		return inStream_->read( bytesToRead, sizeOfBytes );		
	}

	virtual bool isEOS() {
		return inStream_->isEOS();
	}

	void readVariantData( VariantData* data ) {
		String type = "";
		inStream_->read( type );
		if ( type == "i" ) {
			int val = 0;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "l" ) {
			long val = 0;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "+l" ) {
			long val = 0;
			inStream_->read( val );
			*data = (uint32)val;
		}
		else if ( type == "h" ) {
			short val = 0;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "c" ) {
			char val = 0;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "d" ) {
			double val = 0.0;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "f" ) {
			float val = 0.0f;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "b" ) {
			bool val = false;
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "s" ) {
			String val = "";
			inStream_->read( val );
			*data = val;
		}
		else if ( type == "o" ) {
			String className;
			inStream_->read( className );

			Object* obj = NULL;

			try {
				obj = ClassRegistry::createNewInstance( className );
			}
			catch ( BasicException& ) {
				//do nothing, attempt to create from a class ID
			}

			try { 
				if ( NULL == obj ) {
					obj = ClassRegistry::createNewInstanceFromClassID( className );
				}
			}
			catch ( BasicException& ) {
			}

			*data = obj;

			if ( NULL != obj ) {
				Persistable* persistentObj = dynamic_cast<Persistable*>(obj);
				if ( NULL != persistentObj ) {
					inStream_->read( persistentObj );
				}
				else {
					throw TypeCastException("Error attempting to read from stream.\nObject doesn't support Persistable interface!");
				}
			}
			else {
				throw InvalidPointerException();
			}
		}
	}
private:
	InputStream* inStream_;
};

/**
\class VariantDataOutputStream VariantDataStream.h "vcf/FoundationKit/VariantDataStream.h"
*The VariantDataOutputStream is used to write a
*VariantData object to an OutputStream source.
*/
class FOUNDATIONKIT_API VariantDataOutputStream : public OutputStream{

public:
	VariantDataOutputStream( OutputStream* sourceOutputStream ){
		outStream_ = sourceOutputStream;
	};

	virtual ~VariantDataOutputStream(){};

	virtual void seek(const uint32& offset, const SeekType& offsetFrom)	{
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		outStream_->seek( offset, offsetFrom );
	}

	virtual uint32 getSize() {
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		return outStream_->getSize();
	}

	virtual char* getBuffer() {
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		return outStream_->getBuffer();
	}

	virtual uint32 getCurrentSeekPos() {
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		return outStream_->getCurrentSeekPos();
	}

	virtual uint32 write( const unsigned char* bytesToWrite, uint32 sizeOfBytes ) {
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		return outStream_->write( bytesToWrite, sizeOfBytes );
	}

	void writeVariantData( const VariantData* data ) {
		switch ( data->type ) {
			case pdInt : {
				outStream_->write( String("i") );
				outStream_->write( (int)(*data) );
			}
			break;

			case pdUInt : {
				outStream_->write( String("+i") );
				uint32 tmp = (*data);
				outStream_->write( (int)tmp );
			}
			break;

			case pdLong : {
				outStream_->write( String("l") );
				outStream_->write( (long)(*data) );
			}
			break;

			case pdULong : {
				outStream_->write( String("+l") );
				outStream_->write( (long)(*data) );
			}
			break;

			case pdShort : {
				outStream_->write( String("h") );
				outStream_->write( (short)(*data) );
			}
			break;

			case pdUShort : {
				outStream_->write( String("+h") );
				outStream_->write( (ushort)(*data) );
			}
			break;

			case pdChar : {
				outStream_->write( String("c") );
				outStream_->write( (char)(*data) );
			}
			break;

			case pdDouble : {
				outStream_->write( String("d") );
				outStream_->write( (double)(*data) );
			}
			break;

			case pdFloat : {
				outStream_->write( String("f") );
				outStream_->write( (float)(*data) );
			}
			break;

			case pdBool : {
				outStream_->write( String("b") );
				outStream_->write( (bool)(*data) );
			}
			break;

			case pdString : {
				outStream_->write( String("s") );
				outStream_->write( (String)(*data) );
			}
			break;

			case pdObject : {
				Object* obj = *data;
				if ( NULL != obj ) {
					Persistable* persistentObj = dynamic_cast<Persistable*>(obj);
					if ( NULL != persistentObj ) {
						outStream_->write( String("o") );
						outStream_->write( obj->getClassName() );
						outStream_->write( persistentObj );
					}
					else {
						throw TypeCastException("Error attempting to write to stream.\nObject doesn't support Persistable interface!");
					}
				}
				else {
					throw InvalidPointerException();
				}
			}
			break;

            default: {
            }
            break;
		}
	}
private:
	OutputStream* outStream_;
};

}; //end of namespace VCF


#endif // _VCF_VARIANTDATASTREAM_H__

/**
$Id$
*/
