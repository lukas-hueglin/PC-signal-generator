#include "Gui.h"
#include "Platform/Win32/Win32LayoutImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Style/Style.h"

Win32LayoutImpl::Win32LayoutImpl(Graphics2D* p_graphics, WidgetStyle style) : ALayoutImpl(p_graphics, style), mp_brush(nullptr) {

	initGraphicsResources();
}

Win32LayoutImpl::~Win32LayoutImpl() {
	Win32Utils::safeRelease(&mp_brush);
}

void Win32LayoutImpl::onPaint(Math::Rect usedRect) {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_brush != nullptr) {

			// draw background
			p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(usedRect), mp_brush);
		}
	}
}

void Win32LayoutImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor(WidgetState::Normal)), &mp_brush);
	}
}
