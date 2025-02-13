#include "Gui.h"
#include "Platform/Win32/Win32Graphics2D.h"
#include "Platform/Win32/Win32Utils.h"
#include "Widgets/Widget.h"

Win32Graphics2D::Win32Graphics2D(HWND hWnd) : m_hWnd(hWnd), mp_2DFactory(nullptr), mp_writeFactory(nullptr), mp_renderTarget(nullptr) { }

Win32Graphics2D::~Win32Graphics2D() { }

void Win32Graphics2D::beginPaint() {

    // initialize graphics resources
    initGraphicsAssets();

    // begin painting
    if (mp_renderTarget != nullptr) {
        BeginPaint(this->m_hWnd, &m_ps);
        mp_renderTarget->BeginDraw();
    }
}

void Win32Graphics2D::endPaint() {

    // end painting
    if (mp_renderTarget != nullptr) {
        mp_renderTarget->EndDraw();
        EndPaint(this->m_hWnd, &m_ps);
    }
}

void Win32Graphics2D::createGraphicsAssets() {

    // Create D2D1 factory
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mp_2DFactory);

    // create DWrite factory
    DWriteCreateFactory(
        DWRITE_FACTORY_TYPE_SHARED,
        __uuidof(mp_writeFactory),
        reinterpret_cast<IUnknown**>(&mp_writeFactory)
    );
}

void Win32Graphics2D::initGraphicsAssets() {

    HRESULT hr = S_OK;

    if (mp_renderTarget == nullptr && mp_2DFactory != nullptr) {

        // Get the window rectangle and size
        RECT rc;
        GetClientRect(m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        // Create the render target
        hr = mp_2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(m_hWnd, size),
            &mp_renderTarget
        );

        // TODO: check hresult
    }
}

ID2D1Factory1* Win32Graphics2D::get2DFactory(){
    return mp_2DFactory;
}

ID2D1HwndRenderTarget* Win32Graphics2D::getRenderTarget() {
    return mp_renderTarget;
}

IDWriteFactory* Win32Graphics2D::getWriteFactory() {
    return mp_writeFactory;
}

void Win32Graphics2D::discardGraphicsAssets() {

    Win32Utils::safeRelease(&mp_renderTarget);
    Win32Utils::safeRelease(&mp_writeFactory);
    Win32Utils::safeRelease(&mp_2DFactory);
}

void Win32Graphics2D::resizeCanvas() {

    if (mp_renderTarget != nullptr) {

        // get the window rectangle and size
        RECT rc;
        GetClientRect(this->m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(rc.right, rc.bottom);

        mp_renderTarget->Resize(size);
        InvalidateRect(this->m_hWnd, NULL, FALSE);
    }
}

Math::Rect Win32Graphics2D::getDPISize() {

    if (mp_renderTarget != nullptr) {
        D2D1_SIZE_F size = mp_renderTarget->GetSize();
        return Math::Rect(0, size.width, 0, size.height);
    }
    else {
        return Math::Rect();
    }
}
