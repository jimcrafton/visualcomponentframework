/** \file
  * Wrapper for VARIANT.
  */
/*
 * Copyright � 2000, 2001 Sofus Mortensen, Michael Geddes
 *
 * This material is provided "as is", with absolutely no warranty
 * expressed or implied. Any use is at your own risk. Permission to
 * use or copy this software for any purpose is hereby granted without
 * fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is
 * granted, provided the above notices are retained, and a notice that
 * the code was modified is included with the above copyright notice.
 *
 * This header is part of comet.
 * http://www.lambdasoft.dk/comet
 */

#ifndef COMET_VARIANT_H
#define COMET_VARIANT_H

#include <comet/config.h>
#include <comet/datetime.h>
#include <comet/error_fwd.h>
#include <comet/assert.h>
#include <comet/common.h>
#include <comet/bstr.h>
#include <comet/currency.h>

#include <iostream>

#pragma warning(push)
#pragma warning(disable : 4127)

#define COMET_VARIANT_OPERATOR(op, name)																						\
	variant_t operator op(const variant_t& x) const															\
	{																											\
		VARIANT t;																								\
		Var##name(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(x.get_var()), &t) | raise_exception;	\
		return auto_attach(t);																					\
	}																											\
																												\
	variant_t& operator op##=(const variant_t& x)																\
	{																											\
		return operator=(operator op(x));																		\
	}

#define COMET_VARIANT_CONVERTERS_EX_(type, vartype, func)			\
	variant_t(type x) throw()										\
	{																\
		V_##vartype(this) = x; V_VT(this) = VT_##vartype;			\
	}																\
																	\
	func() const													\
	{																\
		if (V_VT(this) == VT_##vartype) return V_##vartype(this);	\
		variant_t v(*this, VT_##vartype);							\
		return V_##vartype(v.get_var());							\
	}																\
																	\
	variant_t& operator=(type x) throw()							\
	{																\
		clear();													\
		V_##vartype(this) = x; V_VT(this) = VT_##vartype;			\
		return *this;												\
	}

#define COMET_VARIANT_CONVERTERS_EXPLICIT(type, vartype, funcname)  COMET_VARIANT_CONVERTERS_EX_(type,vartype, type funcname)
#define COMET_VARIANT_CONVERTERS(type, vartype) COMET_VARIANT_CONVERTERS_EX_(type,vartype, operator type )

#define COMET_VARIANT_FRIENDS(type)												\
	inline bool operator!=(type x, const variant_t& y)	{ return y != x; } \
	inline bool operator==(type x, const variant_t& y)	{ return y == x; } \
	inline bool operator<(type x, const variant_t& y)	{ return y > x; } \
	inline bool operator<=(type x, const variant_t& y)	{ return y >= x; } \
	inline bool operator>(type x, const variant_t& y)	{ return y < x; } \
	inline bool operator>=(type x, const variant_t& y)	{ return y <= x; }

namespace comet {

#ifdef _WIN32_WCE
	HRESULT WINAPI SafeArrayGetVartype(SAFEARRAY* psa, VARTYPE* pvt)
	{


		if (!psa || !pvt)
			return E_INVALIDARG;

		if (psa->fFeatures & FADF_RECORD)
			*pvt = VT_RECORD;
		else if ((psa->fFeatures & (FADF_HAVEIID|FADF_DISPATCH)) == (FADF_HAVEIID|FADF_DISPATCH))
			*pvt = VT_DISPATCH;
		else if (psa->fFeatures & FADF_HAVEIID)
			*pvt = VT_UNKNOWN;
		else if (psa->fFeatures & FADF_HAVEVARTYPE)
		{
			VARTYPE vt = VT_VARIANT;// SAFEARRAY_GetHiddenDWORD(psa);
			*pvt = vt;
		}
		else
			return E_INVALIDARG;

		return S_OK;
	}

	HRESULT _VarChangeTypeExWrap (VARIANTARG* pvargDest,
		VARIANTARG* pvargSrc, LCID lcid, USHORT wFlags, VARTYPE vt)
	{
		HRESULT res;
		VARTYPE flags;

		flags = V_VT(pvargSrc) & ~VT_TYPEMASK;
		V_VT(pvargSrc) &= ~VT_RESERVED;
		res = VariantChangeTypeEx(pvargDest,pvargSrc,lcid,wFlags,vt);
		V_VT(pvargSrc) |= flags;

		return res;
	}


	HRESULT WINAPI VarCmp(LPVARIANT left, LPVARIANT right, LCID lcid, DWORD flags)
	{
		VARTYPE     lvt, rvt, vt;
		VARIANT     rv,lv;
		DWORD       xmask;
		HRESULT     rc;

		lvt = V_VT(left) & VT_TYPEMASK;
		rvt = V_VT(right) & VT_TYPEMASK;
		xmask = (1 << lvt) | (1 << rvt);

		/* If we have any flag set except VT_RESERVED bail out.
		Same for the left input variant type > VT_INT and for the
		right input variant type > VT_I8. Yes, VT_INT is only supported
		as left variant. Go figure */
		if (((V_VT(left) | V_VT(right)) & ~VT_TYPEMASK & ~VT_RESERVED) ||
			lvt > VT_INT || rvt > VT_I8) {
				return DISP_E_BADVARTYPE;
		}

		/* Don't ask me why but native VarCmp cannot handle: VT_I1, VT_UI2, VT_UI4,
		VT_UINT and VT_UI8. Tested with DCOM98, Win2k, WinXP */
		if (rvt == VT_INT || xmask & (VTBIT_I1 | VTBIT_UI2 | VTBIT_UI4 | VTBIT_UI8 |
			VTBIT_DISPATCH | VTBIT_VARIANT | VTBIT_UNKNOWN | VTBIT_15))
			return DISP_E_TYPEMISMATCH;

		/* If both variants are VT_ERROR return VARCMP_EQ */
		if (xmask == VTBIT_ERROR)
			return VARCMP_EQ;
		else if (xmask & VTBIT_ERROR)
			return DISP_E_TYPEMISMATCH;

		if (xmask & VTBIT_NULL)
			return VARCMP_NULL;

		VariantInit(&lv);
		VariantInit(&rv);

		/* Two BSTRs, ignore VT_RESERVED */
		if (xmask == VTBIT_BSTR)
			return VarBstrCmp(V_BSTR(left), V_BSTR(right), lcid, flags);

		/* A BSTR and an other variant; we have to take care of VT_RESERVED */
		if (xmask & VTBIT_BSTR) {
			VARIANT *bstrv, *nonbv;
			VARTYPE nonbvt;
			int swap = 0;

			/* Swap the variants so the BSTR is always on the left */
			if (lvt == VT_BSTR) {
				bstrv = left;
				nonbv = right;
				nonbvt = rvt;
			} else {
				swap = 1;
				bstrv = right;
				nonbv = left;
				nonbvt = lvt;
			}

			/* BSTR and EMPTY: ignore VT_RESERVED */
			if (nonbvt == VT_EMPTY)
				rc = (!V_BSTR(bstrv) || !*V_BSTR(bstrv)) ? VARCMP_EQ : VARCMP_GT;
			else {
				VARTYPE breserv = V_VT(bstrv) & ~VT_TYPEMASK;
				VARTYPE nreserv = V_VT(nonbv) & ~VT_TYPEMASK;

				if (!breserv && !nreserv)
					/* No VT_RESERVED set ==> BSTR always greater */
					rc = VARCMP_GT;
				else if (breserv && !nreserv) {
					/* BSTR has VT_RESERVED set. Do a string comparison */
					rc = VariantChangeTypeEx(&rv,nonbv,lcid,0,VT_BSTR);
					if (FAILED(rc))
						return rc;
					rc = VarBstrCmp(V_BSTR(bstrv), V_BSTR(&rv), lcid, flags);
				} else if (V_BSTR(bstrv) && *V_BSTR(bstrv)) {
					/* Non NULL nor empty BSTR */
					/* If the BSTR is not a number the BSTR is greater */
					rc = _VarChangeTypeExWrap(&lv,bstrv,lcid,0,VT_R8);
					if (FAILED(rc))
						rc = VARCMP_GT;
					else if (breserv && nreserv)
						/* FIXME: This is strange: with both VT_RESERVED set it
						looks like the result depends only on the sign of
						the BSTR number */
						rc = (V_R8(&lv) >= 0) ? VARCMP_GT : VARCMP_LT;
					else
						/* Numeric comparison, will be handled below.
						VARCMP_NULL used only to break out. */
						rc = VARCMP_NULL;
					VariantClear(&lv);
					VariantClear(&rv);
				} else
					/* Empty or NULL BSTR */
					rc = VARCMP_GT;
			}
			/* Fixup the return code if we swapped left and right */
			if (swap) {
				if (rc == VARCMP_GT)
					rc = VARCMP_LT;
				else if (rc == VARCMP_LT)
					rc = VARCMP_GT;
			}
			if (rc != VARCMP_NULL)
				return rc;
		}

		if (xmask & VTBIT_DECIMAL)
			vt = VT_DECIMAL;
		else if (xmask & VTBIT_BSTR)
			vt = VT_R8;
		else if (xmask & VTBIT_R4)
			vt = VT_R4;
		else if (xmask & (VTBIT_R8 | VTBIT_DATE))
			vt = VT_R8;
		else if (xmask & VTBIT_CY)
			vt = VT_CY;
		else
			/* default to I8 */
			vt = VT_I8;

		/* Coerce the variants */
		rc = _VarChangeTypeExWrap(&lv,left,lcid,0,vt);
		if (rc == DISP_E_OVERFLOW && vt != VT_R8) {
			/* Overflow, change to R8 */
			vt = VT_R8;
			rc = _VarChangeTypeExWrap(&lv,left,lcid,0,vt);
		}
		if (FAILED(rc))
			return rc;
		rc = _VarChangeTypeExWrap(&rv,right,lcid,0,vt);
		if (rc == DISP_E_OVERFLOW && vt != VT_R8) {
			/* Overflow, change to R8 */
			vt = VT_R8;
			rc = _VarChangeTypeExWrap(&lv,left,lcid,0,vt);
			if (FAILED(rc))
				return rc;
			rc = _VarChangeTypeExWrap(&rv,right,lcid,0,vt);
		}
		if (FAILED(rc))
			return rc;

#define _VARCMP(a,b) \
	(((a) == (b)) ? VARCMP_EQ : (((a) < (b)) ? VARCMP_LT : VARCMP_GT))

		switch (vt) {
		 case VT_CY:
			 return VarCyCmp(V_CY(&lv), V_CY(&rv));
		 case VT_DECIMAL:
			 return VarDecCmp(&V_DECIMAL(&lv), &V_DECIMAL(&rv));
#ifndef _WIN32_WCE
		 case VT_I8:
			 return _VARCMP(V_I8(&lv), V_I8(&rv));
#endif
		 case VT_R4:
			 return _VARCMP(V_R4(&lv), V_R4(&rv));
		 case VT_R8:
			 return _VARCMP(V_R8(&lv), V_R8(&rv));
		 default:
			 /* We should never get here */
			 return E_FAIL;
		}
#undef _VARCMP
	}

#endif


	template<typename T> class safearray_t;

	namespace impl {
	};

	template<typename Itf> class com_ptr;


	/*! \addtogroup COMType
	 */
	//@{

	//! Wrapper for VARIANT type.
	/** variant_t is exception safe (basic and strong guarantee).
	*/
	class variant_t : private ::tagVARIANT
	{
	private:
		void init() throw()
		{
			//::VariantInit(this);
			tagVARIANT * x = this;
			V_VT(x)= VT_EMPTY;
		}

		void create(const VARIANT& v) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			HRESULT hr = ::VariantCopy(this, const_cast<VARIANT*>(&v));
			if (FAILED(hr)) {
				::VariantClear(this);
				raise_exception(hr);
			}
		}

	public:
		//! Default constructor
		variant_t() throw()
		{
			init();
		}

	private:
		struct tagMissing {};

		variant_t(const tagMissing&) throw()
		{
			init();
			vt = VT_ERROR;
			scode = DISP_E_PARAMNOTFOUND;
		}

		struct tagNothing {};

		variant_t(const tagNothing&) throw()
		{
			init();
			vt = VT_DISPATCH;
			pdispVal = 0;
		}

		struct tagNull {};

		variant_t(const tagNull&) throw()
		{
			init();
			vt = VT_NULL;
		}

	public:
		//! Return a variant constructed as missing.
		/**	(VT_ERROR with code DISP_E_PARAMNOTFOUND )
		 */
		static const variant_t& missing()
		{
			static tagMissing t;
			static variant_t v(t);
			return v;
		}

		//! Return a variant contructed as nothing.
		/** (VT_DISPATCH with value 0)
		 */
		static const variant_t& nothing()
		{
			static tagNothing t;
			static variant_t v(t);
			return v;
		}

		//! Return a variant constructed as null (VT_NULL).
		static const variant_t& null()
		{
			static tagNull t;
			static variant_t v(t);
			return v;
		}

		//! Copy constructor
		/*!
			\exception com_error
				Thrown if underlying VariantCopy fails.
		*/
		variant_t(const variant_t& v) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			init();
			create(v);
		}

	public:

		//! VariantChangeType Constructor
		/*!
			Copies variant and changes to specified type.

			\note Unlike the _variant_t of VC, variant_t uses Thread Locale for type changes instead of the user setting.

			\par v
				Variant to copy from
			\par vartype
				Type to change to.

			\exception com_error
				Thrown if underlying VariantChangeTypeEx fails.
		*/
		variant_t(const variant_t& v, VARTYPE vartype) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			init();
			if (vartype != V_VT(&v))
				::VariantChangeTypeEx(get_var(),
				const_cast<VARIANT*>(v.get_var()),
				GetThreadLocale(),
				0, vartype) | raise_exception;
			else
				::VariantCopy(this, const_cast<VARIANT*>(v.get_var()));
		}

		variant_t(const variant_t& v, VARTYPE vartype, std::nothrow_t) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			init();
			if (vartype != V_VT(&v))
				::VariantChangeTypeEx(get_var(),
				const_cast<VARIANT*>(v.get_var()),
				GetThreadLocale(),
				0, vartype);
			else
				::VariantCopy(this, const_cast<VARIANT*>(v.get_var()));
		}

		//! Constructor
		/*!
			\exception com_error
				Thrown if underlying VariantCopy fails.
		*/
		explicit variant_t(const VARIANT& v) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			init();
			create(v);
		}

		//! Attaching constructor
		/*!
			Takes ownership of specified VARIANT.

			\param v
				auto_attach wrapper variant to attach to the variant_t
		*/
		variant_t(const impl::auto_attach_t<VARIANT>& v) throw()
		{
			memcpy(this, &const_cast<VARIANT&>(v.get()), sizeof(VARIANT));
		}

	private:
		void clear() COMET_THROWS_ASSERT
		{
			HRESULT hr = ::VariantClear(this);
			COMET_ASSERT(SUCCEEDED(hr));
			/* Avoid C4189 */ hr;
		}

	public:

		//! Destructor
		/*!
			\note Be aware that the underlying call to VariantClear may fail.
			But since we are not allowed to throw any exceptions (Otherwise STL containers cannot guarantee exception safety)
			from within a
			destructor, a failing VariantClear will be ignored.
			Instead we assert for success in debug and ignore in release.
		*/
		~variant_t() throw()
		{
			clear();
		}

		/// \name com_ptr<Itf> conversion.
		//@{
	private:
		template<typename Itf> void create(const com_ptr<Itf>& x) throw()
		{
			com_ptr< ::IDispatch > p( com_cast(x) );
			if (p != 0) {
				V_VT(this) = VT_DISPATCH;
				V_DISPATCH(this) = p.detach();
			} else {
				V_VT(this) = VT_UNKNOWN;
//				VTT_(punkVal) = static_cast<::IUnknown*>(com_ptr<Itf>(x).detach());
				com_ptr< ::IUnknown > p( com_cast(x) );
				V_UNKNOWN(this) = p.detach();
			}
		}

	public:
		template<typename Itf> variant_t(const com_ptr<Itf>& x) throw()
		{
			init();
			create(x);
		}

		template<typename Itf>
		variant_t& operator=(const com_ptr<Itf>& x) throw()
		{
			clear(); create(x); return *this;
		}

		//@}


		//!\name bool Conversion
		//@{
		variant_t(bool x) throw() {
			init();
			V_VT(this) = VT_BOOL;
			V_BOOL(this) = x ? COMET_VARIANT_TRUE : COMET_VARIANT_FALSE;
		}

		operator bool() const throw()
		{
			if (V_VT(this) == VT_BOOL) return (V_BOOL(this) != COMET_VARIANT_FALSE);
			variant_t v(*this, VT_BOOL);
			return (V_BOOL(&v) != COMET_VARIANT_FALSE);
		}

		variant_t& operator=(bool x) throw()
		{
			clear();
			V_VT(this) = VT_BOOL;
			V_BOOL(this) = x ? COMET_VARIANT_TRUE : COMET_VARIANT_FALSE;
			return *this;
		}

		//@}

		//!\name string Conversion
		//@{
		variant_t(const bstr_t& s) throw(std::bad_alloc)
		{
			init();
			bstr_t t(s);
			V_BSTR(this) = bstr_t::detach(t);
			V_VT(this) = VT_BSTR;
		}

		variant_t(const wchar_t* s) throw(std::bad_alloc)
		{
			init();
			bstr_t t(s);
			V_BSTR(this) = bstr_t::detach(t);
			V_VT(this) = VT_BSTR;
		}

		variant_t(const std::wstring& s) throw(std::bad_alloc)
		{
			init();
			bstr_t t(s);
			V_BSTR(this) = bstr_t::detach(t);
			V_VT(this) = VT_BSTR;
		}

		variant_t(const std::string& s) throw(std::bad_alloc)
		{
			init();
			bstr_t bs(s);
			V_BSTR(this) = bstr_t::detach(bs);
			V_VT(this) = VT_BSTR;
		}

		variant_t(const char* x)
		{
			init();
			V_BSTR(this) = bstr_t::detach(x);
			V_VT(this) = VT_BSTR;
		}

		/** Attach a BSTR to a variant.
		 * \code
		 		bstr_t val = L"A large string";
				variant_t(auto_attach(val.detach()));
			\endcode
		 */
		variant_t( const impl::auto_attach_t<BSTR> &bstrVal)
		{
			V_BSTR(this) = bstrVal.get();
			V_VT(this) = VT_BSTR;
		}

/*		operator bstr_t() const
		{
			if (V_VT(this) == VT_BSTR) return V_BSTR(this);
			variant_t v(*this, VT_BSTR);
			VARIANT t = v.detach();
			return auto_attach(V_BSTR(&t));
		}*/

		bstr_t str() const
		{
			if (V_VT(this) == VT_BSTR) return V_BSTR(this);
			if (V_VT(this) == (VT_BSTR | VT_BYREF)) return *V_BSTRREF(this);
			if (V_VT(this) == VT_NULL) return bstr_t();
			variant_t v(*this, VT_BSTR);
			VARIANT t = v.detach();
			return auto_attach(V_BSTR(&t));
		}

		operator bstr_t() const
		{
			return str();
		}

		operator std::wstring() const
		{
			if (V_VT(this) == VT_BSTR) return V_BSTR(this);
			if (V_VT(this) == (VT_BSTR | VT_BYREF)) return *V_BSTRREF(this);
			if (V_VT(this) == VT_NULL) return std::wstring();
			variant_t v(*this, VT_BSTR);
			return V_BSTR(&v) ? std::wstring(V_BSTR(&v)) : std::wstring();
		}

		operator std::string() const
		{
			return str().s_str();
		}

		variant_t& operator=(const bstr_t& s)
		{
			variant_t t(s);
			swap(t);
			return *this;
		}

		variant_t& operator=(const wchar_t* s)
		{
			variant_t t(s);
			swap(t);
			return *this;
		}

		variant_t& operator=(const char* s)
		{
			variant_t t(s);
			swap(t);
			return *this;
		}

		variant_t& operator=(const std::wstring& s)
		{
			variant_t t(s);
			swap(t);
			return *this;
		}

		variant_t& operator=(const std::string& s)
		{
			variant_t t(s);
			swap(t);
			return *this;
		}

		//@}

		//! \name safearray Conversions
		//@{
		template<typename SAT>
		variant_t(const safearray_t<SAT> &x)
		{
			safearray_t<SAT> sa( x );
			V_ARRAY(this) = sa.detach();
			V_VT(this) = (VT_ARRAY | safearray_t<SAT>::traits::vt);
		}

		template<typename SAT>
		variant_t& operator=(const safearray_t<SAT> &x) throw()
		{
			variant_t t(x);
			swap(t);
			return *this;
		}

		/** Allow attaching a SAFEARRAY to a variant.
		  * \code
		  *     safearray_t<bstr_t> array;
		  *     variant_t(auto_attach(array.detach()));
		  * \endcode
		  */
		variant_t( const impl::auto_attach_t<SAFEARRAY*> &psa)
		{
			V_ARRAY(this) = psa.get();
			VARTYPE vt;
			SafeArrayGetVartype( psa.get(), &vt) | raise_exception;
			V_VT(this) = VARTYPE(VT_ARRAY | vt) ;
		}


		//@}

		//! \name Numeric Conversions
		//@{

		COMET_VARIANT_CONVERTERS_EXPLICIT(short, I2, as_short);
		inline operator short() const { return as_short(); }
		COMET_VARIANT_CONVERTERS_EXPLICIT(int, I4, as_int); // Do not use VT_INT, because VariantChangeTypeEx does not support VT_INT.
		inline operator int() const { return as_int(); }
		COMET_VARIANT_CONVERTERS_EXPLICIT(long, I4, as_long);
		inline operator long() const { return as_long(); }
		COMET_VARIANT_CONVERTERS_EXPLICIT(float, R4, as_float);
		inline operator float() const { return as_float(); }
		COMET_VARIANT_CONVERTERS_EXPLICIT(double, R8, as_double);
		inline operator double() const { return as_double(); }
		// These can't have implicit conversions as they cause confusion when
		// assigning some common objects from variant_ts.
		COMET_VARIANT_CONVERTERS_EXPLICIT(char, I1, as_char);
		COMET_VARIANT_CONVERTERS_EXPLICIT(unsigned char, UI1, as_uchar);
		COMET_VARIANT_CONVERTERS_EXPLICIT(unsigned short, UI2, as_ushort);
		COMET_VARIANT_CONVERTERS_EXPLICIT(unsigned int, UI4, as_uint);
		COMET_VARIANT_CONVERTERS_EXPLICIT(unsigned long, UI4, as_ulong);
		COMET_VARIANT_CONVERTERS_EXPLICIT(DECIMAL, DECIMAL, as_decimal);

		wchar_t as_wchar_t() const { return as_ushort(); }
		//@}
		// CONVERTERS(DATE, DATE);

		//! \name Currency Conversions
		//@{

		variant_t(const currency_t &x) throw()
		{
			V_CY(this) = x.get();
			V_VT(this) = VT_CY;
		}

		operator currency_t() const
		{
			return as_curency();
		}
		currency_t as_curency() const
		{
			if (V_VT(this) == VT_CY) return V_CY(this);
			variant_t v(*this, VT_CY);
			return V_CY(v.get_var());
		}

		variant_t& operator=(const currency_t &x) throw()
		{
			clear();
			V_CY(this) = x.get();
			V_VT(this) = VT_CY;
			return *this;
		}

		//@}

		//! \name Date Conversions
		//@{

		variant_t(const datetime_t &x) throw()
		{
			V_DATE(this) = x.get();
			V_VT(this) = VT_DATE;
		}

		operator datetime_t() const
		{
			if (V_VT(this) == VT_DATE) return datetime_t(V_DATE(this));
			variant_t v(*this, VT_DATE);
			return datetime_t(V_DATE(v.get_var()));
		}

		variant_t& operator=(const datetime_t &x) throw()
		{
			clear();
			V_DATE(this) = x.get();
			V_VT(this) = VT_DATE;
			return *this;
		}

		//@}
		/// swap routine, fast with nothrow guarantee
		void swap(variant_t& x) throw()
		{
			::tagVARIANT t;
			memcpy(&t, this, sizeof(VARIANT));
			memcpy(this, &x, sizeof(VARIANT));
			memcpy(&x, &t, sizeof(VARIANT));
		}

		/// Assignment operator
		variant_t& operator=(const variant_t& x) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			variant_t t(x);
			swap(t);
			return *this;
		}

		//! \name Comparison operators
		//@{
		template<typename T>
		bool operator==(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return operator==( variant_t(x) );
		}

		bool operator==(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			if (V_VT(&x) != V_VT(this)) {
				if (V_VT(this) == VT_EMPTY || V_VT(&x) == VT_EMPTY) return false;
				variant_t tmp(x, V_VT(this), std::nothrow);
				if (V_VT(&tmp) != V_VT(this)) return false;
				return VARCMP_EQ == (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(tmp.get_var()), GetThreadLocale(), 0) | raise_exception) ;
			} else {
				switch (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(x.get_var()), GetThreadLocale(), 0))
				{
				case VARCMP_EQ:
				case VARCMP_NULL:
					return true;
				default:
					return false;
				}
			}
		}

		template<typename T>
		bool operator!=(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return !operator==(variant_t(x));
		}

		bool operator!=(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return !operator==(x);
		}

		template<typename T>
		bool operator<(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return operator<(variant_t(x));
		}

		bool operator<(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			if (V_VT(&x) != V_VT(this)) {
				return VARCMP_LT == (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(variant_t(x, V_VT(this)).get_var()), GetThreadLocale(), 0) | raise_exception);
			} else {
				return VARCMP_LT == (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(x.get_var()), GetThreadLocale(), 0) | raise_exception);
			}
		}

		template<typename T>
		bool operator<=(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return operator<=(variant_t(x));
		}

		template<typename T>
		bool operator>(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return operator>(variant_t(x));
		}

		bool operator>(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			if (V_VT(&x) != V_VT(this)) {
				return VARCMP_GT == (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(variant_t(x, V_VT(this)).get_var()), GetThreadLocale(), 0) | raise_exception);
			} else {
				return VARCMP_GT == (VarCmp(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(x.get_var()), GetThreadLocale(), 0) | raise_exception);
			}
		}

		bool operator<=(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return !operator>(x);
		}

		template<typename T>
		bool operator>=(const T& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return operator>=(variant_t(x));
		}

		bool operator>=(const variant_t& x) const 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			return !operator<(x);
		}

		//@}

		//! \name Mathematical operators
		//@{
//		COMET_VARIANT_OPERATOR(+,Add);

		variant_t operator+(const variant_t& x) const
	{
		VARIANT t;
		::VarAdd(const_cast<VARIANT*>(get_var()), const_cast<VARIANT*>(x.get_var()), &t) | raise_exception;
		return auto_attach(t);
	}

	variant_t& operator+=(const variant_t& x)
	{
		return operator=(operator+(x));
	}


		COMET_VARIANT_OPERATOR(-,Sub);
		COMET_VARIANT_OPERATOR(*,Mul);
		COMET_VARIANT_OPERATOR(/,Div);
		COMET_VARIANT_OPERATOR(&,And);
		COMET_VARIANT_OPERATOR(|,Or);
		COMET_VARIANT_OPERATOR(^,Xor);
		COMET_VARIANT_OPERATOR(%,Mod);

		variant_t operator-() const
		{
			VARIANT t;
			VarNeg(const_cast<VARIANT*>(get_var()), &t) | raise_exception;
			return auto_attach(t);
		}

		void change_type(VARTYPE vartype) 
#ifndef VCF_MINGW
throw(com_error)
#endif
		{
			if (vartype != V_VT(this))
				::VariantChangeTypeEx(get_var(),
				get_var(),
				GetThreadLocale(),
				0, vartype) | raise_exception;
		}

		//@}

		//! Is variant a BSTR
		bool is_string() const
		{
			return VT_BSTR == get_vt(true);
		}

		//! Is variant an IDispatch or IUnknown pointer?
		bool is_object() const
		{
			return VT_UNKNOWN == get_vt(true) || VT_DISPATCH == get_vt(true);
		}

		/*! Is variant empty.
		 * This compares strictly to VT_EMPTY.
		 */
		bool is_empty() const throw()
		{
			return VT_EMPTY == get_vt();
		}
		/*! Is variant 'NULL'.
		 * This compares strictly to VT_NULL.
		 */
		bool is_null() const throw()
		{
			return VT_NULL == get_vt();
		}

		/**! Is variant Nothing.
		 * Is this a NULL pointer, empty, or null.
		 * This returns true if the value would cleanly try_cast to a NULL
		 * com_ptr<IUnknown>.
		 */
		bool is_nothing() const throw()
		{
			switch (get_vt()) {
			case VT_DISPATCH:           return NULL == V_DISPATCH(&get());
			case VT_UNKNOWN:            return NULL == V_UNKNOWN(&get());
			case VT_DISPATCH|VT_BYREF:  return NULL == *V_DISPATCHREF(&get());
			case VT_UNKNOWN|VT_BYREF:   return NULL == *V_UNKNOWNREF(&get());
			case VT_EMPTY:
			case VT_NULL:               return true;
			}
			return false;
		}


		//! \name Accessor Functions
		//@{
		const VARIANT& get() const throw()
		{
			return *get_var();
		}

		VARTYPE get_vt() const throw()
		{
			return VARTYPE(V_VT(this));
		}

		VARTYPE get_vt(bool ignore_byref) const throw()
		{
			return ignore_byref ? VARTYPE(V_VT(this) & ~VT_BYREF) : VARTYPE(V_VT(this));
		}

		static VARIANT detach(variant_t& v) throw()
		{
			return v.detach();
		}

		VARIANT detach() throw()
		{
			VARIANT r = *get_var();
			V_VT(this) = VT_EMPTY;
			return r;
		}

		static const variant_t& create_const_reference(const VARIANT& x)
		{
			return *reinterpret_cast<const variant_t*>(&x);
		}

		static variant_t& create_reference(VARIANT& x)
		{
			return *reinterpret_cast<variant_t*>(&x);
		}

		//! [in] adapter.
		/*!
			Used when calling raw interfaces that require an [in] VARIANT argument.

			\code
				variant_t v;
				HRESULT hr = pRawInterface->raw_Method(v.in());
			\endcode

			Only use this wrapper when forced to deal with raw interface.
		*/
		VARIANT in() const throw()
		{
			return *get_var();
		}

		//! [in] adapter.
		/*!
			Used when calling raw interfaces that require an [in] VARIANT* argument.

			\code
				variant_t v;
				HRESULT hr = pRawInterface->raw_Method(v.in_ptr());
			\endcode

			Only use this wrapper when forced to deal with raw interface.
		*/
		VARIANT* in_ptr() const throw()
		{
			return const_cast<VARIANT*>(get_var());
		}

		//! [out] adapter.
		/*!
			Used when calling raw interfaces that require an [out] VARIANT * argument.

			\code
				variant_t v;
				HRESULT hr = pRawInterface->raw_MethodThatReturnsVariant(v.out());
			\endcode

			Only use this wrapper when forced to deal with raw interface.
		*/
		VARIANT* out() throw()
		{
			clear();
			new (this) variant_t();
			return get_var();
		}

		//! [in, out] adapter.
		/*!
			Used when calling raw interfaces that require an [in, out] VARIANT * argument.

			\code
				variant_t v;
				HRESULT hr = pRawInterface->raw_MethodThatChangesVariant(v.inout());
			\endcode

			Only use this wrapper when forced to deal with raw interface.
		*/
		VARIANT* inout() throw()
		{
			return get_var();
		}
		//@}

	private:

// mingw does not define these for some strange reason - ACH
#ifndef V_INT
#define V_INT(X) V_UNION(X, intVal)
#endif
#ifndef V_UINT
#define V_UINT(X) V_UNION(X, uintVal)
#endif

#define __COMET_VARAIANT_OUT(vartype) case VT_##vartype: os << V_##vartype(this); break
#define __COMET_VARAIANT_OUT_CAST(vartype,cast) case VT_##vartype: os << cast(V_##vartype(this)); break
		template<typename CH>
		std::basic_ostream<CH> &output(std::basic_ostream<CH> &os) const
		{
			switch (V_VT(this))
			{
				__COMET_VARAIANT_OUT_CAST(I1, short);
				__COMET_VARAIANT_OUT(I2);
				__COMET_VARAIANT_OUT(I4);
				__COMET_VARAIANT_OUT(INT);
				__COMET_VARAIANT_OUT_CAST(UI1, (unsigned short));
				__COMET_VARAIANT_OUT(UI2);
				__COMET_VARAIANT_OUT(UI4);
				__COMET_VARAIANT_OUT(UINT);
				__COMET_VARAIANT_OUT(R4);
				__COMET_VARAIANT_OUT(R8);
//				__COMET_VARAIANT_OUT_CAST(CY, currency_t::create_const_reference);
//				__COMET_VARAIANT_OUT_CAST(DATE, datetime_t::create_const_reference);
				default:
					os << std::basic_string<CH>(*this);
					break;
			}
			return os;
		}
#undef __COMET_VARAIANT_OUT
	public:
		friend
		std::basic_ostream<char> &operator<<(std::basic_ostream<char> &os, const variant_t &val)
		{
			return val.output(os);
		}

		friend
		std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &os, const variant_t &val)
		{
			return val.output(os);
		}

	private:
		const VARIANT* get_var() const throw()
		{
#ifndef __BORLANDC__
			return static_cast<const VARIANT*>(this);
#else
			return reinterpret_cast<const VARIANT*>(this);
#endif
		}

		VARIANT* get_var() throw()
		{
#ifdef __BORLANDC__
#if __BORLANDC__ >= 0x0550
			return reinterpret_cast<VARIANT*>(this);
#else
			return static_cast<VARIANT*>(this);
#endif
#else
			return reinterpret_cast<VARIANT*>(this);
#endif
		}
	};
	//@}

	COMET_VARIANT_FRIENDS(short);
	COMET_VARIANT_FRIENDS(int);
	COMET_VARIANT_FRIENDS(long);
	COMET_VARIANT_FRIENDS(float);
	COMET_VARIANT_FRIENDS(double);

	COMET_VARIANT_FRIENDS(const char*);
	COMET_VARIANT_FRIENDS(const wchar_t*);

	COMET_VARIANT_FRIENDS(const std::wstring&);
	COMET_VARIANT_FRIENDS(const std::string&);

	COMET_VARIANT_FRIENDS(const DECIMAL&);

} // namespace

#include <comet/error.h>
#include <comet/ptr.h>

namespace std {
	template<> inline void swap(comet::variant_t& x, comet::variant_t& y) COMET_STD_SWAP_NOTHROW
	{
		x.swap(y);
	}
}

#undef COMET_VARIANT_CONVERTERS
#undef COMET_VARIANT_CONVERTERS_EX_
#undef COMET_VARIANT_CONVERTERS_EXPLICIT
#undef COMET_VARIANT_OPERATOR
#undef COMET_VARIANT_FRIENDS

namespace comet {
	/*! \addtogroup COMType
	 */
	//@{

		inline bool operator!=(const bstr_t& b, const variant_t& v)
		{
			return v != b;
		}

		inline bool operator==(const bstr_t& b, const variant_t& v)
		{
			return v == b;
		}

		inline bool operator<(const bstr_t& b, const variant_t& v)
		{
			return v > b;
		}

		inline bool operator>(const bstr_t& b, const variant_t& v)
		{
			return v < b;
		}

		inline bool operator<=(const bstr_t& b, const variant_t& v)
		{
			return v >= b;
		}

		inline bool operator>=(const bstr_t& b, const variant_t& v)
		{
			return v <= b;
		}
	//@}
}

#pragma warning(pop)

#endif
