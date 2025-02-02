#include "Gui.h"
#include "Style/Palette.h"

Color Palette::Background() {

	return Color(0x232323);
}

Color Palette::PrimaryWidget() {

	return Color(0x282b32);
}

Color Palette::SecondaryWidget() {

	return Color(0x1f2126);
}

Color Palette::Highlight() {

	return Color::RoyalBlue;
}

Color Palette::Text() {

	return Color::Silver;
}

Color Palette::TextSelection()
{
	return Color::RoyalBlue.makeTransparent(0.5);
}

Color Palette::Debug1() {

	return Color::Red;
}

Color Palette::Debug2() {

	return Color::Green;
}

Color Palette::Debug3() {

	return Color::Blue;
}

Color Palette::Plot(int index) {

	switch (index % 4) {
	case 0:
		return Color::Yellow;
	case 1:
		return Color::DodgerBlue;
	case 2:
		return Color::LimeGreen;
	case 3:
		return Color::Magenta;
	}
}
