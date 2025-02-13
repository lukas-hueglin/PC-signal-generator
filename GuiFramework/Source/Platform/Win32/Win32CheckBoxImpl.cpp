#include "Gui.h"
#include "Platform/Win32/Win32CheckBoxImpl.h"
#include "Platform/Win32/Win32Utils.h"

Win32CheckBoxImpl::Win32CheckBoxImpl(Graphics2D* p_graphics, WidgetStyle style) : ACheckBoxImpl(p_graphics, style),
    mp_textBrush(nullptr), mp_textFormat(nullptr),
    mp_edgeBrush(nullptr), mp_fillBrush(nullptr), mp_pathGeometry(nullptr) {

    initGraphicsResources();
}

Win32CheckBoxImpl::~Win32CheckBoxImpl() {

    Win32Utils::safeRelease(&mp_textBrush);
    Win32Utils::safeRelease(&mp_textFormat);

    Win32Utils::safeRelease(&mp_edgeBrush);
    Win32Utils::safeRelease(&mp_fillBrush);
    Win32Utils::safeRelease(&mp_pathGeometry);
}

void Win32CheckBoxImpl::onResize(Math::Rect textRect, Math::Rect boxRect) {

    m_textRect = textRect;
    m_boxRect = boxRect;

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
        Win32Utils::createRoundedRect(boxRect, m_style.getTopLeftRadius(), m_style.getTopRightRadius(), m_style.getBottomLeftRadius(), m_style.getBottomRightRadius(), mp_pathGeometry);
    }
}

void Win32CheckBoxImpl::onPaint(std::wstring text, WidgetState widgetState) {

    // get render target and write factory
    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();

    // check if render target exists
    if (p_renderTarget != nullptr) {

        // check if brush and text format exists
        if (mp_textBrush != nullptr && mp_textFormat != nullptr && mp_edgeBrush != nullptr && mp_fillBrush != nullptr && mp_pathGeometry != nullptr) {

            // set background color
            mp_fillBrush->SetColor(Win32Utils::D2D1Color(m_style.getFillColor(widgetState)));

            // draw box
            p_renderTarget->FillGeometry(mp_pathGeometry, mp_fillBrush);
            p_renderTarget->DrawGeometry(mp_pathGeometry, mp_edgeBrush, m_style.getEdgeThickness(), (ID2D1StrokeStyle*)m_style.getLineStyle());

            // draw text
            p_renderTarget->DrawTextW(text.c_str(), text.length(), mp_textFormat, Win32Utils::D2D1Rect(m_textRect), mp_textBrush);
        }
        else {
            initGraphicsResources();
        }
    }
}

void Win32CheckBoxImpl::initGraphicsResources() {

    // get render target and 2d factory
    ID2D1HwndRenderTarget* p_renderTarget = mp_graphics->getRenderTarget();
    ID2D1Factory1* p_2DFactory = mp_graphics->get2DFactory();
    IDWriteFactory* p_writeFactory = mp_graphics->getWriteFactory();

    if (p_renderTarget != nullptr && p_2DFactory != nullptr && p_writeFactory != nullptr) {

        // Create brush
        p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getEdgeColor()), &mp_edgeBrush);
        p_renderTarget->CreateSolidColorBrush(Win32Utils::D2D1Color(m_style.getFillColor(WidgetState::Normal)), &mp_fillBrush);

        // create path geometry
        p_2DFactory->CreatePathGeometry(&mp_pathGeometry);

        // Create brush
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
