#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/WidgetStyle.h"


class GUI_API APlotImpl {

protected:
	Math::Rect m_plotRect;
	Math::Rect m_legendRect;

	WidgetStyle m_style;
	Graphics2D* mp_graphics;

public:
	APlotImpl(Graphics2D* p_graphics, WidgetStyle style) : mp_graphics(p_graphics), m_style(style) { };

public:
	virtual void onResize(Math::Rect plotRect, Math::Rect legendRect) = 0;

	virtual void onPaintAxis(std::wstring xAxisText, std::wstring yAxisText) = 0;

	virtual void onPaintHorizontalTicks(float value, std::wstring text) = 0;
	virtual void onPaintVerticalTicks(float value, std::wstring text) = 0;

	//virtual void onPaintLegendBackground() = 0;
};