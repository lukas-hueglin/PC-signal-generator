#include "Gui.h"
#include "Platform/Win32/Win32SliderImpl.h"
#include "Platform/Win32/Win32Utils.h"

Win32SliderImpl::Win32SliderImpl(Graphics2D* p_graphics, WidgetStyle style) : ASliderImpl(p_graphics, style), mp_fillBrush(nullptr), mp_pathGeometry(nullptr) {

	initGraphicsResources();
}

Win32SliderImpl::~Win32SliderImpl() {

	Win32Utils::safeRelease(&mp_fillBrush);
	Win32Utils::safeRelease(&mp_pathGeometry);
}

void Win32SliderImpl::onPaint(Math::Rect sliderRect, WidgetState widgetState) {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_fillBrush != nullptr) {

			// set background color
			mp_fillBrush->SetColor(Win32Utils::D2D1Color(m_style.getHighlightColor(widgetState)));

			// Create a layer.
			HRESULT hr;
			ID2D1Layer* p_layer;
			hr = p_renderTarget->CreateLayer(NULL, &p_layer);

			if (SUCCEEDED(hr)) {

				// set mask
				p_renderTarget->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), mp_pathGeometry), p_layer);

				p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(sliderRect), mp_fillBrush);

				// release mask
				p_renderTarget->PopLayer();
			}

			// delete layer
			Win32Utils::safeRelease(&p_layer);
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32SliderImpl::onResize(Math::Rect hitboxRect) {

	// delete path geometry if needed
	if (mp_pathGeometry != nullptr) {
		Win32Utils::safeRelease(&mp_pathGeometry);
	}

	// create new path geometry
	ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();

	if (p_2DFactory != nullptr) {

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);

		// update path geometry
		Win32Utils::createRoundedRect(hitboxRect, m_style.getTopLeftRadius(), m_style.getTopRightRadius(), m_style.getBottomLeftRadius(), m_style.getBottomRightRadius(), mp_pathGeometry);
	}

}

void Win32SliderImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getHighlightColor(WidgetState::Normal)), &mp_fillBrush);
		mp_fillBrush->SetOpacity(0.5f);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);
	}
}
