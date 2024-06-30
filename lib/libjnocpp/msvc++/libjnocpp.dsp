# Microsoft Developer Studio Project File - Name="libjnocpp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libjnocpp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libjnocpp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libjnocpp.mak" CFG="libjnocpp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libjnocpp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libjnocpp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBJNOCPP_EXPORTS" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GR /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "LIBJNOCPP_EXPORTS" /D "iNexumDll" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /machine:I386

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBJNOCPP_EXPORTS" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GR /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "LIBJNOCPP_EXPORTS" /D "iNexumDll" /D "iNxmDebug" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /out:"Debug/libjnocppd.dll" /pdbtype:sept
# Begin Special Build Tool
WkspDir=.
SOURCE="$(InputPath)"
PostBuild_Cmds="C:\Documents and Settings\nvojinov.TSE\My Documents\working\doc++\docxx" --dir "$(WkspDir)\html" "$(WkspDir)\dxx\*.dxx"
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "libjnocpp - Win32 Release"
# Name "libjnocpp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Array.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\BlockData.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\BuiltinObject.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Class.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\ClassObject.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\util\Debug.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\InetAddress.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\lang\java_lang.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\JavaObjectParser.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\JavaObjectSerializer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\javaObjLexer.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\javaObjParse.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\os\libjnocpp_win32.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Member.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\io\ObjectInputStream.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\io\ObjectOutputStream.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Serializable.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableCreator.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableVoidPointerArray.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializeBuiltinType.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializeString.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\ServerSocket.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\SingletonVictim.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\Socket.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\socketbuf.cpp"
# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\Types.cpp"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Array.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\ArrayObject.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\AutoPtr.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\BlockData.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\BuiltinObject.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Class.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\ClassObject.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Creator.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\util\Debug.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\definitions.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Entity.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\lang\Exception.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\ExceptionObject.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Factory.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\InetAddress.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\io\IOException.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\lang\java_lang.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\java_serializable.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\JavaObjectParser.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\JavaObjectSerializer.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\javaObjParse.hpp"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\javaObjParser.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\JLong.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Map.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Member.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Object.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\io\ObjectInputStream.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\io\ObjectOutputStream.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\PrimitiveValue.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Serializable.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableArray.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableCreator.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializablePointerArray.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableTypePointerArray.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializableVoidPointerArray.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\Serialize.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializeBuiltinType.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\SerializeString.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\ServerSocket.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Singleton.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\SingletonVictim.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\Socket.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\SocketAddress.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\socketbuf.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\java\net\SocketException.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Stack.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\StringLableCreator.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\StringObject.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\Throwable.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\Types.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\stl\Vector.h"

!IF  "$(CFG)" == "libjnocpp - Win32 Release"

!ELSEIF  "$(CFG)" == "libjnocpp - Win32 Debug"

# PROP Exclude_From_Build 1

!ENDIF 

# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE="..\..\..\src\c++\inexum\OSP\javaObjParse.y"
# End Source File
# End Group
# End Target
# End Project
