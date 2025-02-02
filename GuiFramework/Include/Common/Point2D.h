#pragma once
#include "Common/WidgetUtils.h"

namespace Math {

	class GUI_API Point2D {

	private:
		float m_x;
		float m_y;

	public:
		Point2D();
		Point2D(float x, float y);

	public:
		float& x();
		float& y();

		float length();

		float& operator[](Orientation orientation);

		Point2D operator+(Point2D point);
		Point2D operator-(Point2D point);
		Point2D operator*(float value);
		Point2D operator/(float value);
		Point2D& operator+=(Point2D point);
		Point2D& operator-=(Point2D point);
	};
}