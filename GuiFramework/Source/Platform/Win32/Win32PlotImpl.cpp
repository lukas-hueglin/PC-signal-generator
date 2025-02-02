#include "Gui.h"
#include "Platform/Win32/Win32PlotImpl.h"
#include "Platform/Win32/Win32Utils.h"

Win32PlotImpl::Win32PlotImpl(Graphics2D* p_graphics, WidgetStyle style) :
	APlotImpl(p_graphics, style),
	mp_edgeBrush(nullptr), mp_fillBrush(nullptr),
	mp_axisBrush(nullptr), mp_textBrush(nullptr),
	mp_xTextFormat(nullptr), mp_yTextFormat(nullptr),
	mp_pathGeometry(nullptr) {

	initGraphicsResources();
}

Win32PlotImpl::~Win32PlotImpl() {

	Win32Utils::safeRelease(&mp_edgeBrush);
	Win32Utils::safeRelease(&mp_fillBrush);

	Win32Utils::safeRelease(&mp_axisBrush);
	Win32Utils::safeRelease(&mp_textBrush);

	Win32Utils::safeRelease(&mp_xTextFormat);
	Win32Utils::safeRelease(&mp_yTextFormat);

	Win32Utils::safeRelease(&mp_pathGeometry);
}

void Win32PlotImpl::onResize(Math::Rect plotRect, Math::Rect legendRect) {

	m_plotRect = plotRect;
	m_legendRect = legendRect;

	// delete path geometry if needed
	if (mp_pathGeometry != nullptr) {
		Win32Utils::safeRelease(&mp_pathGeometry);
	}

	// create new path geometry
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_2DFactory != nullptr) {

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);

		// create new path geometry
		Win32Utils::createRoundedRect(m_legendRect, m_style.getTopLeftRadius(), m_style.getTopRightRadius(), m_style.getBottomLeftRadius(), m_style.getBottomRightRadius(), mp_pathGeometry);
	}

}

void Win32PlotImpl::onPaintAxis(std::wstring xAxisText, std::wstring yAxisText) {

	// calculate coordinates
	Math::Point2D origin(m_plotRect.left() - 10, m_plotRect.bottom() + 10);
	Math::Point2D x_axis(m_plotRect.right(), m_plotRect.bottom() + 10);
	Math::Point2D y_axis(m_plotRect.left() - 10, m_plotRect.top());

	// draw axis
	drawArrow(origin, x_axis, 10.0f);
	drawArrow(origin, y_axis, 10.0f);

	// calculate label rectangles
	Math::Rect xAxisRect(x_axis.x() - 40.0f, x_axis.x() + 40.0f, x_axis.y() + 10.0f, x_axis.y() + 25.0f);
	Math::Rect yAxisRect(y_axis.x() - 40.0f, y_axis.x() + 40.0f, y_axis.y() - 25.0f, y_axis.y() - 10.0f);

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		if (mp_textBrush != nullptr) {

			// draw labels
			p_renderTarget->DrawTextW(xAxisText.c_str(), xAxisText.length(), mp_xTextFormat, Win32Utils::D2D1Rect(xAxisRect), mp_textBrush);
			p_renderTarget->DrawTextW(yAxisText.c_str(), yAxisText.length(), mp_xTextFormat, Win32Utils::D2D1Rect(yAxisRect), mp_textBrush);
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32PlotImpl::onPaintHorizontalTicks(float value, std::wstring text) {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		if (mp_textBrush != nullptr) {

			// calculate coordinates
			Math::Point2D lineBegin = Math::Point2D(m_plotRect.left(), value);
			Math::Point2D lineEnd = Math::Point2D(m_plotRect.right(), value);

			Math::Point2D tickBegin = lineBegin - Math::Point2D(15, 0);
			Math::Point2D tickEnd = lineBegin - Math::Point2D(5, 0);
			Math::Rect textRect(lineBegin.x() - 55, lineBegin.x() - 20, lineBegin.y() - 10, lineBegin.y() + 10);

			// draw dashed line
			p_renderTarget->DrawLine(Win32Utils::D2D1Point(lineBegin), Win32Utils::D2D1Point(lineEnd), mp_axisBrush, m_style.getEdgeThickness());

			// draw tick
			p_renderTarget->DrawLine(Win32Utils::D2D1Point(tickBegin), Win32Utils::D2D1Point(tickEnd), mp_axisBrush, m_style.getEdgeThickness());

			// draw text
			p_renderTarget->DrawTextW(text.c_str(), text.length(), mp_yTextFormat, Win32Utils::D2D1Rect(textRect), mp_textBrush);
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32PlotImpl::onPaintVerticalTicks(float value, std::wstring text) {

	// get render target
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	if (p_renderTarget != nullptr) {

		if (mp_textBrush != nullptr) {

			// calculate coordinates
			Math::Point2D lineBegin = Math::Point2D(value, m_plotRect.bottom());
			Math::Point2D lineEnd = Math::Point2D(value, m_plotRect.top());

			Math::Point2D tickBegin = lineBegin + Math::Point2D(0, 15);
			Math::Point2D tickEnd = lineBegin + Math::Point2D(0, 5);
			Math::Rect textRect(lineBegin.x() - 20, lineBegin.x() + 20, lineBegin.y() + 20, lineBegin.y() + 40);

			// draw dashed line
			p_renderTarget->DrawLine(Win32Utils::D2D1Point(lineBegin), Win32Utils::D2D1Point(lineEnd), mp_axisBrush, m_style.getEdgeThickness());

			// draw tick
			p_renderTarget->DrawLine(Win32Utils::D2D1Point(tickBegin), Win32Utils::D2D1Point(tickEnd), mp_axisBrush, m_style.getEdgeThickness());

			// draw text
			p_renderTarget->DrawTextW(text.c_str(), text.length(), mp_xTextFormat, Win32Utils::D2D1Rect(textRect), mp_textBrush);
		}
		else {
			initGraphicsResources();
		}
	}
}

/*
void Win32PlotImpl::onPaintLegend() {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr) {

			// draw background
			p_renderTarget->FillGeometry(mp_pathGeometry, mp_fillBrush);
			p_renderTarget->DrawGeometry(mp_pathGeometry, mp_edgeBrush, m_style.getEdgeThickness(), (ID2D1StrokeStyle*)m_style.getLineStyle());
		}
		else {
			initGraphicsResources();
		}
	}
}*/

void Win32PlotImpl::drawArrow(Math::Point2D a, Math::Point2D b, float size) {

	// calculate arrow head
	Math::Point2D base = b - a;
	base = base / base.length() * size;

	// calculate corners
	Math::Point2D c = b - base + Math::Point2D(-base.y(), base.x()) / 2;
	Math::Point2D d = b - base + Math::Point2D(base.y(), -base.x()) / 2;

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	// create triangle
	ID2D1GeometrySink* p_sink;
	ID2D1PathGeometry* p_pathGeometry;
	HRESULT hr;

	if (p_renderTarget != nullptr && p_2DFactory != nullptr) {

		hr = p_2DFactory->CreatePathGeometry(&p_pathGeometry);

		if (SUCCEEDED(hr))
		{
			// Write to the path geometry using the geometry sink.
			hr = p_pathGeometry->Open(&p_sink);

			if (SUCCEEDED(hr))
			{
				p_sink->BeginFigure(
					Win32Utils::D2D1Point(b),
					D2D1_FIGURE_BEGIN_FILLED
				);

				p_sink->AddLine(Win32Utils::D2D1Point(c));
				p_sink->AddLine(Win32Utils::D2D1Point(d));

				p_sink->EndFigure(D2D1_FIGURE_END_CLOSED);

				hr = p_sink->Close();
			}

		}

		// draw
		if (mp_axisBrush != nullptr) {

			p_renderTarget->DrawLine(Win32Utils::D2D1Point(a), Win32Utils::D2D1Point(b), mp_axisBrush, m_style.getEdgeThickness());
			p_renderTarget->FillGeometry(p_pathGeometry, mp_axisBrush);
		}
		else {
			initGraphicsResources();
		}

		// delete resources
		Win32Utils::safeRelease(&p_sink);
		Win32Utils::safeRelease(&p_pathGeometry);
	}
}

void Win32PlotImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();
	ID2D1Factory* p_2DFactory = mp_graphics->get2DFactory();

	if (p_renderTarget != nullptr && p_writeFactory != nullptr && p_2DFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor(WidgetState::Normal)), &mp_fillBrush);

		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_axisBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_textBrush);

		// create new text format
		p_writeFactory->CreateTextFormat(
			m_style.getFontName().c_str(),
			NULL,
			(DWRITE_FONT_WEIGHT)m_style.getFontWeight(),
			(DWRITE_FONT_STYLE)m_style.getFontStyle(),
			DWRITE_FONT_STRETCH_NORMAL,
			m_style.getFontSize(),
			L"en-us",
			&mp_xTextFormat
		);

		p_writeFactory->CreateTextFormat(
			m_style.getFontName().c_str(),
			NULL,
			(DWRITE_FONT_WEIGHT)m_style.getFontWeight(),
			(DWRITE_FONT_STYLE)m_style.getFontStyle(),
			DWRITE_FONT_STRETCH_NORMAL,
			m_style.getFontSize(),
			L"en-us",
			&mp_yTextFormat
		);

		// set alignment
		mp_xTextFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT) 2);
		mp_xTextFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT) 2);

		mp_yTextFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT) 1);
		mp_yTextFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT) 2);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);
	}
}
