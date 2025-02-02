#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32Application.h"
	using Application = Win32Application;
#endif