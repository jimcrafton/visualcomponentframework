#ifndef _VCF_INIFINI_H__
#define _VCF_INIFINI_H__
//IniFini.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


namespace VCF  {

	typedef void (*InitializationFunc)();
	typedef void (*FinalizationFunc)();

	class FOUNDATIONKIT_API Initialization {
	public:
		Initialization( InitializationFunc funcPtr );
	private:
		Initialization();
		Initialization( const Initialization& );
		~Initialization();
	};


	class FOUNDATIONKIT_API Finalization {
	public:
		Finalization( FinalizationFunc funcPtr );
	private:
		Finalization();
		Finalization( const Finalization& );
		~Finalization();
	};
};


#endif // _VCF_INIFINI_H__

/**
$Id: IniFini.h  $
*/
