========================================================================
    VCF Application Wizard : "[!output PROJECT_NAME]" Project Overview
========================================================================

The VCF Application Wizard has created this "[!output PROJECT_NAME]" project for you as a starting point.

The application will link [!if LIB_DYNAMIC]dynamically[!endif][!if LIB_STATIC]statically[!endif] to the VCF libraries.

List of functionality:
-----------------------------------------------------
[!if FILE_MENU]Standard File menu
[!endif]
[!if UNDO_REDO]Undo/redo support
[!endif]
[!if HELP_MENU]Minimal Help menu
[!endif]
[!if SPLASH_SCREEN]Splash screen
[!endif]

[!if LIB_NET]
Additionally, the application supports VCF Net.[!endif][!if LIB_REMOTE]
Additionally, the application supports VCF Net and VCF Remote.[!endif]



The project consists of the following files:
------------------------------------------------------

Main Entry Point:
	[!output PROJECT_NAME].cpp

Application
	[!output PROJECT_NAME]Application.h
	[!output PROJECT_NAME]Application.cpp
[! if SPLASH_SCREEN]

Splash Screen
	SplashScreen.h
	SplashScreen.cpp
	res\app.rc
	res\splash.bmp
[!endif]

Main Window
	MainWindow.h
	MainWindow.cpp
[! if HELP_MENU]

About Box
	[!output PROJECT_NAME]About.h
	[!output PROJECT_NAME]About.cpp
[!endif]


Please look in the 'examples' folder for hints on how to progress. ;-)
