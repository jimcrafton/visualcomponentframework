# Microsoft Developer Studio Project File - Name="FoundationKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=FoundationKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKit.mak" CFG="FoundationKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FoundationKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "FoundationKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FoundationKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../../../lib/"
# PROP Intermediate_Dir "vc6/ReleaseS/"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MD /W3 /WX /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "BUILD_FRAMEWORK_LIB" /Yu"FoundationKit.h" /FD /c
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/FoundationKit_vc6_s.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/FoundationKit_vc6_s.lib"

!ELSEIF  "$(CFG)" == "FoundationKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../../../lib/"
# PROP Intermediate_Dir "vc6/DebugS/"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /WX /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "NO_MFC" /D "BUILD_FRAMEWORK_LIB" /Fd"../../../lib/FoundationKit_vc6_sd.pdb" /Yu"FoundationKit.h" /FD /GZ /c
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../lib/FoundationKit_vc6_sd.bsc"
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"../../../lib/FoundationKit_vc6_sd.lib"

!ENDIF 

# Begin Target

# Name "FoundationKit - Win32 Release"
# Name "FoundationKit - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=../../../include/FoundationKit.h
# End Source File
# Begin Source File

SOURCE=../../../include/FoundationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/FoundationKitSelectLib.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File


SOURCE=../../../src/utils/Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/core/FoundationKit.cpp
# ADD CPP /Yc"FoundationKit.h"
# End Source File
# Begin Source File

SOURCE=../../../include/FoundationKitRTTI.inl
# End Source File
# Begin Source File

SOURCE=../../../src/utils/Library.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/core/Locales.cpp
# End Source File
# End Group
# Begin Group "Peers"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=../../../src/implementerkit/Win32Condition.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Condition.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32FilePeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/ImplementerKit/Win32FilePeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32FileStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32FileStream.h
# End Source File
# Begin Source File

SOURCE=../../../src/implementerkit/Win32LibraryPeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerkit/Win32LibraryPeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/implementerkit/Win32LocalePeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32LocalePeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Mutex.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Mutex.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Peer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Peer.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32ProcessIORedirector.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32ProcessIORedirector.h
# End Source File
# Begin Source File

SOURCE=../../../src/implementerkit/Win32ProcessPeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerkit/Win32ProcessPeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/implementerkit/Win32Registry.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerkit/Win32Registry.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32SemaphorePeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32SemaphorePeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32SystemPeer.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32SystemPeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32SystemToolkit.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=../../../src/ImplementerKit/Win32Thread.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/implementerKit/Win32Thread.h
# End Source File
# End Group
# Begin Group "Exceptions"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=../../../src/Exceptions/BasicException.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/BasicException.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/BasicFileError.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/CantCreateObjectException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/ClassNotFound.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/ErrorStrings.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/FileIOError.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/FileNotFound.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/InvalidPeer.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/InvalidPointerException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/NoFreeMemException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/NoPeerFoundException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/NoSuchElementException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/OutOfBoundsException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/ProcessException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/PropertyChangeException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/RuntimeException.h
# End Source File
# Begin Source File

SOURCE=../../../include/exceptions/TypeCastException.h
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=../../../include/events/Delegate.h
# End Source File
# Begin Source File

SOURCE=../../../src/Events/Event.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/events/Event.h
# End Source File
# Begin Source File

SOURCE=../../../src/Events/EventHandler.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/events/EventHandler.h
# End Source File
# Begin Source File

SOURCE=../../../include/events/NotifyEvent.h
# End Source File
# Begin Source File

SOURCE=../../../include/events/OutputReadyEvent.h
# End Source File
# Begin Source File

SOURCE=../../../src/Events/PropertyChangeEvent.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/events/PropertyChangeEvent.h
# End Source File
# Begin Source File

SOURCE=../../../src/Events/ThreadEvent.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/events/ThreadEvent.h
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=../../../src/IO/BasicInputStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/BasicInputStream.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/BasicOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/BasicOutputStream.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/Directory.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/Directory.h
# End Source File
# Begin Source File

SOURCE=../../../src/io/File.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/File.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/FilePath.h
# End Source File
# Begin Source File

SOURCE=../../../include/Implementer/FilePeer.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/FileStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/FileStream.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/FileStreamPeer.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/FileUtils.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/MemoryStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/MemoryStream.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/MemStreamUtils.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/Persistable.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/Stream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/Stream.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/TextInputStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/TextInputStream.h
# End Source File
# Begin Source File

SOURCE=../../../src/IO/TextOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/io/TextOutputStream.h
# End Source File
# Begin Source File

SOURCE=../../../include/io/VariantDataStream.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=../../../src/Utils/CommandLine.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/CommandLine.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Condition.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Condition.h
# End Source File
# Begin Source File

SOURCE=../../../src/utils/DateTime.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/DateTime.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Dictionary.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Enumerator.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/ErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/ErrorLog.h
# End Source File
# Begin Source File


SOURCE=../../../src/Utils/FilePath.cpp
# End Source File
# Begin Source File

SOURCE=../../../src/IO/FileUtils.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Library.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Lock.h
# End Source File
# Begin Source File

SOURCE=../../../src/utils/MessageLoader.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/MessageLoader.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Mutex.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Mutex.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Parser.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Parser.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/ProcessWithRedirectedIO.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/ProcessWithRedirectedIO.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Registry.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Registry.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Runnable.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Semaphore.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Semaphore.h
# End Source File
# Begin Source File

SOURCE=../../../src/utils/StringsMessageLoader.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/StringsMessageLoader.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/StringUtils.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/SynchObject.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/System.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/System.h
# End Source File
# Begin Source File

SOURCE=../../../src/utils/SystemToolkit.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=../../../src/utils/TextCodec.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/TextCodec.h
# End Source File
# Begin Source File

SOURCE=../../../src/Utils/Thread.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/Thread.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/VCFChar.h
# End Source File
# Begin Source File

SOURCE=../../../src/core/VCFMath.cpp
# End Source File
# Begin Source File


SOURCE=../../../src/Utils/VCFProcess.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/VCFProcess.h
# End Source File

# Begin Source File

SOURCE=../../../src/utils/VCFString.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/VCFString.h
# End Source File
# Begin Source File

SOURCE=../../../include/utils/VCFulong64.h
# End Source File
# Begin Source File


SOURCE=../../../include/utils/Waitable.h
# End Source File
# Begin Source File


SOURCE=../../../src/Utils/XMLParser.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/utils/XMLParser.h
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter "*.h"
# Begin Source File


SOURCE=../../../include/core/CommonDefines.h
# End Source File
# Begin Source File


SOURCE=../../../include/core/FrameworkConfig.h
# End Source File
# Begin Source File


SOURCE=../../../include/core/Locales.h
# End Source File
# Begin Source File


SOURCE=../../../src/core/Object.cpp
# End Source File
# Begin Source File


SOURCE=../../../include/core/Object.h
# End Source File
# End Group
# Begin Group "Peer Interfaces"

# PROP Default_Filter "*.h"
# Begin Source File


SOURCE=../../../src/core/ObjectWithEvents.cpp
# End Source File
# Begin Source File


SOURCE=../../../include/core/ObjectWithEvents.h
# End Source File
# Begin Source File


SOURCE=../../../include/core/VCF.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/VCFMath.h
# End Source File
# Begin Source File

SOURCE=../../../include/core/WarningsOffVc.h
# End Source File
# End Group
# Begin Group "Peer Interfaces"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=../../../include/implementer/ConditionPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/LibraryPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/LocalePeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/MutexPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/ProcessIORedirectionPeer.h
# End Source File
# End Group
# Begin Group "RTTI"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File


SOURCE=../../../include/implementer/ProcessPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/RegistryPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/utils/SemaphorePeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/utils/SystemPeer.h
# End Source File
# Begin Source File


SOURCE=../../../include/implementer/ThreadPeer.h
# End Source File

# End Group
# Begin Group "RTTI"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=../../../src/rtti/Class.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/rtti/Class.h
# End Source File
# Begin Source File

SOURCE=../../../include/rtti/ClassInfo.h
# End Source File
# Begin Source File

SOURCE=../../../src/rtti/ClassRegistry.cpp
# End Source File
# Begin Source File

SOURCE=../../../include/rtti/ClassRegistry.h
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/Enum.h
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/Field.h
# End Source File
# Begin Source File


SOURCE=../../../src/rtti/InterfaceClass.cpp
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/InterfaceClass.h
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/Method.h
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/Property.h
# End Source File
# Begin Source File


SOURCE=../../../src/core/VariantData.cpp
# End Source File
# Begin Source File


SOURCE=../../../include/core/VariantData.h
# End Source File
# Begin Source File


SOURCE=../../../include/rtti/VCFRTTIImpl.h
# End Source File
# End Group
# End Target
# End Project
