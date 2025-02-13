#include "Gui.h"
#include "Platform/Win32/Win32PlotSeries1DImpl.h"
#include "Platform/Win32/Win32Utils.h"

Win32PlotSeries1DImpl::Win32PlotSeries1DImpl(Graphics2D* p_graphics, Color color) :
	APlotSeries1DImpl(p_graphics, color),
	
	mp_edgeBrush(nullptr), mp_fillBrush(nullptr),
	mp_edgePathGeometry(nullptr), mp_fillPathGeometry(nullptr) {

	initGraphicsResources();
}

Win32PlotSeries1DImpl::~Win32PlotSeries1DImpl() {

	Win32Utils::safeRelease(&mp_edgeBrush);
	Win32Utils::safeRelease(&mp_fillBrush);

	Win32Utils::safeRelease(&mp_edgePathGeometry);
	Win32Utils::safeRelease(&mp_fillPathGeometry);
}

void Win32PlotSeries1DImpl::onUpdate(float* pa_data, int size, int head, float lowerBound, float upperBound) {

	if (mp_edgePathGeometry != nullptr && mp_fillPathGeometry != nullptr) {

		Win32Utils::safeRelease(&mp_edgePathGeometry);
		Win32Utils::safeRelease(&mp_fillPathGeometry);
	}

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();

	// create triangle
	ID2D1GeometrySink* p_edgeSink;
	ID2D1GeometrySink* p_fillSink;
	HRESULT hr;

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// create new path geometry
		ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();


		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_edgePathGeometry);
		p_2DFactory->CreatePathGeometry(&mp_fillPathGeometry);

		// Write to the path geometry using the geometry sink.
		hr = mp_edgePathGeometry->Open(&p_edgeSink);
		hr |= mp_fillPathGeometry->Open(&p_fillSink);

		if (SUCCEEDED(hr)) {

			// calculate step
			float step = (upperBound - lowerBound) / size;

			// begin figure
			p_edgeSink->BeginFigure(
				D2D1::Point2F(lowerBound, pa_data[head]),
				D2D1_FIGURE_BEGIN_FILLED
			);
			p_fillSink->BeginFigure(
				D2D1::Point2F(lowerBound, pa_data[head]),
				D2D1_FIGURE_BEGIN_FILLED
			);

			// add all points
			for (int i = 1; i < size; ++i) {

				// calculate index
				int index = (head + i) % size;

				p_edgeSink->AddLine(D2D1::Point2F(lowerBound + step * i, pa_data[index]));
				p_fillSink->AddLine(D2D1::Point2F(lowerBound + step * i, pa_data[index]));
			}

			// end figure
			p_edgeSink->EndFigure(D2D1_FIGURE_END_OPEN);
			p_fillSink->EndFigure(D2D1_FIGURE_END_CLOSED);

			p_edgeSink->Close();
			p_fillSink->Close();
		}

		// delete resources
		Win32Utils::safeRelease(&p_edgeSink);
		Win32Utils::safeRelease(&p_fillSink);
	}
}

void Win32PlotSeries1DImpl::onPaint(Math::Rect availableRect, Math::Rect plotBounds, bool fillArea) {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr && mp_edgePathGeometry != nullptr && mp_fillPathGeometry != nullptr) {

			// create transform
			float scaleX = availableRect.getWidth() / plotBounds.getWidth();
			float scaleY = availableRect.getHeight() / plotBounds.getHeight();
			float dx = availableRect.left() - plotBounds.left() / plotBounds.getWidth() * availableRect.getWidth();
			float dy = availableRect.bottom() - plotBounds.bottom() / plotBounds.getHeight() * availableRect.getHeight();
			
			D2D1_MATRIX_3X2_F transform = D2D1::Matrix3x2F(scaleX, 0, 0, scaleY, dx, dy);

			// set transform
			p_renderTarget->SetTransform(&transform);

			// set mask
			p_renderTarget->PushAxisAlignedClip(Win32Utils::D2D1Rect(plotBounds), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

			// draw
			p_renderTarget->DrawGeometry(mp_edgePathGeometry, mp_edgeBrush, 1.0f, mp_strokeStyle);

			if (fillArea) {
				p_renderTarget->FillGeometry(mp_fillPathGeometry, mp_fillBrush);
			}

			// release mask
			p_renderTarget->PopAxisAlignedClip();

			// release transform
			p_renderTarget->SetTransform(D2D1::IdentityMatrix());
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32PlotSeries1DImpl::setColor(Color color) {

	if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr) {

		mp_edgeBrush->SetColor(Win32Utils::D2D1Color(color));
		mp_fillBrush->SetColor(Win32Utils::D2D1Color(color));
	}
}

void Win32PlotSeries1DImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_color), &mp_edgeBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_color), &mp_fillBrush);

		// create stoke style
		p_2DFactory->CreateStrokeStyle(
			D2D1::StrokeStyleProperties1(
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_FLAT,
				D2D1_CAP_STYLE_FLAT,
				D2D1_LINE_JOIN_MITER,
				10.0f,
				D2D1_DASH_STYLE_SOLID,
				0.0f, D2D1_STROKE_TRANSFORM_TYPE_FIXED
			),
			nullptr, 0, &mp_strokeStyle);

		// set opacity of fill brush
		mp_fillBrush->SetOpacity(0.2);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_edgePathGeometry);
		p_2DFactory->CreatePathGeometry(&mp_fillPathGeometry);
	}
}
