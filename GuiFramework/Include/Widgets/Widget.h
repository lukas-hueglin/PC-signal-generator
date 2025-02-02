#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Core/Graphics2D.h"
#include "Common/WidgetUtils.h"
#include "Widgets/Frame.h"
#include "Style/WidgetStyle.h"
#include "Style/Style.h"

#ifdef WIN32
	#include "Platform/Win32/Win32WidgetImpl.h"
	using WidgetImpl = Win32WidgetImpl;
#endif


class GUI_API Widget : public Frame {

protected:
	int m_id;

	bool m_mouseHover;
	bool m_mouseDown;

	Math::Point2D m_lastMousePos;
	Math::Point2D m_mouseDelta;

	WidgetImpl m_widgetImpl;

public:
	Widget(Window* p_parent, WidgetStyle style = Style::Default());

	virtual void onPaint();
	virtual void onTick(float deltaTime);

	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point);
	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseDown(bool doubleClk, Math::Point2D point);
	virtual void onMouseRelease(Math::Point2D point);
	virtual void onMouseScroll(bool up, bool shift, bool ctr);

	virtual void onKeyDown(Key key);
	virtual void onKeyDown(char key);

	void setId(int id);
	int getId();
};