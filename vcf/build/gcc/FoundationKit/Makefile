# "$Id$"
#
# Makefile for FoundationKit of the Visual Component Framework
#
# Copyright 2000 by Endre Somogyi
# please mail any questions to etsomogy@ouray.cudenver.edu
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Library General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Library General Public License for more details.
#
# You should have received a copy of the GNU Library General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# Please report all bugs and problems to "fltk-bugs@fltk.org".
#

SHELL=/bin/sh

# basic GTK+ app makefile

SRC = ../../../src
INC = ../../../include

.SUFFIXES: .cpp .o
.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c -DVCF_GCC $*.cpp

SOURCES = $(SRC)/Exceptions/BasicException.cpp \
$(SRC)/IO/BasicInputStream.cpp \
$(SRC)/IO/BasicOutputStream.cpp \
$(SRC)/core/Class.cpp \
$(SRC)/core/ClassRegistry.cpp \
$(SRC)/IO/Directory.cpp \
$(SRC)/Utils/ErrorLog.cpp \
$(SRC)/Events/Event.cpp \
$(SRC)/Events/EventHandler.cpp \
$(SRC)/IO/File.cpp \
$(SRC)/IO/FileStream.cpp \
$(SRC)/IO/FileUtils.cpp \
$(SRC)/core/FoundationKit.cpp \
$(SRC)/core/InterfaceClass.cpp \
$(SRC)/utils/Library.cpp \
$(SRC)/core/Locales.cpp \
$(SRC)/IO/MemoryStream.cpp \
$(SRC)/Utils/Mutex.cpp \
$(SRC)/core/Object.cpp \
$(SRC)/core/ObjectWithEvents.cpp \
$(SRC)/utils/Parser.cpp \
$(SRC)/core/Point.cpp \
$(SRC)/Events/PropertyChangeEvent.cpp \
$(SRC)/core/Rect.cpp \
$(SRC)/utils/Registry.cpp \
$(SRC)/IO/Stream.cpp \
$(SRC)/Utils/StringUtils.cpp \
$(SRC)/Utils/System.cpp \
$(SRC)/Utils/SystemToolkit.cpp \
$(SRC)/IO/TextInputStream.cpp \
$(SRC)/IO/TextOutputStream.cpp \
$(SRC)/Utils/Thread.cpp \
$(SRC)/Events/ThreadEvent.cpp \
$(SRC)/core/VCFMath.cpp \
$(SRC)/utils/VCFProcess.cpp \


INCLUDES = -I $(INC)/core -I $(INC)/events -I $(INC)/dragdrop -I $(INC)/exceptions -I $(INC)/io \
-I $(INC)/utils -I $(INC)/implementer -I $(INC)/implementerkit -I $(INC)/graphics -I /usr/include/g++3

OBJS    = ${SOURCES:.cpp=.o}
CFLAGS  = -fpic

LDADD   = -shared 
DEFINES = -Dgtk
CC      = gcc
PACKAGE = FoundationKit.so

all : ${OBJS}
	${CC} -o ${PACKAGE} ${OBJS} ${LDADD} 

link : *.o
	${CC} -o ${PACKAGE} *.o ${LDADD} 
# end of file
