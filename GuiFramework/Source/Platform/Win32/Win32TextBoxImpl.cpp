#include "Gui.h"
#include "Platform/Win32/Win32TextBoxImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Style/Palette.h"

Win32TextBoxImpl::Win32TextBoxImpl(Graphics2D* p_graphics, WidgetStyle style) :
	ATextBoxImpl(p_graphics, style),
	mp_edgeBrush(nullptr), mp_fillBrush(nullptr), mp_textBrush(nullptr), mp_textSelectBrush(nullptr), mp_pathGeometry(nullptr), mp_textFormat(nullptr), mp_textLayout(nullptr) {

	initGraphicsResources();
}

Win32TextBoxImpl::~Win32TextBoxImpl() {

	Win32Utils::safeRelease(&mp_edgeBrush);
	Win32Utils::safeRelease(&mp_fillBrush);
	Win32Utils::safeRelease(&mp_textBrush);
	Win32Utils::safeRelease(&mp_textSelectBrush);

	Win32Utils::safeRelease(&mp_pathGeometry);

	Win32Utils::safeRelease(&mp_textFormat);
	Win32Utils::safeRelease(&mp_textLayout);
}

void Win32TextBoxImpl::onPaint(WidgetState widgetState) {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

	// check if render target exists
	if (p_renderTarget != nullptr) {

		// check if brush was created successfully
		if (mp_edgeBrush != nullptr && mp_fillBrush != nullptr && mp_textBrush != nullptr && mp_textFormat != nullptr && mp_textLayout != nullptr) {

			// set background color
			mp_fillBrush->SetColor(Win32Utils::D2D1Color(m_style.getFillColor(widgetState)));

			// draw background
			p_renderTarget->FillGeometry(mp_pathGeometry, mp_fillBrush);
			p_renderTarget->DrawGeometry(mp_pathGeometry, mp_edgeBrush, m_style.getEdgeThickness(), (ID2D1StrokeStyle*)m_style.getLineStyle());

			// draw text
			p_renderTarget->DrawTextLayout(Win32Utils::D2D1Point(m_rect.topLeft()), mp_textLayout, mp_textBrush);
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32TextBoxImpl::onPaintCursor(int firstIndex, int lastIndex, bool dragFirstCursor, bool cursor) {

	ID2D1RenderTarget* p_renderTarget = mp_graphics->getRenderTarget();


	// check if render target exists
	if (p_renderTarget != nullptr) {

		if (mp_textBrush != nullptr && mp_textSelectBrush != nullptr) {
			if (firstIndex == lastIndex) {

				// check animation cycle
				if (cursor) {
					// get cursor position
					Math::Rect rect = getCursorPosition(firstIndex);
					p_renderTarget->DrawRectangle(Win32Utils::D2D1Rect(rect), mp_textBrush, m_style.getEdgeThickness());
				}
			}
			else {

				// get cursor positions
				Math::Point2D firstCursor = getCursorPosition(firstIndex, dragFirstCursor).topLeft();
				Math::Point2D lastCursor = getCursorPosition(lastIndex, !dragFirstCursor).bottomRight();
				Math::Rect rect = Math::Rect(firstCursor, lastCursor);

				p_renderTarget->FillRectangle(Win32Utils::D2D1Rect(rect), mp_textSelectBrush);
			}
		}
		else {
			initGraphicsResources();
		}
	}
}

void Win32TextBoxImpl::onResize(Math::Rect hitboxRect, Math::Rect contentRect) {

	// set rectangle
	m_rect = contentRect;

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

	// delete textLayout if needed
	if (mp_textLayout != nullptr) {
		Win32Utils::safeRelease(&mp_textLayout);
	}

	// update textLayout
	initTextLayout();
}

void Win32TextBoxImpl::setText(std::wstring text) {

	m_text = text;

	// delete textLayout if needed
	if (mp_textLayout != nullptr) {
		Win32Utils::safeRelease(&mp_textLayout);
	}

	// update textLayout
	initTextLayout();
}

int Win32TextBoxImpl::getMousePosition(Math::Point2D point) {
	
	if (mp_textLayout != nullptr) {

		// create helper variables
		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		BOOL isInside;
		BOOL isTrailing;

		// perform hit test
		mp_textLayout->HitTestPoint(point.x() - m_rect.left(), point.y() - m_rect.top(), &isTrailing, &isInside, &hitTestMetrics);

		return hitTestMetrics.textPosition;
	}

	return 0;
}

Math::Rect Win32TextBoxImpl::getCursorPosition(int cursor, bool trailing) {
	
	// create rect
	Math::Rect rect(0, 0, 0, 0);

	// create helper variables
	DWRITE_TEXT_METRICS textMetrics;
	DWRITE_HIT_TEST_METRICS hitTestMetrics;
	FLOAT pointX;
	FLOAT pointY;

	// get height of text
	mp_textLayout->GetMetrics(&textMetrics);

	// test first cursor
	mp_textLayout->HitTestTextPosition(cursor, trailing, &pointX, &pointY, &hitTestMetrics);
	rect.topLeft() = Math::Point2D(pointX, pointY) + m_rect.topLeft();
	rect.bottomRight() = Math::Point2D(pointX, pointY + textMetrics.height) + m_rect.topLeft();

	return rect;
}

void Win32TextBoxImpl::initGraphicsResources() {

	// get render target and 2d factory
	ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
	ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();
	IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

	if (p_renderTarget != nullptr && p_2DFactory != nullptr && p_writeFactory != nullptr) {

		// Create brush
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor(WidgetState::Normal)), &mp_fillBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_textBrush);
		p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(Palette::TextSelection()), &mp_textSelectBrush);

		// create path geometry
		p_2DFactory->CreatePathGeometry(&mp_pathGeometry);

		// create new text format
		p_writeFactory->CreateTextFormat(
			m_style.getFontName().c_str(),
			NULL,
			(DWRITE_FONT_WEIGHT)m_style.getFontWeight(),
			(DWRITE_FONT_STYLE)m_style.getFontStyle(),
			DWRITE_FONT_STRETCH_NORMAL,
			m_style.getFontSize(),
			L"en-us",
			&mp_textFormat
		);

		// create text layout
		initTextLayout();
	}
}

void Win32TextBoxImpl::initTextLayout() {

	// get write factory
	IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

	if (p_writeFactory != nullptr) {

		// create new text layout
		p_writeFactory->CreateTextLayout(
			m_text.c_str(),      // The string to be laid out and formatted.
			m_text.size(),  // The length of the string.
			mp_textFormat,  // The text format to apply to the string (contains font information, etc).
			m_rect.getWidth(),         // The width of the layout box.
			m_rect.getHeight(),        // The height of the layout box.
			&mp_textLayout  // The IDWriteTextLayout interface pointer.
		);

		// align text
		int horizontal_alignment = (3 - (m_style.getTextAlignment() % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
		int vertical_alignment = (3 - (m_style.getTextAlignment() / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1

		if (mp_textLayout != nullptr) {
			mp_textLayout->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)horizontal_alignment);
			mp_textLayout->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);
		}
	}
}
