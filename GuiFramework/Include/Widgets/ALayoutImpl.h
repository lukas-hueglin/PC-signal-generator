#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/WidgetStyle.h"

class GUI_API ALayoutImpl {

protected:
	WidgetStyle m_style;
	Graphics2D* mp_graphics;

public:
	ALayoutImpl(Graphics2D* p_graphics, WidgetStyle style) : mp_graphics(p_graphics), m_style(style) { };

public:
	virtual void onPaint(Math::Rect usedRect) = 0;
};