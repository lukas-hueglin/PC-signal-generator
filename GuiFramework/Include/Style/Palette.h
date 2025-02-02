#pragma once
#include "Gui.h"
#include "Style/Color.h"

class GUI_API Palette {

public:
	Palette() = delete;

public:
	static Color Background();

	static Color PrimaryWidget();
	static Color SecondaryWidget();
	static Color Highlight();

	static Color Text();
	static Color TextSelection();

	static Color Debug1();
	static Color Debug2();
	static Color Debug3();

	static Color Plot(int index);
};