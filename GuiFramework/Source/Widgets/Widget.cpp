#include "Gui.h"
#include "Widgets/Widget.h"
#include "Style/Style.h"

Widget::Widget(Window<Graphics2D>* p_parent) :
	mp_graphics(p_parent->getGraphics()),

	m_minSize(Math::Rect(0, 0, 0, 0)),
	m_usedRect(Math::Rect(0, 0, 0, 0)),
	m_hitboxRect(Math::Rect(0, 0, 0, 0)),
	m_contentRect(Math::Rect(0, 0, 0, 0)),

	m_margin(0), m_padding(0),

	m_alignment(Alignment::Center),
	m_fillMode(FillMode::Expand),

	m_mouseHover(false),
	m_mouseDown(false) {}

void Widget::onPaint() {}

void Widget::onResize(Math::Rect availableRect) {

	m_usedRect = availableRect;
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::onMouseHover(Math::Point2D point) {

	// check for child hover

}

void Widget::onMouseEnter() {

	m_mouseHover = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseLeave() {

	m_mouseHover = false;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseDown() {

	// check for child click
	m_mouseDown = true;
	mp_graphics->scheduleRedraw();
}

void Widget::onMouseRelease() {

	// check for child release
	m_mouseDown = false;
	mp_graphics->scheduleRedraw();
}

void Widget::setMargin(float margin) {

	m_margin = margin;

	// update hitbox and content rect
	m_hitboxRect = Math::shrinkRect(m_usedRect, m_margin);
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

void Widget::setPadding(float padding) {

	m_padding = padding;

	// update content rect
	m_contentRect = Math::shrinkRect(m_hitboxRect, m_padding);
}

bool Widget::isMouseHovering() {

	return m_mouseHover;
}

Math::Rect Widget::getHitbox() {

	return m_hitboxRect;
}
