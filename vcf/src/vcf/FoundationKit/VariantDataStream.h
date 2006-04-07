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

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom)	{
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		inStream_->seek( offset, offsetFrom );
	}

	virtual unsigned long getSize() {
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

	virtual ulong32 getCurrentSeekPos() {
		if ( NULL == inStream_ ) {
			throw InvalidPointerException();
		}
		return inStream_->getCurrentSeekPos();
	}

	virtual unsigned long read( unsigned char* bytesToRead, unsigned long sizeOfBytes ) {
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
			*data = (unsigned long)val;
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

	virtual void seek(const unsigned long& offset, const SeekType& offsetFrom)	{
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		outStream_->seek( offset, offsetFrom );
	}

	virtual unsigned long getSize() {
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

	virtual ulong32 getCurrentSeekPos() {
		if ( NULL == outStream_ ) {
			throw InvalidPointerException();
		}
		return outStream_->getCurrentSeekPos();
	}

	virtual unsigned long write( const unsigned char* bytesToWrite, unsigned long sizeOfBytes ) {
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


/**
*CVS Log info
*$Log$
*Revision 1.4  2006/04/07 02:35:36  ddiego
*initial checkin of merge from 0.6.9 dev branch.
*
*Revision 1.3.2.4  2006/03/19 00:04:17  obirsoy
*Linux FoundationKit improvements.
*
*Revision 1.3.2.3  2006/03/12 22:01:44  ddiego
*doc updates.
*
*Revision 1.3.2.2  2006/02/23 01:41:58  ddiego
*some minor changes to teh variantdata class, added support for specific char* and WideChar* cosntructor and for unsigned short types.
*
*Revision 1.3.2.1  2005/09/21 02:21:53  ddiego
*started to integrate jpeg support directly into graphicskit.
*
*Revision 1.3  2005/01/02 03:04:23  ddiego
*merged over some of the changes from the dev branch because they're important resoource loading bug fixes. Also fixes a few other bugs as well.
*
*Revision 1.2.4.1  2004/12/24 00:59:29  marcelloptr
*VariantData::toString() made const
*
*Revision 1.2  2004/08/07 02:49:15  ddiego
*merged in the devmain-0-6-5 branch to stable
*
*Revision 1.1.2.4  2004/07/20 04:56:30  ddiego
*fixed bug in VariantDataINputStream, where an object was not getting created correctly. Made some small updates to QTPLayer.
*
*Revision 1.1.2.3  2004/06/06 07:05:33  marcelloptr
*changed macros, text reformatting, copyright sections
*
*Revision 1.1.2.2  2004/04/29 04:07:13  marcelloptr
*reformatting of source files: macros and csvlog and copyright sections
*
*Revision 1.1.2.1  2004/04/28 03:29:41  ddiego
*migration towards new directory structure
*
*Revision 1.10.4.1  2004/04/26 21:58:45  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.10  2003/12/18 05:15:59  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.9.4.2  2003/11/24 05:05:23  ddiego
*added some more docs, and some minor changes to the Win32ScrollPeer
*
*Revision 1.9.4.1  2003/10/23 04:24:51  ddiego
*more musical chairs with headers again, in yet another attempt to make
*them more efficent to speed up compiles.
*Removed all teh template RTTI classes and put them all in one header
*called VCFRTTIImpl.h. This should help compile speeds a bit.
*The next step is to look at some of the event classes and remove ones
*that aren't really neccessary - I'd estimate that 50% of the current
*event classes are unneccessary and can be removed.
*
*Revision 1.9  2003/05/17 20:37:15  ddiego
*this is the checkin for the 0.6.1 release - represents the merge over from
*the devmain-0-6-0 branch plus a few minor bug fixes
*
*Revision 1.8.22.2  2003/03/23 06:46:01  marcelloptr
*minor fixes
*
*Revision 1.8.22.1  2003/03/12 03:11:46  ddiego
*switched all member variable that used the "m_"<name> prefix to
* <name>"_" suffix nameing standard.
*Also changed all vcf builder files to accomadate this.
*Changes were made to the Stream classes to NOT multiple inheritance and to
*be a little more correct. Changes include breaking the FileStream into two
*distinct classes, one for input and one for output.
*
*Revision 1.8  2002/02/28 01:07:09  ddiego
*fixed bug [ 523259 ] InputStream::read(String&) is incorrect
*added new virtual function Stream::getCurrentSeekPos to help fix the problem.
*Made apropriate changes to all stream headers and implementation to account
*for thisd
*
*Revision 1.7  2002/01/24 01:46:48  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/


#endif // _VCF_VARIANTDATASTREAM_H__


