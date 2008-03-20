//Base64Codec
#ifndef _VCF_BASE64CODEC_H__
#define _VCF_BASE64CODEC_H__
//Base64Codec.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF {



/**
\class Base64Codec Base64Codec.h "vcf/FoundationKit/Base64Codec.h"
*/
class FOUNDATIONKIT_API Base64Codec {
public:
	
	static void encode( const unsigned char* buffer, uint32 bufferSize, AnsiString& output, bool addLineBreak ) { 
		uint32 count = 0;
		uint32 o = 0;
		
		
		while (count < bufferSize) {
			uint32 remainingBytes = bufferSize - count;
			if ( addLineBreak && o && (o % 76 == 0) ) {
				output += "\n";
			}
			switch ( remainingBytes ) {
				case 1: {
					output += Base64Codec::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Codec::base64EncodingTable[ ((buffer[count] << 4) & 0x30) ];
					output += "==";
				}
				break; 
				case 2: {
					output += Base64Codec::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Codec::base64EncodingTable[ ((buffer[count] << 4) & 0x30) + ((buffer[count + 1] >> 4) & 0x0f) ];
					output += Base64Codec::base64EncodingTable[ ((buffer[count + 1] << 2) & 0x3c) ];
					output += "=";
				}
				break;

				default: {
					output += Base64Codec::base64EncodingTable[ ((buffer[count] >> 2) & 0x3f) ];
					output += Base64Codec::base64EncodingTable[ ((buffer[count] << 4) & 0x30) + ((buffer[count + 1] >> 4) & 0x0f) ];
					output += Base64Codec::base64EncodingTable[ ((buffer[count + 1] << 2) & 0x3c) + ((buffer[count + 2] >> 6) & 0x03) ];
					output += Base64Codec::base64EncodingTable[ (buffer[count + 2] & 0x3f) ];
				}
				break;
			}
			o += 4;
			count += 3;
		}
	}

	//calling this with a NULL buffer means that the buffer size will be returned
	static void decode(const AnsiString& input, unsigned char *buffer, uint32& bufferSize )	{
		uint32 index = 0;
		uint32 count = input.size();
		uint32 bufferIndex = 0;
		
		

		while (index < count)
		{
			while (index < count && (input[index] == 13 || input[index] == 10)) {
				index++;
			}

			if (index < count) {
				unsigned char b1 = (unsigned char)((Base64Codec::base64DecodingTable[(int)input[index]] << 2 & 0xfc) +
					(Base64Codec::base64DecodingTable[(int)input[index + 1]] >> 4 & 0x03));
				
				if ( buffer ) {
					buffer[bufferIndex] = b1;
				}
				
				bufferIndex++;
				if (input[index + 2] != '=')  {
					unsigned char b2 = (unsigned char)((Base64Codec::base64DecodingTable[(int)input[index + 1]] << 4 & 0xf0) +
						(Base64Codec::base64DecodingTable[(int)input[index + 2]] >> 2 & 0x0f));
					
					if ( buffer ) {
						buffer[bufferIndex] = b2;
					}

					bufferIndex++;
				}

				if (input[index + 3] != '=') {
					unsigned char b3 = (unsigned char)((Base64Codec::base64DecodingTable[(int)input[index + 2]] << 6 & 0xc0) +
						Base64Codec::base64DecodingTable[(int)input[index + 3]]);
					
					if ( buffer ) {
						buffer[bufferIndex] = b3;
					}
					
					bufferIndex++;
				}
				index += 4;
			}
		}
		bufferSize = bufferIndex;
	}

	static char* base64EncodingTable;
	static char base64DecodingTable[];
};


};



#endif //_VCF_BASE64CODEC_H__