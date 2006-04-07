#######################################################
# MAKEFILE for building all  VCF    libs              #
#                                                     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

MK=make

!ifndef FREECOMP
FREECOMP = TRUE
!endif

!if $(FREECOMP) != TRUE && $(FREECOMP) != FALSE
!  error Illegal value for FREECOMP option
!endif

all: static_libs dynamic_libs

clean: static_libs_clean dynamic_libs_clean

static_libs: static_libs_rel static_libs_dbg

dynamic_libs: dynamic_libs_rel dynamic_libs_dbg

dynamic_libs_clean: dynamic_libs_rel_clean dynamic_libs_dbg_clean

static_libs_clean: static_libs_rel_clean static_libs_dbg_clean

dynamic_libs_rel:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=DLL -DBMODE=RELEASE

dynamic_libs_dbg:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=DLL -DBMODE=DEBUG

static_libs_rel:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=LIB -DBMODE=RELEASE

static_libs_dbg:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=LIB -DBMODE=DEBUG

static_libs_dbg_clean:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=LIB -DBMODE=DEBUG clean
	
static_libs_rel_clean:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=LIB -DBMODE=RELEASE clean

dynamic_libs_dbg_clean:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=DLL -DBMODE=DEBUG clean
	
dynamic_libs_rel_clean:
	@$(MK) -fvcfAllDynStatLibs.mak -DFREECOMP=$(FREECOMP) -DTARGET=DLL -DBMODE=RELEASE clean
