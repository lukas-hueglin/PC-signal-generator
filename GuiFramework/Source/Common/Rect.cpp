#include "Gui.h"
#include "Common/Rect.h"

Math::Rect::Rect() : m_topLeft(Math::Point2D()), m_bottomRight(Math::Point2D()) { }

Math::Rect::Rect(float left, float right, float top, float bottom) : m_topLeft(Math::Point2D(left, top)), m_bottomRight(Math::Point2D(right, bottom)) {}

Math::Rect::Rect(Point2D& topLeft, Point2D& bottomRight) : m_topLeft(topLeft), m_bottomRight(bottomRight) { }

Math::Rect::Rect(RECT& rect) : Rect(rect.left, rect.right, rect.top, rect.bottom) { }

float& Math::Rect::left() {
	return m_topLeft.x();
}

float& Math::Rect::right() {
	return m_bottomRight.x();
}

float& Math::Rect::top() {
	return m_topLeft.y();
}

float& Math::Rect::bottom() {
	return m_bottomRight.y();
}

Math::Point2D& Math::Rect::topLeft() {
	return m_topLeft;
}

Math::Point2D& Math::Rect::bottomRight() {
	return m_bottomRight;
}

float Math::Rect::getWidth() {
	return m_bottomRight.x() - m_topLeft.x();
}

float Math::Rect::getHeight() {
	return m_bottomRight.y() - m_topLeft.y();
}

Math::Point2D Math::Rect::getCenter() {
	return (m_topLeft + m_bottomRight) / 2;
}

Math::Size Math::Rect::getSize() {
	return Math::Size(m_bottomRight - m_topLeft);
}