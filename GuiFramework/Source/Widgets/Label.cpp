#include "Gui.h"
#include "Widgets/Label.h"
#include "Style/Style.h"

Label::Label(Window* p_parent, std::wstring text, WidgetStyle style) : Widget(p_parent, style), m_text(text), m_labelImpl(mp_graphics, style) { }

void Label::onPaint() {

	// draw background by calling the widgetImpl's onPaint
	m_widgetImpl.onPaint();

	// draw text
	m_labelImpl.onPaint(m_text);

	// call master parent function
	Frame::onPaint();
}

void Label::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	m_labelImpl.onResize(m_contentRect);
}

void Label::setText(std::wstring text) {

	m_text = text;
}
