#######################################################
# MAKEFILE for building all  VCF    libs              #
#                                                     #
#                                                     #
# (c) 2004 by Darko Miletic                           #
# e-mail: kiklop@fibertel.com.ar                      # 
#######################################################
.autodepend

MK=make

all: static_libs dynamic_libs

clean: static_libs_clean dynamic_libs_clean


static_libs::
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=LIB -DBMODE=DEBUG
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=LIB -DBMODE=RELEASE

dynamic_libs::
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=DEBUG
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=RELEASE

dynamic_libs_rel:
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=RELEASE

dynamic_libs_dbg:
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=DEBUG

static_libs_clean::
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=LIB -DBMODE=DEBUG clean
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=LIB -DBMODE=RELEASE clean

dynamic_libs_clean::
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=DEBUG clean
	@$(MK) -fvcfAllDynStatLibs.mak -DTARGET=DLL -DBMODE=RELEASE clean
