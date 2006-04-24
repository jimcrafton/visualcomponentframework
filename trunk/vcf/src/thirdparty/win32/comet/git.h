/** \file
  * Global Interface Table wrapper.
  */
/*
 * Copyright © 2000, 2001 Sofus Mortensen
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

#ifndef COMET_GIT_H
#define COMET_GIT_H

#include <comet/config.h>

#include <comet/ptr.h>

namespace comet {
	/*! \addtogroup COMType
	 */
	//@{

	class GIT;

	/// Type-safe GIT Cookie.
	template<typename Itf> class GIT_cookie
	{
		friend class GIT;
	public:
		GIT_cookie(const GIT_cookie& c) : cookie_(c.cookie_) {}
		explicit GIT_cookie(DWORD c) : cookie_(c) {}

		DWORD get_cookie() { return cookie_; }
	private:	
		DWORD cookie_;
	};

	/// Global Interface Table wrapper.
	class GIT {
	public:
		GIT() : git_(CLSID_StdGlobalInterfaceTable)
		{}

		/** Register Interface in the GIT.
		  * \param ptr Interface to register.
		  * \return Type-safe cookie.
		  */
		template<typename Itf>
		GIT_cookie<Itf> register_interface(com_ptr<Itf>& ptr)
		{
			DWORD cookie;
			git_->RegisterInterfaceInGlobal(ptr.get(), uuidof<Itf>(), &cookie) | raise_exception;
			return GIT_cookie<Itf>(cookie);
		}

		/** Retrieve Interface in the GIT.
		  * \param c Cookie
		  * \return Marshalled interface.
		  */
		template<typename Itf>
		com_ptr<Itf> get_interface(GIT_cookie<Itf>& c)
		{
			Itf* itf;
			git_->GetInterfaceFromGlobal(c.get_cookie(), uuidof<Itf>(), reinterpret_cast<void**>(&itf)) | raise_exception;
			return auto_attach(itf);
		}

		/** Revoke the cookie from the GIT.
		  * \param c Cookie.
		  */
		template<typename Itf>
		void revoke_interface(GIT_cookie<Itf>& c)
		{
			git_->RevokeInterfaceFromGlobal(c.get_cookie()) | raise_exception;
		}

	private:
		com_ptr<::IGlobalInterfaceTable> git_;
	};
	//@}

} // namespace comet

#endif
