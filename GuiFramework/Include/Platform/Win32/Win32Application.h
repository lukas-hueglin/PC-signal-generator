#pragma once
#include "Core/IApplication.h"

class GUI_API Win32Application : public IApplication {
public:
	Win32Application(int argc, char** argv);

public:
	int exec();

protected:
	std::wstring getIniPath();
};