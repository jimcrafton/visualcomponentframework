# Microsoft Developer Studio Project File - Name="FoundationKitDLL" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=FOUNDATIONKITDLL - WIN32 DEBUG
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKitDLL.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "FoundationKitDLL.mak" CFG="FOUNDATIONKITDLL - WIN32 DEBUG"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "FoundationKitDLL - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "FoundationKitDLL - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "FoundationKitDLL - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\ReleaseDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FOUNDATIONKITDLL_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O1 /I "$(VCF_INCLUDE)" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_EXPORTS" /Yu"vcf/FoundationKit/FoundationKit.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/FoundationKit_vc6.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /dll /machine:I386 /out:"..\..\..\bin\FoundationKit_vc6.dll"
# SUBTRACT LINK32 /pdb:none /debug


!ELSEIF  "$(CFG)" == "FoundationKitDLL - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "FoundationKitDLL___Win32_Debug"
# PROP BASE Intermediate_Dir "FoundationKitDLL___Win32_Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\..\..\lib\"
# PROP Intermediate_Dir "vc6\DebugDLL\"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FOUNDATIONKITDLL_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /I "$(VCF_INCLUDE)" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "FOUNDATIONKIT_DLL" /D "FOUNDATIONKIT_EXPORTS" /Fd"..\..\..\bin\FoundationKit_vc6_d.pdb" /Yu"vcf/FoundationKit/FoundationKit.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo /o"../../../bin/FoundationKit_vc6_d.bsc"
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 Rpcrt4.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib version.lib /nologo /dll /profile /debug /machine:I386 /out:"..\..\..\bin\FoundationKit_vc6_d.dll"

!ENDIF 

# Begin Target

# Name "FoundationKitDLL - Win32 Release"
# Name "FoundationKitDLL - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitPrivate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitSelectLib.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FrameworkConfig.h
# End Source File
# End Group
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKit.cpp
# ADD CPP /Yc"vcf/FoundationKit/FoundationKit.h"
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FoundationKitRTTI.inl
# End Source File
# End Group
# Begin Group "Peers"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Condition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Condition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FilePeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FilePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FileStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32FileStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LibraryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LocalePeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32LocalePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Peer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Peer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessIORedirector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ProcessPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Registry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32RunLoopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SemaphorePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ThreadManagerPeer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Win32ThreadManagerPeer.h
# End Source File
# End Group
# Begin Group "Exceptions"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicException.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicFileError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CantCreateObjectException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassNotFound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorStrings.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileIOError.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileNotFound.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidPointerException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InvalidStateException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoFreeMemException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoPeerFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoSuchElementException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NotImplementedException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NoToolKitFoundException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\OutOfBoundsException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RuntimeException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TypeCastException.h
# End Source File
# End Group
# Begin Group "Events"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Delegate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Event.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Event.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\EventHandler.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\EventHandler.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\NotifyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\OutputReadyEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PropertyChangeEvent.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadEvent.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadEvent.h
# End Source File
# End Group
# Begin Group "IO"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\BasicOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Directory.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Directory.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\File.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\File.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FilePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemoryStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemoryStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MemStreamUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Persistable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Stream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Stream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextOutputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextOutputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantDataStream.h
# End Source File
# End Group
# Begin Group "Utils"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommandLine.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommandLine.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\DateTime.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\DateTime.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorLog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ErrorLog.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Library.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Library.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MessageLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MessageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MIMEType.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MIMEType.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Parser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessWithRedirectedIO.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Registry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Registry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringsMessageLoader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringsMessageLoader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringUtils.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\StringUtils.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextCodec.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\TextCodec.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFProcess.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFProcess.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\XMLParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\XMLParser.h
# End Source File
# End Group
# Begin Group "Core"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\CommonDefines.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Dictionary.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Dictionary.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Enumerator.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Format.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Locales.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Locales.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Object.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Object.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ObjectWithEvents.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ObjectWithEvents.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PackageInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\PackageInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProgramInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Resource.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Resource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundle.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundle.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopSource.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\System.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\System.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemToolkit.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemToolkit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCF.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFChar.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFMath.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFMath.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFString.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFString.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFulong64.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\WarningsOffVc.h
# End Source File
# End Group
# Begin Group "Peer Interfaces"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ConditionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\FileStreamPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\LibraryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\LocalePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\MutexPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessIORedirectionPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ProcessPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RegistryPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ResourceBundlePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoopPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SemaphorePeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SystemPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManagerPeer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadPeer.h
# End Source File
# End Group
# Begin Group "RTTI"

# PROP Default_Filter "*.h;*.cpp"
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Class.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Class.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassInfo.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassRegistry.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ClassRegistry.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Enum.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Field.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Interface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InterfaceClass.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\InterfaceClass.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Method.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Property.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RTTIMacros.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VariantData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\VCFRTTIImpl.h
# End Source File
# End Group
# Begin Group "Threads"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Condition.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Condition.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Lock.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoop.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\RunLoop.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Runnable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Semaphore.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Semaphore.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\SynchObject.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadKit.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManager.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\ThreadManager.h
# End Source File
# Begin Source File

SOURCE=..\..\..\src\vcf\FoundationKit\Waitable.h
# End Source File
# End Group
# End Target
# End Project
