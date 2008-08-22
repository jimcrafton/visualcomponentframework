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
	protected:
		TextControl* inputControl_;
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
	protected:
		size_t maxChars_;
		String invalidChars_;

		virtual bool allowCharacter( VCFChar ch ) {
			return true;
		}
	};
};



#endif //_VCF_INPUTVALIDATION_H__