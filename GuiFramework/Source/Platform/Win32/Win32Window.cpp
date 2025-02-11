#include "Gui.h"
#include "Platform/Win32/Win32Window.h"
#include "Platform/Win32/Win32Utils.h"
#include "Core/Graphics2D.h"


Win32Window::Win32Window() : m_hWnd(NULL) { }

Win32Window::~Win32Window() {

    DestroyWindow(m_hWnd);
}

void Win32Window::initialize(std::wstring title) {

    // create win32 hWnd
    createHwnd(title.c_str(), WS_OVERLAPPEDWINDOW);
}

void Win32Window::createHwnd(PCWSTR lpWindowName, DWORD dwStyle, DWORD dwExStyle, int x, int y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu) {

    // create window class struct
    WNDCLASS wc = { 0 };
    wc.style = CS_DBLCLKS;

    // Check if class is already registered
    if (!GetClassInfo(HInstance(), getClassName(), &wc)) {

        // Register the window class.
        wc.lpfnWndProc = Win32Window::windowProc;
        wc.hInstance = HInstance();
        wc.lpszClassName = getClassName();

        RegisterClass(&wc);
    }

    // Create the window
    HWND hWnd = CreateWindowEx(
        dwExStyle,      // Extended window style
        getClassName(), // Window class
        lpWindowName,   // Window title
        dwStyle,        // Window style

        // Position and size
        x, y, nWidth, nHeight,

        hWndParent,     // Parent window
        hMenu,          // Menu
        HInstance(),    // Instance handle
        this            // Additional application data
    );
}

LRESULT Win32Window::windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

    Win32Window* p_this = nullptr;

    // Check if window is created
    if (uMsg == WM_NCCREATE) {

        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        p_this = (Win32Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)p_this);

        // set window handle member variable
        p_this->m_hWnd = hWnd;

        // create graphics_type
        p_this->mp_graphics = new Graphics2D(hWnd);

        // show window
        ShowWindow(hWnd, 1);
    }
    else {

        // get window pointer from the userdata
        p_this = (Win32Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
    }

    if (p_this) {

        // filter out some messages and handle them here
        switch (uMsg) {

        case WM_CREATE:
        {
            p_this->onBegin();
            return 1;
        }
        case WM_DESTROY:
        {
            p_this->onDestroy();
            PostQuitMessage(0); // if any window is closed, the program will exit
            return 1;
        }
        case WM_PAINT:
        {
            p_this->onPaint();
            return 1;
        }
        case WM_SIZE:
        {
            RECT rc;
            GetClientRect(p_this->m_hWnd, &rc);
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onResize(Math::Rect(0, rc.right / dpiScale, 0, rc.bottom / dpiScale));
            return 1;
        }
        case WM_MOUSEMOVE:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseMove(Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONDBLCLK:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseDown(true, Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONDOWN:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float)USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseDown(false, Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_LBUTTONUP:
        {
            float dpiScale = GetDpiForWindow(p_this->m_hWnd) / ((float) USER_DEFAULT_SCREEN_DPI);

            p_this->onMouseRelease(Math::Point2D(GET_X_LPARAM(lParam) / dpiScale, GET_Y_LPARAM(lParam) / dpiScale));
            return 1;
        }
        case WM_KEYDOWN:
        {
            Key key = Win32Utils::convertWin32Keys(wParam);
            if (key != Key::Empty) {
                p_this->onKeyDown(key);
            }
            return 1;
        }
        case WM_CHAR:
        {
            // if characters are printable
            if (wParam >= 0x20 && wParam <= 0x7E) {
                p_this->onKeyDown((char)wParam);
            }
            return 1;
        }
        case WM_MOUSEWHEEL:
        {
            // extract data
            float zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
            int fwKeys = GET_KEYSTATE_WPARAM(wParam);

            p_this->onMouseScroll(GET_WHEEL_DELTA_WPARAM(wParam) > 0, (fwKeys >> 2) & 1, (fwKeys >> 3) & 1);
            return 1;
        }
        default:
            // call the child function for handling the messages
            return p_this->handleMessage(uMsg, wParam, lParam);
        }
    }
    else {

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

PCWSTR Win32Window::getClassName() {
    
    return L"Window";
}
