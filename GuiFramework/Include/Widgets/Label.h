#pragma once
#include "Widgets/Widget.h"

#ifdef WIN32
	#include "Platform/Win32/Win32LabelImpl.h"
	using LabelImpl = Win32LabelImpl;
#endif


class GUI_API Label : public Widget {

protected:
	std::wstring m_text;

	LabelImpl m_labelImpl;

public:
	Label(Window* p_parent, std::wstring text, WidgetStyle style = Style::Default());

	void onPaint() override;
	void onResize(Math::Rect availableRect);

	virtual void setText(std::wstring text);
};