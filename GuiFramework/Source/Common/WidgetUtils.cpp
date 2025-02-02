#include "Gui.h"
#include "Common/WidgetUtils.h"
#include <sstream>


Justification getJustification(Alignment& alignment, Orientation& orientation) {
	return (Justification)(orientation == Orientation::Horizontal ? alignment % 3 : alignment / 3);
}

std::wstring floatToString(float value) {

	std::wstringstream wss;
	wss << value;
	return wss.str();
}
