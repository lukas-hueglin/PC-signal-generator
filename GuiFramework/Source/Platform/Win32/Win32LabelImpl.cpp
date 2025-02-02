#include "Gui.h"
#include "Platform/Win32/Win32LabelImpl.h"
#include "Platform/Win32/Win32Utils.h"
#include "Style/Style.h"

Win32LabelImpl::Win32LabelImpl(Graphics2D* p_graphics, WidgetStyle style) : ALabelImpl(p_graphics, style), mp_textBrush(nullptr), mp_textFormat(nullptr) {

    initGraphicsResources();
}

Win32LabelImpl::~Win32LabelImpl() {

	Win32Utils::safeRelease(&mp_textBrush);
	Win32Utils::safeRelease(&mp_textFormat);
}

void Win32LabelImpl::onPaint(std::wstring text) {

    // get render target and write factory
    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

    // check if render target exists
    if (p_renderTarget != nullptr) {

        // check if brush and text format exists
        if (mp_textBrush != nullptr && mp_textFormat != nullptr) {

            // draw text
            p_renderTarget->DrawTextW(text.c_str(), text.length(), mp_textFormat, Win32Utils::D2D1Rect(m_rect), mp_textBrush);
        }
        else {
            initGraphicsResources();
        }
    }
}

void Win32LabelImpl::onResize(Math::Rect contentRect) {

    m_rect = contentRect;
}

void Win32LabelImpl::initGraphicsResources() {

    // get render target and write factory
    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
    IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

    if (p_renderTarget != nullptr && p_writeFactory != nullptr) {

        // Create brush
        p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getTextColor()), &mp_textBrush);

        // create new text format
        p_writeFactory->CreateTextFormat(
            m_style.getFontName().c_str(),
            NULL,
            (DWRITE_FONT_WEIGHT) m_style.getFontWeight(),
            (DWRITE_FONT_STYLE) m_style.getFontStyle(),
            DWRITE_FONT_STRETCH_NORMAL,
            m_style.getFontSize(),
            L"en-us",
            &mp_textFormat
        );

        // align text
        int horizontal_alignment = (3 - (m_style.getTextAlignment() % 3)) % 3; // Left -> 0, Center -> 2, Right -> 1
        int vertical_alignment = (3 - (m_style.getTextAlignment() / 3)) % 3; // Top -> 0, Center -> 2, Bottom -> 1

        if (mp_textFormat != nullptr) {
            mp_textFormat->SetTextAlignment((DWRITE_TEXT_ALIGNMENT)horizontal_alignment);
            mp_textFormat->SetParagraphAlignment((DWRITE_PARAGRAPH_ALIGNMENT)vertical_alignment);
        }
    }
}
