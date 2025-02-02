#include "Gui.h"
#include "Common/Point2D.h"
#include "Common/WidgetUtils.h"

#include <math.h>

Math::Point2D::Point2D() : m_x(0.0f), m_y(0.0f) { }

Math::Point2D::Point2D(float x, float y) : m_x(x), m_y(y) { }

float& Math::Point2D::x() {
	return m_x;
}

float& Math::Point2D::y() {
	return m_y;
}

float Math::Point2D::length() {
	return sqrt(m_x*m_x + m_y*m_y);
}

float& Math::Point2D::operator[](Orientation orientation) {
	return orientation == Orientation::Horizontal ? m_x : m_y;
}

Math::Point2D Math::Point2D::operator+(Point2D point) {

	return Point2D(m_x + point.x(), m_y + point.y());
}

Math::Point2D Math::Point2D::operator-(Point2D point) {

	return Point2D(m_x - point.x(), m_y - point.y());
}

Math::Point2D Math::Point2D::operator*(float value) {
	return Point2D(m_x * value, m_y * value);
}

Math::Point2D Math::Point2D::operator/(float value) {
	return Point2D(m_x / value, m_y / value);
}

Math::Point2D& Math::Point2D::operator+=(Point2D point) {

	m_x += point.x();
	m_y += point.y();
	return *this;
}

Math::Point2D& Math::Point2D::operator-=(Point2D point) {

	m_x -= point.x();
	m_y -= point.y();
	return *this;
}