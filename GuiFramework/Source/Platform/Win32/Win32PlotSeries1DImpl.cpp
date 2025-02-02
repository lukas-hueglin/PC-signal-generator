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

void Win32PlotSeries1DImpl::onUpdate(std::vector<Math::Point2D>* p_points) {

	if (mp_edgePathGeometry != nullptr && mp_fillPathGeometry != nullptr) {

		Win32Utils::safeRelease(&mp_edgePathGeometry);
		Win32Utils::safeRelease(&mp_fillPathGeometry);
	}

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	// create triangle
	ID2D1GeometrySink* p_edgeSink;
	ID2D1GeometrySink* p_fillSink;
	HRESULT hr;

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// create new path geometry
		ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();


		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_edgePathGeometry);
		p_2DFactory->CreatePathGeometry(&mp_fillPathGeometry);

		// Write to the path geometry using the geometry sink.
		hr = mp_edgePathGeometry->Open(&p_edgeSink);
		hr |= mp_fillPathGeometry->Open(&p_fillSink);

		if (SUCCEEDED(hr)) {

			// begin figure
			p_edgeSink->BeginFigure(
				Win32Utils::D2D1Point(p_points->at(0)),
				D2D1_FIGURE_BEGIN_FILLED
			);
			p_fillSink->BeginFigure(
				Win32Utils::D2D1Point(p_points->at(0)),
				D2D1_FIGURE_BEGIN_FILLED
			);

			// add all points
			for (Math::Point2D& point : (*p_points)) {
				p_edgeSink->AddLine(Win32Utils::D2D1Point(point));
				p_fillSink->AddLine(Win32Utils::D2D1Point(point));
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

void Win32PlotSeries1DImpl::onPaint(Math::Rect& availableRect, bool fillArea) {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr && mp_edgePathGeometry != nullptr && mp_fillPathGeometry != nullptr) {

			// set mask
			p_renderTarget->PushAxisAlignedClip(Win32Utils::D2D1Rect(availableRect), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

			// draw
			p_renderTarget->DrawGeometry(mp_edgePathGeometry, mp_edgeBrush);

			if (fillArea) {
				p_renderTarget->FillGeometry(mp_fillPathGeometry, mp_fillBrush);
			}

			// release mask
			p_renderTarget->PopAxisAlignedClip();

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
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_color), &mp_edgeBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_color), &mp_fillBrush);

		// set opacity of fill brush
		mp_fillBrush->SetOpacity(0.2);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_edgePathGeometry);
		p_2DFactory->CreatePathGeometry(&mp_fillPathGeometry);
	}
}
