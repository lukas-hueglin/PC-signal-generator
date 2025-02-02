#include "Gui.h"
#include "Platform/Win32/Win32ButtonImpl.h"
#include "Platform/Win32/Win32Utils.h"

Win32ButtonImpl::Win32ButtonImpl(Graphics2D* p_graphics, WidgetStyle style) : AButtonImpl(p_graphics, style), mp_edgeBrush(nullptr), mp_fillBrush(nullptr), mp_pathGeometry(nullptr) {

	initGraphicsResources();
}

Win32ButtonImpl::~Win32ButtonImpl() {

	Win32Utils::safeRelease(&mp_edgeBrush);
	Win32Utils::safeRelease(&mp_fillBrush);
	Win32Utils::safeRelease(&mp_pathGeometry);
}

void Win32ButtonImpl::onPaint(WidgetState widgetState) {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr && mp_pathGeometry != nullptr) {

			// set background color
			mp_fillBrush->SetColor(Win32Utils::D2D1Color(m_style.getFillColor(widgetState)));

			// draw background
			p_renderTarget->FillGeometry(mp_pathGeometry, mp_fillBrush);
			p_renderTarget->DrawGeometry(mp_pathGeometry, mp_edgeBrush, m_style.getEdgeThickness(), (ID2D1StrokeStyle*) m_style.getLineStyle());
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32ButtonImpl::onResize(Math::Rect hitboxRect) {

	// delete path geometry if needed
	if (mp_pathGeometry != nullptr) {
		Win32Utils::safeRelease(&mp_pathGeometry);
	}

	// create new path geometry
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_2DFactory != nullptr) {

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);

		// update path geometry
		Win32Utils::createRoundedRect(hitboxRect, m_style.getTopLeftRadius(), m_style.getTopRightRadius(), m_style.getBottomLeftRadius(), m_style.getBottomRightRadius(), mp_pathGeometry);
	}
}

void Win32ButtonImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor(WidgetState::Normal)), &mp_fillBrush);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);
	}
}
