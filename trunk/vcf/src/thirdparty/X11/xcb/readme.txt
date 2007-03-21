To install the xcb libraries that you'll need, just run the build.sh script.
If you prefer to do this by hand then you need to do the following:

install git

if you don't have the following programs, you'll need to install them

pkgconfig 0.15.0
automake 1.7
autoconf 2.50
libtool 1.5.6
check (but see NoCheck if you don't want to install this)
xsltproc
gperf 3.0.1

Note that the following order matters - don't build in 
any other order, unless you know *alot* about XCB.

cd macros
./autogen.sh
make
sudo make install

export ACLOCAL="aclocal -I /usr/local/share/aclocal"

cd ../xproto
./autogen.sh
make
sudo make install



cd ../libXau
./autogen.sh
make
sudo make install

cd ../pthread-stubs
./autogen.sh
make
sudo make install



cd ../proto
./autogen.sh
make
sudo make install


cd ../libxcb
./autogen.sh
make
sudo make install


cd ../util
./autogen.sh
make
sudo make install

You should have everything you need to build successfully. 
