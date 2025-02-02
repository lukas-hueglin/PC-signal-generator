#pragma once
#include "Widgets/Label.h"
#include "Common/Signal.h"

#ifdef WIN32
	#include "Platform/Win32/Win32ButtonImpl.h"
	using ButtonImpl = Win32ButtonImpl;
#endif

class GUI_API Button : public Label {

protected:
	ButtonImpl m_buttonImpl;

public:
	Button(Window* p_parent, std::wstring text, WidgetStyle style = Style::Default());

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseRelease(Math::Point2D point) override;

	Signal<> onButtonClick;
	Signal<int> onButtonClickId;
};