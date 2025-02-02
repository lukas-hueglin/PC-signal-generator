#include "Gui.h"
#include "Style/WidgetStyleBuilder.h"


WidgetStyleBuilder::WidgetStyleBuilder(WidgetStyle& widgetStyle) : m_widgetStyle(widgetStyle) { }

WidgetStyleBuilder& WidgetStyleBuilder::edgeColor(const Color& edgeColor) {

	m_widgetStyle.m_edgeColor = edgeColor;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::fillColor(const Color& fillColor, WidgetState state) {

	switch (state) {
	case WidgetState::Normal:
		m_widgetStyle.m_normalFillColor = fillColor;
		break;
	case WidgetState::Hover:
		m_widgetStyle.m_hoverFillColor = fillColor;
		break;
	case WidgetState::Click:
		m_widgetStyle.m_clickFillColor = fillColor;
	}
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::highlightColor(const Color& highlightColor, WidgetState state) {

	switch (state) {
	case WidgetState::Normal:
		m_widgetStyle.m_normalHighlightColor = highlightColor;
		break;
	case WidgetState::Hover:
		m_widgetStyle.m_hoverHighlightColor = highlightColor;
		break;
	case WidgetState::Click:
		m_widgetStyle.m_clickHighlightColor = highlightColor;
		break;
	}
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::textColor(const Color& textColor) {

	m_widgetStyle.m_textColor = textColor;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::fontWeight(const FontWeight& fontWeight) {

	m_widgetStyle.m_fontWeight = fontWeight;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::fontStyle(const FontStyle& fontStyle) {

	m_widgetStyle.m_fontStyle = fontStyle;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::textAlignment(const Alignment textAlignment) {

	m_widgetStyle.m_textAlignment = textAlignment;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::lineStyle(const LineStyle lineStyle) {

	m_widgetStyle.m_lineStyle = lineStyle;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::fontName(std::wstring fontName) {
	
	m_widgetStyle.m_fontName = fontName;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::fontSize(const float fontSize) {

	m_widgetStyle.m_fontSize = fontSize;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::edgeThickness(const float edgeThickness) {

	m_widgetStyle.m_edgeThickness = edgeThickness;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::radius(const float topLeft, const float topRight, const float bottomLeft, const float bottomRight) {

	m_widgetStyle.m_topLeftRadius = topLeft;
	m_widgetStyle.m_topRightRadius = topRight;
	m_widgetStyle.m_bottomLeftRadius = bottomLeft;
	m_widgetStyle.m_bottomRightRadius = bottomRight;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::radius(const float top, const float bottom) {

	m_widgetStyle.m_topLeftRadius = top;
	m_widgetStyle.m_topRightRadius = top;
	m_widgetStyle.m_bottomLeftRadius = bottom;
	m_widgetStyle.m_bottomRightRadius = bottom;
	return *this;
}

WidgetStyleBuilder& WidgetStyleBuilder::radius(const float radius) {

	m_widgetStyle.m_topLeftRadius = radius;
	m_widgetStyle.m_topRightRadius = radius;
	m_widgetStyle.m_bottomLeftRadius = radius;
	m_widgetStyle.m_bottomRightRadius = radius;
	return *this;
}

WidgetStyleBuilder::operator WidgetStyle() {

	return this->m_widgetStyle;
}
