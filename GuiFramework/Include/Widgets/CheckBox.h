#pragma once
#include "Widgets/Widget.h"
#include "Common/Signal.h"

#ifdef WIN32
	#include "Platform/Win32/Win32CheckBoxImpl.h"
	using CheckBoxImpl = Win32CheckBoxImpl;
#endif


class GUI_API CheckBox : public Widget {

protected:
	bool m_state;
	std::wstring m_text;

	float m_boxSize;

	Math::Rect m_textRect;
	Math::Rect m_boxRect;

	CheckBoxImpl m_checkBoxImpl;

public:
	CheckBox(Window* p_parent, std::wstring text, bool state, WidgetStyle style = Style::CheckBox());

	void onPaint() override;
	void onResize(Math::Rect availableRect);

	virtual void setText(std::wstring text);

	bool getState();
	void setState(bool state);

	void onMouseRelease(Math::Point2D point) override;

	Signal<bool> onStateChanged;
};