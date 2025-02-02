#pragma once
#include "Style/WidgetStyle.h"

class GUI_API Style {

public:
	Style() = delete;

public:
	static WidgetStyle Default();
	static WidgetStyle Layout();
	static WidgetStyle Slider();
	static WidgetStyle CheckBox();
	static WidgetStyle Title();

	static WidgetStyle DropDown(Justification justification);
};