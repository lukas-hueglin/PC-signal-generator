#pragma once
#include "Gui.h"
#include "Style/WidgetStyle.h"

class GUI_API WidgetStyleBuilder {

private:
    WidgetStyle m_widgetStyle;

public:
    WidgetStyleBuilder(WidgetStyle& widgetStyle);

public:
    WidgetStyleBuilder& edgeColor(const Color& edgeColor);
    WidgetStyleBuilder& fillColor(const Color& fillColor, WidgetState state);
    WidgetStyleBuilder& highlightColor(const Color& highlightColor, WidgetState state);
    WidgetStyleBuilder& textColor(const Color& textColor);

    WidgetStyleBuilder& fontWeight(const FontWeight& fontWeight);
    WidgetStyleBuilder& fontStyle(const FontStyle& fontStyle);

    WidgetStyleBuilder& textAlignment(const Alignment textAlignment);

    WidgetStyleBuilder& lineStyle(const LineStyle lineStyle);

    WidgetStyleBuilder& fontName(std::wstring fontName);
    WidgetStyleBuilder& fontSize(const float fontSize);

    WidgetStyleBuilder& edgeThickness(const float edgeThickness);

    WidgetStyleBuilder& radius(const float topLeft, const float topRight, const float bottomLeft, const float bottomRight);
    WidgetStyleBuilder& radius(const float top, const float bottom);
    WidgetStyleBuilder& radius(const float radius);

    // conversion operator
    operator WidgetStyle();
};