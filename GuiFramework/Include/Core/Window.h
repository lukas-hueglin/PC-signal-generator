#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32Window.h"
	using Window = Win32Window;
#endif