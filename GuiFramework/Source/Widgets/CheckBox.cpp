#include "Gui.h"
#include "Widgets/CheckBox.h"

CheckBox::CheckBox(Window* p_parent, std::wstring text, bool state, WidgetStyle style): Widget(p_parent, style), m_text(text), m_state(state), m_boxSize(15.0f), m_checkBoxImpl(mp_graphics, style) { }

void CheckBox::onPaint() {

	// draw background by calling the widgetImpl's onPaint
	m_widgetImpl.onPaint();

	// draw checkbox
	WidgetState state = m_mouseHover ? WidgetState::Hover : m_state ? WidgetState::Click : WidgetState::Normal;
	m_checkBoxImpl.onPaint(m_text, state);

	// call master parent function
	Frame::onPaint();
}

void CheckBox::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	m_boxRect = Math::Rect(m_contentRect.left(), m_contentRect.left() + m_boxSize, m_contentRect.getCenter().y() - m_boxSize/2, m_contentRect.getCenter().y() + m_boxSize / 2);
	m_textRect = Math::Rect(m_contentRect.left() + m_boxSize + 5.0f, m_contentRect.right(), m_contentRect.top(), m_contentRect.bottom());

	// call resize on implementation
	m_checkBoxImpl.onResize(m_textRect, m_boxRect);
}

void CheckBox::setText(std::wstring text) {

	m_text = text;
}

bool CheckBox::getState() {

	return m_state;
}

void CheckBox::setState(bool state) {

	m_state = state;
	requestRedraw();

	EMIT(onStateChanged, m_state);
}

void CheckBox::onMouseRelease(Math::Point2D point) {

	// call parent first, then call connected function
	Widget::onMouseRelease(point);

	m_state = !m_state;
	EMIT(onStateChanged, m_state);
}
