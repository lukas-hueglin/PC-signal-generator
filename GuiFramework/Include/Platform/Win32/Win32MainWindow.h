#pragma once
#include "Platform/Win32/Win32Window.h"

class GUI_API Win32MainWindow : public Win32Window {

public:
	static Win32MainWindow* create(std::wstring title);

private:
	PCWSTR getClassName() override;
	LRESULT handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
};