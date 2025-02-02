#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/WidgetStyle.h"

class GUI_API ASliderImpl {

protected:
	WidgetStyle m_style;
	Graphics2D* mp_graphics;

public:
	ASliderImpl(Graphics2D* p_graphics, WidgetStyle style) : mp_graphics(p_graphics), m_style(style) { };

public:
	virtual void onResize(Math::Rect hitboxRect) = 0;
	virtual void onPaint(Math::Rect sliderRect, WidgetState widgetState) = 0;
};