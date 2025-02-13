#include "Gui.h"
#include "Widgets/ComboBox.h"
#include "Widgets/DropDown.h"

ComboBox::ComboBox(Window* p_parent, std::vector<std::wstring> elements, WidgetStyle style) : Button(p_parent, elements.at(0), style), m_state(0), m_elements(elements), m_style(style) {

	// connect in such a way, that a dropdown is created, when the button is clicked
	connect<ComboBox, ComboBox>(this, &ComboBox::createDropDown, onButtonClick);
}

void ComboBox::setState(int state) {

	m_state = state;
}

int ComboBox::getState() {

	return m_state;
}

void ComboBox::createDropDown() {

	// create drop down
	DropDown* p_dropDown = new DropDown(mp_parent, this, Math::Point2D(Frame::m_hitboxRect.left(), Frame::m_hitboxRect.bottom()), m_elements, m_style);

	// connect drop down
	connect<DropDown, ComboBox, int>(this, &ComboBox::closeDropDown, p_dropDown->onDropDownClose);

	// register dropdown
	mp_parent->registerDropDown(p_dropDown);
}

void ComboBox::closeDropDown(int index) {

	if (m_state != index) {

		m_state = index;
		m_text = m_elements.at(index);

		// emit on value changed signal
		EMIT(onValueChanged, m_state)
	}

	requestRedraw();
	mp_parent->unregisterDropDown();
}