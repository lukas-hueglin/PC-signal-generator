#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32MainWindow.h"
	using MainWindow = Win32MainWindow;
#endif