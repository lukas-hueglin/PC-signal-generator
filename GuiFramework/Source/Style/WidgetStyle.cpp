#include "Gui.h"
#include "Style/WidgetStyle.h"
#include "Style/WidgetStyleBuilder.h"

WidgetStyle::WidgetStyle() :
	m_edgeColor(Color::Transparent),
	m_normalFillColor(Color::Transparent),
	m_hoverFillColor(Color::Transparent),
	m_clickFillColor(Color::Transparent),
	m_normalHighlightColor(Color::Transparent),
	m_hoverHighlightColor(Color::Transparent),
	m_clickHighlightColor(Color::Transparent),
	m_textColor(Color::Black),

	m_lineStyle(LineStyle::Solid),

	m_fontName(L"SegoeUI"),
	m_fontSize(12),
	m_fontWeight(FontWeight::Regular),
	m_fontStyle(FontStyle::Standard),

	m_edgeThickness(1.0f),

	m_topLeftRadius(0.0f),
	m_topRightRadius(0.0f),
	m_bottomLeftRadius(0.0f),
	m_bottomRightRadius(0.0f) { }


WidgetStyleBuilder WidgetStyle::create() {

	WidgetStyle s;
	return WidgetStyleBuilder(s);
}

Color& WidgetStyle::getEdgeColor() {
	return m_edgeColor;
}

Color& WidgetStyle::getFillColor(WidgetState state) {

	switch (state) {
	case WidgetState::Normal:
		return m_normalFillColor;
	case WidgetState::Hover:
		return m_hoverFillColor;
	case WidgetState::Click:
		return m_clickFillColor;
	}
}

Color& WidgetStyle::getHighlightColor(WidgetState state) {

	switch (state) {
	case WidgetState::Normal:
		return m_normalHighlightColor;
	case WidgetState::Hover:
		return m_hoverHighlightColor;
	case WidgetState::Click:
		return m_clickHighlightColor;
	}
}

Color& WidgetStyle::getTextColor() {

	return m_textColor;
}

FontWeight& WidgetStyle::getFontWeight() {

	return m_fontWeight;
}

FontStyle& WidgetStyle::getFontStyle() {
	
	return m_fontStyle;
}

Alignment WidgetStyle::getTextAlignment() {

	return m_textAlignment;
}

LineStyle WidgetStyle::getLineStyle() {
	return m_lineStyle;
}

std::wstring WidgetStyle::getFontName() {
	return m_fontName;
}

float WidgetStyle::getFontSize() {
	return m_fontSize;
}

float WidgetStyle::getEdgeThickness() {
	return m_edgeThickness;
}

float WidgetStyle::getTopLeftRadius() {
	return m_topLeftRadius;
}

float WidgetStyle::getTopRightRadius() {
	return m_topRightRadius;
}

float WidgetStyle::getBottomLeftRadius() {
	return m_bottomLeftRadius;
}

float WidgetStyle::getBottomRightRadius() {
	return m_bottomRightRadius;
}
