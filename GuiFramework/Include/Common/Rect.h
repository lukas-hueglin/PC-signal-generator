#pragma once
#include <memory>
#include "Common/Point2D.h"
#include "Common/Size.h"

namespace Math {

	class GUI_API Rect {

	private:
		Point2D m_topLeft;
		Point2D m_bottomRight;

	public:
		Rect();
		Rect(float left, float right, float top, float bottom);
		Rect(Point2D& topLeft, Point2D& bottomRight);
		Rect(RECT& rect);

	public:
		float& left();
		float& right();
		float& top();
		float& bottom();

		Point2D& topLeft();
		Point2D& bottomRight();

		Point2D getCenter();
		Size getSize();
		float getWidth();
		float getHeight();
	};
}