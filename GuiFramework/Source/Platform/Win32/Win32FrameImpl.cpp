#include "Gui.h"
#include "Platform/Win32/Win32FrameImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Style/Palette.h"

Win32FrameImpl::Win32FrameImpl(Graphics2D* p_graphics) : AFrameImpl(p_graphics), mp_debug1Brush(nullptr), mp_debug2Brush(nullptr), mp_debug3Brush(nullptr) {

	initGraphicsResources();
}

Win32FrameImpl::~Win32FrameImpl() {

	Win32Utils::safeRelease(&mp_debug1Brush);
	Win32Utils::safeRelease(&mp_debug2Brush);
	Win32Utils::safeRelease(&mp_debug3Brush);
}

void Win32FrameImpl::onPaint() {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_debug1Brush != nullptr && mp_debug2Brush != nullptr && mp_debug3Brush != nullptr) {

			// draw background
			p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(m_usedRect), mp_debug1Brush);
			p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(m_hitboxRect), mp_debug2Brush);
			p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(m_contentRect), mp_debug3Brush);
		}
	}
}

void Win32FrameImpl::onResize(Math::Rect usedRect, Math::Rect hitboxRect, Math::Rect contentRect) {

	m_usedRect = usedRect;
	m_hitboxRect = hitboxRect;
	m_contentRect = contentRect;
}

void Win32FrameImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(Palette::Debug1()), &mp_debug1Brush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(Palette::Debug2()), &mp_debug2Brush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(Palette::Debug3()), &mp_debug3Brush);
	}
}
