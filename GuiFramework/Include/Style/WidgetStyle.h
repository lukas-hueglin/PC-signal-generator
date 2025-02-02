#pragma once
#include "Gui.h"
#include "Style/Color.h"
#include "Common/WidgetUtils.h"

enum FontWeight {
	Thin = 100,
	Light = 300,
	Regular = 400,
	SemiBold = 600,
	Bold = 700,
	Heavy = 900
};

enum FontStyle {
	Standard = 0,
	Italic = 1,
	Oblique = 2
};

enum GUI_API LineStyle {
	Solid = 0,
	Dashed = 1,
	Dotted = 2
};

class WidgetStyleBuilder;

class GUI_API WidgetStyle {

private:
	Color m_edgeColor;

	Color m_normalFillColor;
	Color m_hoverFillColor;
	Color m_clickFillColor;

	Color m_normalHighlightColor;
	Color m_hoverHighlightColor;
	Color m_clickHighlightColor;

	Color m_textColor;
	FontWeight m_fontWeight;
	FontStyle m_fontStyle;

	Alignment m_textAlignment;

	LineStyle m_lineStyle;

	std::wstring m_fontName;
	float m_fontSize;

	float m_edgeThickness;

	float m_topLeftRadius;
	float m_topRightRadius;
	float m_bottomLeftRadius;
	float m_bottomRightRadius;


private:
	WidgetStyle();

public:
	static WidgetStyleBuilder create();

	Color& getEdgeColor();
	Color& getFillColor(WidgetState state);
	Color& getHighlightColor(WidgetState state);
	Color& getTextColor();

	FontWeight& getFontWeight();
	FontStyle& getFontStyle();

	Alignment getTextAlignment();

	LineStyle getLineStyle();

	std::wstring getFontName();
	float getFontSize();

	float getEdgeThickness();

	float getTopLeftRadius();
	float getTopRightRadius();
	float getBottomLeftRadius();
	float getBottomRightRadius();

	friend class WidgetStyleBuilder;
};