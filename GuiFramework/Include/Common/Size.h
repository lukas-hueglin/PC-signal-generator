#pragma once
#include "Common/Point2D.h"

namespace Math {

	class GUI_API Size {

	private:
		float m_width;
		float m_height;

	public:
		Size();
		Size(float width, float height);
		Size(Point2D point);

	public:
		float& width();
		float& height();

		float& operator[](Orientation orientation);

		Size operator+(Size point);
		Size operator-(Size point);
		Size operator*(float value);
		Size operator/(float value);
		Size& operator+=(Size point);
		Size& operator-=(Size point);
	};
}