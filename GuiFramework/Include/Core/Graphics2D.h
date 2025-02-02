#pragma once

#ifdef WIN32
	#include "Platform/Win32/Win32Graphics2D.h"
	using Graphics2D = Win32Graphics2D;
#endif