If you need to rebuild the scan.cpp and tab.cpp files then you need to install flex, bison and sed.
Make sure that either flex, bison, and sed are in your path or go to Tools > Options and pick
executable directories, and add the directories where flex, bison and sed are found. If you are
using cygwin, don't forget to also add the cygwin bin directory too (for me it's D:\cygwin\bin).

To generate the files select the "Win32 Generate YY and LL files" configuration and build. 
Then select the "Win32 Release" or "Win32 Debug" configuration to build the rest.


Many, many thanks to duff (http://vcf.sourceforge.net/forums/index.php?showuser=83) for
contributing this!!!
The initial posting for this can be seen here:
http://vcf.sourceforge.net/forums/index.php?showtopic=213

