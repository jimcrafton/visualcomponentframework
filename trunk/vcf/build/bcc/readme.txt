Couple of things I should say about this first port of VCF to Borland C++
compiler:

1. It is only tested on BCB6 with SP4 and linker update installed. It is not
   possible to link debug libraries without linker update.
   To obtain this update go to registered users section at www.borland.com and
   download appropriate patch.

1a. To add new info on this: library has been tested with BCB 6, BCB 5 with and 
    without SP and it works.

2. Since Borland did not ship glaux.lib and comsupp.lib with their compiler I 
   had to supply these lib's. Fortunately I did that quite some time ago.
   Interested people can take a look at http://makefiles.lebeausoftware.org/
   for these and some other missing lib's for Borland compiler.
   These libs are located in <PATH_TO_VCF>\build\bcc\missing_libs .
   To use them copy them either to <PATH_TO_BCB_INST>\Lib or <PATH_TO_VCF>\Lib .

3. Locate file bcc32.cfg in <PATH_TO_BCB_INST>\bin and make sure it looks like 
   this:
-I"C:\bcb6\Include";"C:\bcb6\Include\vcl";"C:\bcb6\Include\Atl"
-L"C:\bcb6\lib";"C:\bcb6\lib\obj";"C:\bcb6\lib\release";"C:\bcb6\lib\PSDK"
  Of course replace C:\bcb6\ part with appropriate path where you installed bcb.

4. Locate file ilink32.cfg in <PATH_TO_BCB_INST>\bin and make sure it looks like 
   this:
-L"C:\bcb6\lib";"C:\bcb6\lib\obj";"C:\bcb6\lib\release";"C:\bcb6\lib\PSDK"
  Of course replace C:\bcb6\ part with appropriate path where you installed bcb.

5. After you do all this preparations build libraries by issuing this command 
   from <PATH_TO_VCF>\build\bcc :
   make -fvcfAllLibs.mak
   
   This will build all dynamic and static libs. 
   If for some reason name of your make util is not make.exe open vcfAllLibs.mak
   and change MK variable to the name of your make util. Do the same thing in 
   vcfAllDynStatLibs.mak.

Any comments, hints, ideas are welcome.

contact me on kiklop@fibertel.com.ar

Darko Miletic   