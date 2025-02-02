#include "Gui.h"
#include "Widgets/GroupBox.h"

GroupBox::GroupBox(Window* p_parent, Frame* p_frame, std::wstring title) : Layout(p_parent), mp_frame(p_frame), m_indent(5.0f) {

	// set default fill mode
	m_fillMode = FillMode::Shrink;

	// create label
	mp_label = new Label(p_parent, title, Style::Title());
	mp_label->setMargin(0);
	mp_label->setPadding(0);
	mp_label->setAlignment(Alignment::CenterLeft);
}

GroupBox::~GroupBox() {

	delete mp_label;
}

void GroupBox::onPaint() {

	// call parent function
	Layout::onPaint();

	// paint Label
	mp_label->onPaint();

	// paint frame
	mp_frame->onPaint();
}

void GroupBox::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// resize label
	mp_label->onResize(Math::Rect(m_contentRect.left(), m_contentRect.right(), m_contentRect.top(), m_contentRect.top() + mp_label->getMinSize().height()));

	// resize frame
	mp_frame->onResize(Math::Rect(m_contentRect.left() + m_indent, m_contentRect.right(), m_contentRect.top() + mp_label->getMinSize().height(), m_contentRect.bottom()));
}

void GroupBox::onTick(float deltaTime) {

	// check label
	if (mp_label->isImmediateMode())
		mp_label->onTick(deltaTime);
	if (mp_label->hasRequestedRedraw())
		mp_label->onPaint();

	// check frame
	if (mp_frame->isImmediateMode())
		mp_frame->onTick(deltaTime);
	if (mp_frame->hasRequestedRedraw())
		mp_frame->onPaint();
}

void GroupBox::onMouseHover(Math::Point2D point) {

	// check for label
	if (Math::pointInRect(mp_label->getHitbox(), point)) {

		// check if mouse was already hovering
		if (mp_label != m_mouseHoverFrame) {
			mp_label->onMouseEnter();
			m_mouseHoverFrame = mp_label;
		}

		mp_label->onMouseHover(point);
	}
	// check if mouse is registered as hovering
	else if (mp_label == m_mouseHoverFrame) {
		mp_label->onMouseLeave();
		m_mouseHoverFrame = nullptr;
	}

	// check for frame
	if (Math::pointInRect(mp_frame->getHitbox(), point)) {

		// check if mouse was already hovering
		if (mp_frame != m_mouseHoverFrame) {
			mp_frame->onMouseEnter();
			m_mouseHoverFrame = mp_frame;
		}

		mp_frame->onMouseHover(point);
	}
	// check if mouse is registered as hovering
	else if (mp_frame == m_mouseHoverFrame) {
		mp_frame->onMouseLeave();
		m_mouseHoverFrame = nullptr;
	}
}

void GroupBox::setFrame(Frame* p_frame) {

	mp_frame = p_frame;
}

void GroupBox::calcMinSize(){

	// calculate width and height
	float width = max(mp_label->getMinSize().width(), m_indent + mp_frame->getMinSize().width());
	float height = mp_label->getMinSize().height() + mp_frame->getMinSize().height();

	m_minSize = Math::Size(width + 2 * (m_margin + m_padding), height + 2 * (m_margin + m_padding));
}
