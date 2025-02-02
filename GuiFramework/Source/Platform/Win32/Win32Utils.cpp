#include "Gui.h"
#include "Platform/Win32/Win32Utils.h"

D2D1_POINT_2F Win32Utils::D2D1Point(Math::Point2D point) {

    return D2D1::Point2F(point.x(), point.y());
}

D2D1_RECT_F Win32Utils::D2D1Rect(Math::Rect rect) {

    return D2D1::RectF(rect.left(), rect.top(), rect.right(), rect.bottom());
}

D2D1_COLOR_F Win32Utils::D2D1Color(Color color){

    return D2D1::ColorF(color.r, color.g, color.b, color.a);
}

Key Win32Utils::convertWin32Keys(WPARAM wParam) {

    if (wParam == 0x08) {
        return Key::Backspace;
    }
    else if (wParam == 0x09) {
        return Key::Tab;
    }
    else if (wParam == 0x0D) {
        return Key::Enter;
    }
    else if (wParam == 0x1B) {
        return Key::Esc;
    }
    else if (wParam == 0x2D) {
        return Key::Insert;
    }
    else if (wParam == 0x2E) {
        return Key::Delete;
    }
    else if (wParam >= 0x21 && wParam <= 0x28) {
        return static_cast<Key>(wParam);
    }
    else if (wParam >= 0x70 && wParam <= 0x7B) {
        return static_cast<Key>(wParam);
    }
    else {
        return Key::Empty;
    }
}

void Win32Utils::createRoundedRect(Math::Rect rect, float topLeftRadius, float topRightRadius, float bottomLeftRadius, float bottomRightRadius, ID2D1PathGeometry* p_pathGeometry) {

    // create hresult
    HRESULT hr;

    // create geometry sink
    ID2D1GeometrySink* p_sink;

    if (p_pathGeometry != nullptr) {

        // Write to the path geometry using the geometry sink.
        hr = p_pathGeometry->Open(&p_sink);

        if (SUCCEEDED(hr)) {

            // begin figure
            p_sink->BeginFigure(
                D2D1::Point2F(rect.left(), rect.top() + topLeftRadius),
                D2D1_FIGURE_BEGIN_FILLED
            );

            // topLeft
            p_sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(rect.left() + topLeftRadius, rect.top()), D2D1::SizeF(topLeftRadius, topLeftRadius), 90.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
            p_sink->AddLine(D2D1::Point2F(rect.right() - topRightRadius, rect.top()));

            // topRight
            p_sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(rect.right(), rect.top() + topRightRadius), D2D1::SizeF(topRightRadius, topRightRadius), 90.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
            p_sink->AddLine(D2D1::Point2F(rect.right(), rect.bottom() - bottomRightRadius));

            // bottomRight
            p_sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(rect.right() - bottomRightRadius, rect.bottom()), D2D1::SizeF(bottomRightRadius, bottomRightRadius), 90.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));
            p_sink->AddLine(D2D1::Point2F(rect.left() + bottomLeftRadius, rect.bottom()));

            // bottomLeft
            p_sink->AddArc(D2D1::ArcSegment(D2D1::Point2F(rect.left(), rect.bottom() - bottomLeftRadius), D2D1::SizeF(bottomLeftRadius, bottomLeftRadius), 90.0f, D2D1_SWEEP_DIRECTION_CLOCKWISE, D2D1_ARC_SIZE_SMALL));


            // end figure
            p_sink->EndFigure(D2D1_FIGURE_END_CLOSED);

            hr = p_sink->Close();
        }

        Win32Utils::safeRelease(&p_sink);
    }
}
