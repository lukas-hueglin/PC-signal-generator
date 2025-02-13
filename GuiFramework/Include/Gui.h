#pragma once

// if windows is used
#ifdef WIN32

	// include important headers
	#include<Windows.h>
	#include <windowsx.h>
	#include <d2d1.h>
	#include <d2d1_1.h>
	#include <dwrite.h>

	// add lib comments
	#pragma comment(lib, "d2d1")
	#pragma comment(lib, "dwrite")

	// define macros
	#define HInstance() GetModuleHandle(NULL)
	#define MAX_STRING_SIZE 64

#endif

// dll import export macro
#ifdef BUILD_DLL
	#define GUI_API __declspec(dllexport)
#else
	#define GUI_API __declspec(dllimport)
#endif

// debug
#ifdef DEBUG

	// include dependencies
	#include <iostream>
	#include <sstream>

	// define debug print macros
	#define DEBUG_PRINT(x) std::cout << x;
	#define DEBUG_PRINTLN(x) std::cout << x << std::endl;

	// define setup console macro
	#define SETUP_CONSOLE() \
	AllocConsole(); \
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); \
	std::cout << "Debug Console Setup! ..." << std::endl;

#else

	// define debug print macros as empty
	#define DEBUG_PRINT(x)
	#define DEBUG_PRINTLN(x)
	#define SETUP_CONSOLE()

#endif
