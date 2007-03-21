#!/bin/bash

#look for required programs
if [ `which xsltproc` ] 
then
	echo "xsltproc found."
else
	echo "xsltproc wasn't found. Either it's not on your PATH, or you need to install it."
	echo "exiting build script."
	exit
fi


if [ `which pkg-config` ] 
then
	echo "pkg-config found."
else
	echo "pkg-config wasn't found. Either it's not on your PATH, or you need to install it."
	echo "exiting build script."
	exit
fi

if [ `which automake` ] 
then
	echo "automake found."
else
	echo "automake wasn't found. Either it's not on your PATH, or you need to install it."
	echo "exiting build script."
	exit
fi

if [ `which autoconf` ] 
then
	echo "autoconf found."
else
	echo "autoconf wasn't found. Either it's not on your PATH, or you need to install it."
	echo "exiting build script."
	exit
fi


if [ `which libtool` ] 
then
	echo "libtool found."
else
	echo "libtool wasn't found. Either it's not on your PATH, or you need to install it."
	echo "exiting build script."
	exit
fi


cd macros
./autogen.sh
make
if [ !`sudo make install` ]
then
	echo "you need an administrator (root) password to install."
	exit
fi

cd ../

export ACLOCAL="aclocal -I /usr/local/share/aclocal"

cd ./xproto
./autogen.sh
make
sudo make install

cd ../

cd ./libXau
./autogen.sh
make
sudo make install

cd ../

cd ./pthread-stubs
./autogen.sh
make
sudo make install
cd ../


cd ./proto
./autogen.sh
make
sudo make install
cd ../

cd ./libxcb
./autogen.sh
make
sudo make install
cd ../

cd ./util
./autogen.sh
make
sudo make install
cd ../

