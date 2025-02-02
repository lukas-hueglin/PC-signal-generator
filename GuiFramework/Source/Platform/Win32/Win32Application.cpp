#include "Gui.h"
#include "Platform/Win32/Win32Application.h"
#include "shlobj.h"

#include <chrono>

Win32Application::Win32Application(int argc, char** argv) : IApplication(argc, argv) { }

int Win32Application::exec() {

    // setup console if debug mode
    SETUP_CONSOLE()

    // call onBegin
    onBegin();

    // create time stamp and duration object
    std::chrono::time_point<std::chrono::system_clock> now, lastFrame;
    std::chrono::duration<float> deltaTime;
    lastFrame = std::chrono::system_clock::now();

    // get and translate windows message
    MSG msg = { };
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            
            // handle Windows messages
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // measure time
            now = std::chrono::system_clock::now();
            deltaTime = now - lastFrame;

            if (deltaTime.count() >= 1.0f / 30.0f) {
                onTick(deltaTime.count());
                lastFrame = now;
            }
        }
    }

    // call onClose
    onClose();

	return 0;
}

std::wstring Win32Application::getIniPath() {

    // create a path
    PWSTR appDataLocal;
    HRESULT hr;

    // read app data location
    hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &appDataLocal);

    // create path
    std::wstringstream ss;
    ss << appDataLocal << L"\\" << getApplicationName();

    // Create Folder
    CreateDirectory(ss.str().c_str(), NULL);

    // add file name
    ss << L"\\" << PROJECT_NAME << L".ini";

    return ss.str();
}
