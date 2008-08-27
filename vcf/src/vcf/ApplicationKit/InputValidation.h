#ifndef _VCF_INPUTVALIDATION_H__
#define _VCF_INPUTVALIDATION_H__
//InputValidation.h

/*
Copyright 2000-3004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif

/**
Text based input validation based on the MFC classes by Alvaro Mendez (07/17/2000).
The classes referenced were the CAMSEdit, Behavior, AlphanumericBehavior, 
MaskedBehavior, NumericBehavior, DateBehavior, TimeBehavior, and DateTimeBehavior.
*/

#define VCF_MIN_NUMBER			-1.7976931348623158e+308
#define VCF_MAX_NUMBER			 1.7976931348623158e+308

namespace VCF {

	class Control;

	class APPLICATIONKIT_API InvalidInputEvent : public Event {
	public:
		InvalidInputEvent( Object* source ): Event(source),invalidChar(0){}

		InvalidInputEvent( Object* source, const uint32& eventType ): Event(source,eventType),invalidChar(0){}

		virtual ~InvalidInputEvent(){}

		virtual Object* clone( bool deep=false ) {
			return new InvalidInputEvent(*this);
		}

		VCFChar invalidChar;
	};


	typedef Delegate1<InvalidInputEvent*> InvalidInputDelegate; 



	class APPLICATIONKIT_API InputValidator : public Component {
	public:

		DELEGATE(InvalidInputDelegate,InvalidInput);

		InputValidator();
		virtual ~InputValidator(){}


		virtual void handleEvent( Event* e );


		virtual String getValidText() = 0;

		TextControl* getInputControl() {
			return inputControl_;
		}

		void setInputControl( TextControl* val );

		virtual void resetText();

		void addFlag( uint32 flag ) {
			modifyFlags(flag,0);
		}

		void removeFlag( uint32 flag ) {
			modifyFlags(0,flag);
		}

		void setFlags( const uint32& flags );

		uint32 getFlags() {
			return flags_;
		}

		bool hasFlag( uint32 flag ) {
			return flags_ & flag ? true : false;
		}

		bool modifyFlags( uint32 flagToAdd, uint32 flagToRemove );
		
	protected:
		virtual bool allowCharacter( VCFChar ch ) {
			return true;
		}

		TextControl* inputControl_;

		uint32 flags_;
	};



	class APPLICATIONKIT_API AlphaNumericValidator : public InputValidator {
	public:
		AlphaNumericValidator();

		virtual String getValidText();
		virtual void handleEvent( Event* e );

		void setInvalidCharacters( const String& val );

		String getInvalidCharacters() {
			return invalidChars_;
		}

		void setMaxCharacters( size_t val );

		size_t getMaxCharacters() {
			return maxChars_;
		}

		void changeMaxCharacters( Event* );
		void changeInvalidCharacters( Event* );
	protected:
		size_t maxChars_;
		String invalidChars_;

		
	};


	class APPLICATIONKIT_API MaskedValidator : public InputValidator {
	public:
		MaskedValidator();

		virtual String getValidText();

		virtual void handleEvent( Event* e );

		void setMask( const String& val );

		String getMask() {
			return mask_;
		}

		String getNumericText();


		class APPLICATIONKIT_API Symbol	{
		public:
			typedef int (*ValidationFunction)(VCFChar);		
			typedef VCFChar (*ConversionFunction)(VCFChar);		
			
			
			Symbol():symbol_(0), validationFunc_(NULL), conversionFunc_(NULL){}
			Symbol(VCFChar symbol, ValidationFunction validationFunc, ConversionFunction conversionFunc = NULL):
				symbol_(symbol),
					validationFunc_(validationFunc),
					conversionFunc_(conversionFunc)	{}

			virtual ~Symbol(){}


			virtual bool validate(VCFChar c) const {
				if ( validationFunc_ ) {
					return validationFunc_(c) ? true : false;
				}

				return true;
			}

			virtual VCFChar convert(VCFChar c) const {
				if ( NULL != conversionFunc_ ) {
					return (VCFChar) conversionFunc_(c);
				}
				return c;
			}

			void set(VCFChar val) {
				symbol_ = val;
			}

			VCFChar get() const {
				return symbol_;
			}

			operator VCFChar() const {
				return symbol_;
			}

		protected:
			VCFChar symbol_;
			ValidationFunction validationFunc_;
			ConversionFunction conversionFunc_;
		};


		typedef std::vector<Symbol> SymbolArray;


		SymbolArray& getSymbolArray() {
			return symbols_;
		}

		void changeMask( Event* );
	protected:
		String mask_;
		SymbolArray symbols_;

	};




	class APPLICATIONKIT_API NumericValidator : public InputValidator {
	public:
		NumericValidator();

		enum ValidationFlags {
			vfNone										= 0x0000,
			vfCannotBeNegative							= 0x1000,
			vfAddDecimalAfterMaxWholeDigits				= 0x2000,
			vfPadWithZerosAfterDecimalWhenTextChanges		= 0x4000,
			vfPadWithZerosAfterDecimalWhenTextIsSet		= 0x8000,

			vfOnKillFocus_BeepIfInvalid					= 0x0001,
			vfOnKillFocus_BeepIfEmpty					= 0x0002,
			vfOnKillFocus_Beep							= 0x0003,
			vfOnKillFocus_SetValidIfInvalid				= 0x0004,
			vfOnKillFocus_SetValidIfEmpty				= 0x0008,
			vfOnKillFocus_SetValid						= 0x000C,
			vfOnKillFocus_SetFocusIfInvalid				= 0x0010,
			vfOnKillFocus_SetFocusIfEmpty				= 0x0020,
			vfOnKillFocus_SetFocus						= 0x0030,
			vfOnKillFocus_ShowMessageIfInvalid			= 0x0050,
			vfOnKillFocus_ShowMessageIfEmpty				= 0x00A0,
			vfOnKillFocus_ShowMessage						= 0x00F0,

			vfOnKillFocus_PadWithZerosBeforeDecimal		= 0x0100,
			vfOnKillFocus_PadWithZerosAfterDecimal		= 0x0200,
			vfOnKillFocus_DontPadWithZerosIfEmpty			= 0x0400,
			vfOnKillFocus_RemoveExtraLeadingZeros			= 0x0800,
			vfOnKillFocus_Max								= 0x0FFF
		};


		virtual String getValidText();
		virtual void handleEvent( Event* e );


		void setDoubleAndTrim( const double& val, bool bTrimTrailingZeros );
		void setDouble( const double& val);
		double getDouble();

		void setInt( const int& val );
		int getInt();
		
		void setMaxWholeDigits( const int& val );
		int getMaxWholeDigits() {
			return maxWholeDigits_;
		}
		
		void setMaxDecimalPlaces( const size_t& val );

		size_t getMaxDecimalPlaces() {
			return maxDecimalPlaces_;
		}
		
		void setAllowNegative( const bool& val );
		bool isNegativeAllowed();
		
		void setDigitsInGroup( const size_t& nDigitsInGroup );
		size_t getDigitsInGroup() {
			return digitsInGroup_;
		}
		
		void setSeparators( const String& decimalChar, const String& groupChar );
		void getSeparators( String& decimalChar, String& groupChar );

		void setDecimalSeparator( const String& val );
		String getDecimalSeparator() {
			return decimalPoint_;
		}

		void setGroupSeparator( const String& val );
		String getGroupSeparator() {
			return groupSeparator_;
		}
		

		void setPrefix(const String& val );
		String getPrefix() {
			return prefix_;
		}

		void setMask(const String& mask);
		String getMask();

		void setRange( double minNum, double maxNum );
		void getRange( double& minNum, double& maxNum);

		void setMax( const double& val );
		double getMax() {
			return max_;
		}

		void setMin( const double& val );
		double getMin() {
			return min_;
		}

		virtual bool isValid();
		bool checkIfValid(bool showErrorIfNotValid = true);


		void changeMask( Event* );
		void changeAllowNegative( Event* );
		void changeMaxWholeDigits( Event* );
		void changeMaxDecimalPlaces( Event* );
	protected:
		int maxWholeDigits_;
		size_t maxDecimalPlaces_;
		String negativeSign_;
		String decimalPoint_;
		String groupSeparator_;
		size_t digitsInGroup_;
		String prefix_;
		double min_;
		double max_;
		bool adjustingSeparators_;

		
		int getGroupSeparatorCount(const String& strText);
		
		String getNumericText(const String& text, bool useMathSymbols = false);
		String getDoubleText(double val, bool bTrimTrailingZeros = true);
		String getSeparatedText(const String& text);
		void adjustSeparators(int currentSeparatorCount);
		static void insertZeros(String& text, int nPos, int nCount);

		virtual void showErrorMessage();
		void adjustWithinRange();

	};
};



#endif //_VCF_INPUTVALIDATION_H__