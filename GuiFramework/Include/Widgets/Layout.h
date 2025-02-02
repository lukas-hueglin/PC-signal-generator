#pragma once
#include "Widgets/Frame.h"
#include "Style/Style.h"
#include <vector>

#ifdef WIN32
	#include "Platform/Win32/Win32LayoutImpl.h"
	using LayoutImpl = Win32LayoutImpl;
#endif

class GUI_API Layout : public Frame {

protected:
	LayoutImpl m_layoutImpl;
	Frame* m_mouseHoverFrame;

public:
	Layout(Window* p_parent, WidgetStyle style = Style::Layout());

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseEnter() override;
	void onMouseLeave() override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onMouseRelease(Math::Point2D point) override;
	void onMouseScroll(bool up, bool shift, bool ctr) override;

	void onKeyDown(Key key);
	void onKeyDown(char key);

	Math::Size getMinSize() override;

private:
	virtual void calcMinSize() = 0;
};