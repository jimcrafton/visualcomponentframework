#ifndef MK1MF_BUILD
  /* auto-generated by Configure for crypto/cversion.c:
   * for Unix builds, crypto/Makefile.ssl generates functional definitions;
   * Windows builds (and other mk1mf builds) compile cversion.c with
   * -DMK1MF_BUILD and use definitions added to this file by util/mk1mf.pl. */
  #error "Windows builds (PLATFORM=VC-WIN32) use mk1mf.pl-created Makefiles"
#endif
#ifdef MK1MF_PLATFORM_VC_WIN32
  /* auto-generated/updated by util/mk1mf.pl for crypto/cversion.c */
  #define CFLAGS "cl  /Od -DDEBUG -D_DEBUG /MDd /W3 /WX /GF /Gy /Zi /nologo -DOPENSSL_SYSNAME_WIN32 -DWIN32_LEAN_AND_MEAN -DL_ENDIAN -DDSO_WIN32 -D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -DBN_ASM -DMD5_ASM -DSHA1_ASM -DRMD160_ASM -DOPENSSL_USE_APPLINK -I. /Fdssleay32d.pdb -DOPENSSL_NO_CAMELLIA -DOPENSSL_NO_RC5 -DOPENSSL_NO_MDC2 -DOPENSSL_NO_KRB5 -DOPENSSL_NO_DYNAMIC_ENGINE    "
  #define PLATFORM "VC-WIN32"
  #define DATE "Wed Oct 31 18:26:37 2007"
#endif