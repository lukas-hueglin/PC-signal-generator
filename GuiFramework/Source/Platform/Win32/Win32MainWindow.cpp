#include "Gui.h"
#include "Platform/Win32/Win32MainWindow.h"
#include "Core/Graphics2D.h"


Win32MainWindow* Win32MainWindow::create(std::wstring title) {
	
	return Win32Window::create<Win32MainWindow>(title);
}

PCWSTR Win32MainWindow::getClassName() {

	return L"MainWindow";
}

LRESULT Win32MainWindow::handleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {

		// add cases for custom functionality

	default:

		return DefWindowProc(this->m_hWnd, uMsg, wParam, lParam);
	}
}
