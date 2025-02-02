#include "Gui.h"
#include "Platform/Win32/Win32WidgetImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Style/Palette.h"

Win32WidgetImpl::Win32WidgetImpl(Graphics2D* p_graphics, WidgetStyle style) : AWidgetImpl(p_graphics, style), mp_fillBrush(nullptr) {

	initGraphicsResources();
}

Win32WidgetImpl::~Win32WidgetImpl() {

	Win32Utils::safeRelease(&mp_fillBrush);
}

void Win32WidgetImpl::onPaint() {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_fillBrush != nullptr) {

			// draw background
			p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(m_rect), mp_fillBrush);
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32WidgetImpl::onResize(Math::Rect availableRect) {

	m_rect = availableRect;
}

void Win32WidgetImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(Palette::Background()), &mp_fillBrush);
	}
}
