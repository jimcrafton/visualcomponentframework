
SHELL=/bin/sh


# basic gcc app makefile

SRC = ../../../src
INC = ../../../include

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
$(SRC)/Utils/Library.cpp \
$(SRC)/core/Locales.cpp \
$(SRC)/IO/MemoryStream.cpp \
$(SRC)/Utils/Mutex.cpp \
$(SRC)/core/Object.cpp \
$(SRC)/core/ObjectWithEvents.cpp \
$(SRC)/Utils/Parser.cpp \
$(SRC)/core/Point.cpp \
$(SRC)/Events/PropertyChangeEvent.cpp \
$(SRC)/core/Rect.cpp \
$(SRC)/Utils/Registry.cpp \
$(SRC)/IO/Stream.cpp \
$(SRC)/Utils/StringUtils.cpp \
$(SRC)/Utils/System.cpp \
$(SRC)/Utils/SystemToolkit.cpp \
$(SRC)/IO/TextInputStream.cpp \
$(SRC)/IO/TextOutputStream.cpp \
$(SRC)/Utils/Thread.cpp \
$(SRC)/Events/ThreadEvent.cpp \
$(SRC)/core/VCFMath.cpp \
$(SRC)/Utils/VCFProcess.cpp \
$(SRC)/ImplementerKit/LinuxPeer.cpp \
$(SRC)/ImplementerKit/LinuxFilePeer.cpp \
$(SRC)/ImplementerKit/LinuxFileStream.cpp

OBJ_DIR = ./objs

OBJ_LIST = $(OBJ_DIR)/BasicException.o \
$(OBJ_DIR)/BasicInputStream.o \
$(OBJ_DIR)/BasicOutputStream.o \
$(OBJ_DIR)/Class.o \
$(OBJ_DIR)/ClassRegistry.o \
$(OBJ_DIR)/Directory.o \
$(OBJ_DIR)/ErrorLog.o \
$(OBJ_DIR)/Event.o \
$(OBJ_DIR)/EventHandler.o \
$(OBJ_DIR)/File.o \
$(OBJ_DIR)/FileStream.o \
$(OBJ_DIR)/FileUtils.o \
$(OBJ_DIR)/FoundationKit.o \
$(OBJ_DIR)/InterfaceClass.o \
$(OBJ_DIR)/Library.o \
$(OBJ_DIR)/Locales.o \
$(OBJ_DIR)/MemoryStream.o \
$(OBJ_DIR)/Mutex.o \
$(OBJ_DIR)/Object.o \
$(OBJ_DIR)/ObjectWithEvents.o \
$(OBJ_DIR)/Parser.o \
$(OBJ_DIR)/Point.o \
$(OBJ_DIR)/PropertyChangeEvent.o \
$(OBJ_DIR)/Rect.o \
$(OBJ_DIR)/Registry.o \
$(OBJ_DIR)/Stream.o \
$(OBJ_DIR)/StringUtils.o \
$(OBJ_DIR)/System.o \
$(OBJ_DIR)/SystemToolkit.o \
$(OBJ_DIR)/TextInputStream.o \
$(OBJ_DIR)/TextOutputStream.o \
$(OBJ_DIR)/Thread.o \
$(OBJ_DIR)/ThreadEvent.o \
$(OBJ_DIR)/VCFMath.o \
$(OBJ_DIR)/VCFProcess.o \
$(OBJ_DIR)/LinuxPeer.o \
$(OBJ_DIR)/LinuxFilePeer.o \
$(OBJ_DIR)/LinuxFileStream.o

INCLUDES = -I $(INC)/core -I $(INC)/events -I $(INC)/dragdrop -I $(INC)/exceptions -I $(INC)/io \
-I $(INC)/utils -I $(INC)/implementer -I $(INC)/implementerKit -I $(INC)/graphics -I /usr/include/g++3

#OBJS    = ${SOURCES:.cpp=.o}



CFLAGS  = -fpic

LDADD   = -shared
DEFINES = -Dgtk
CC      = g++
#PACKAGE = libFoundationKit.a

libFoundationKit_shared.so : $(OBJ_LIST)
	echo linking

$(OBJ_LIST) : $(SOURCES)
	$(CC) $(CFLAGS) $(INCLUDES) -c -DVCF_GCC $(SOURCES)