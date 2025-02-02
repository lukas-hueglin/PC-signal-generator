#include "Gui.h"
#include "Common/Size.h"

Math::Size::Size() :m_width(0.0f), m_height(0.0f) { }

Math::Size::Size(float width, float height) : m_width(width), m_height(height) { }

Math::Size::Size(Point2D point) : m_width(point.x()), m_height(point.y()) { }

float& Math::Size::width() {

	return m_width;
}

float& Math::Size::height() {

	return m_height;
}

float& Math::Size::operator[](Orientation orientation) {
	return orientation == Orientation::Horizontal ? m_width : m_height;
}

Math::Size Math::Size::operator+(Size size) {

	return Size(m_width + size.width(), m_height + size.height());
}

Math::Size Math::Size::operator-(Size size) {

	return Size(m_width - size.width(), m_height - size.height());
}

Math::Size Math::Size::operator*(float value) {
	return Size(m_width * value, m_height * value);
}

Math::Size Math::Size::operator/(float value) {
	return Size(m_width / value, m_height / value);
}

Math::Size& Math::Size::operator+=(Size size) {

	m_width += size.width();
	m_height += size.height();
	return *this;
}

Math::Size& Math::Size::operator-=(Size size) {

	m_width -= size.width();
	m_height -= size.height();
	return *this;
}