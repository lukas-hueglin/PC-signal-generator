#pragma once
#include "Widgets/TextBox.h"

#ifdef WIN32
	#include "Platform/Win32/Win32SliderImpl.h"
	using SliderImpl = Win32SliderImpl;
#endif

template<typename T>
class GUI_API Slider : public TextBox {

private:
	T m_value;
	T m_min;
	T m_max;

	Math::Rect m_sliderRect;

	SliderImpl m_sliderImpl;

public:
	Slider(Window* p_parent, T value, T min=0, T max=1, WidgetStyle style = Style::Slider());

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseHover(Math::Point2D point) override;

	void setRequireDoubleClk(bool requireDoubleClk) = delete;

	Signal<T> onValueChanged;

private:
	bool filterInput(char key) override;

	void disableEditMode(bool backup);
};