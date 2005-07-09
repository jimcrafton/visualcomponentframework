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

Building examples:

Most of the examples can be compiled with Borland compiler. All that fall in 
this category have 2 options for building.
1. build_bcc.bat . With this batch file you can quickly build any sample. It expects 
that you build release dll version of VCF libs.

2. You have allso 2 project files for BCB 5 IDE. One is for release dll VCF and 
another is for debug dll VCF. To use IDE project files you need to do following:

- in your CBuilder root folder create subfolder lib_patch. In there copy c0x32.obj from 
<CBuilder root>\Lib folder and rename it to c0w32.obj.

Here is a more detailed explanation why this was needed (from the VCF forum):

After quite some time I managed to create set of IDE project files for building 
VCF examples in BCB 5. Examples excluded in this release are:

- QTPlayer - This example uses QuickTime SDK that only works with visual C++.
All lib files and headers are only MSVC compatibile. If somebody
makes a port of this to BCB than this sample could be ported.

- TexLabel - Can not be compiled with BCB 5. Works only with BCB 6.

Here is one important note about building these samples.

Unfortunately in BCB project file it is not possible to specify custom startup object file. 
That is necessary with VCF because every example has main procedure. Unfortunately BCB 
project with windows application forces linkage of c0w32.obj that is startup file that 
requires winmain procedure. What we need instead is c0x32.obj - startup file that uses 
main procedure.

The only way I found to trick BCB to use different object file than standard was to create 
new folder in BCB root folder and copy there c0x32.obj and rename it to c0w32.obj. 
After that every IDE project file must have this folder placed first in a list of folders 
with lib files
(Project\Options\Directories/Conditionals - line "Library path").

All example project files assume that path of this folder is $(BCB)\lib_patch.

So create folder lib_patch in the root of BCB installation and copy/rename mentioned startup 
object file. This trick is needed only for windows applications. For console applications it 
is enough to create standard console project in BCB.

In every folder for a example there are two project files - <projectname>_bcb5.bpr and 
<projectname>_bcb5_d.bpr . First one is for release build and another is for debug build.
In <VCFROOT>\Examples folder are located project group files Examples_bcb5.bpg 
(release projects) and Examples_bcb5_debug.bpg (debug projects)


Any comments, hints, ideas are welcome.

contact me on kiklop@fibertel.com.ar

Darko Miletic   