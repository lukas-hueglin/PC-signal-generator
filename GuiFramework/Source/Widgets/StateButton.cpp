#include "Gui.h"
#include "Widgets/StateButton.h"
#include "Style/Style.h"

StateButton::StateButton(Window* p_parent, std::vector<std::wstring> texts, WidgetStyle style) :
	Label(p_parent, texts.at(0), style), m_state(0), m_texts(texts), m_buttonImpl(mp_graphics, style) {}

void StateButton::onPaint() {

	// draw background by calling the widgetImpl's onPaint
	//m_widgetImpl.onPaint();

	// draw box
	WidgetState state = m_mouseDown ? WidgetState::Click : m_mouseHover ? WidgetState::Hover : WidgetState::Normal;
	m_buttonImpl.onPaint(state);

	// draw text
	m_labelImpl.onPaint(m_texts.at(m_state));

	// call master parent function
	Frame::onPaint();
}

void StateButton::onResize(Math::Rect availableRect) {

	// call parent function
	Label::onResize(availableRect);

	m_buttonImpl.onResize(m_hitboxRect);
}

void StateButton::onMouseRelease(Math::Point2D point) {

	// call parent first, then call connected function
	Widget::onMouseRelease(point);

	// increase state
	m_state = ( m_state + 1 ) % m_texts.size();

	EMIT(onStateChanged, m_state);
}

void StateButton::setState(int state) {

	m_state = state;
	requestRedraw();

	EMIT(onStateChanged, m_state);
}

int StateButton::getState() {

	return m_state;
}
