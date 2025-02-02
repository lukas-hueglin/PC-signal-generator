#include "Gui.h"
#include "Widgets/Layout.h"
#include "Style/Style.h"

Layout::Layout(Window* p_parent, WidgetStyle style) : Frame(p_parent), m_mouseHoverFrame(nullptr), m_layoutImpl(mp_graphics, style) {
	
	// override FillMode to Expand
	m_fillMode = FillMode::Expand;

	// override immediate mode
	enableImmediateMode();
}

void Layout::onPaint() {

	// paint background
	m_layoutImpl.onPaint(m_usedRect);
}

void Layout::onResize(Math::Rect availableRect) {

	// calculate minimal size
	calcMinSize();

	// call parent function
	Frame::onResize(availableRect);
}

void Layout::onMouseEnter() {}

void Layout::onMouseLeave() {

	// make sure mouse left child frame
	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseLeave();
		m_mouseHoverFrame = nullptr;
	}
}

void Layout::onMouseDown(bool doubleClk, Math::Point2D point) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseDown(doubleClk, point);
	}
}

void Layout::onMouseRelease(Math::Point2D point) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseRelease(point);
	}
}

void Layout::onMouseScroll(bool up, bool shift, bool ctr) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onMouseScroll(up, shift, ctr);
	}
}

void Layout::onKeyDown(Key key) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onKeyDown(key);
	}
}

void Layout::onKeyDown(char key) {

	if (m_mouseHoverFrame != nullptr) {
		m_mouseHoverFrame->onKeyDown(key);
	}
}

Math::Size Layout::getMinSize() {

	calcMinSize();
	return m_minSize;
}
