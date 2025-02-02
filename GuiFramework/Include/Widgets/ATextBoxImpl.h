#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/WidgetStyle.h"

class GUI_API ATextBoxImpl {

protected:
	WidgetStyle m_style;
	Graphics2D* mp_graphics;

public:
	ATextBoxImpl(Graphics2D* p_graphics, WidgetStyle style) : mp_graphics(p_graphics), m_style(style) { };

public:
	virtual void onResize(Math::Rect hitboxRect, Math::Rect contentRect) = 0;
	virtual void onPaint(WidgetState widgetState) = 0;
	virtual void onPaintCursor(int firstIndex, int lastIndex, bool dragFirstCursor, bool cursor) = 0;

	virtual void setText(std::wstring text) = 0;

	virtual int getMousePosition(Math::Point2D point) = 0;
	virtual Math::Rect getCursorPosition(int cursor, bool trailing = false) = 0;
};