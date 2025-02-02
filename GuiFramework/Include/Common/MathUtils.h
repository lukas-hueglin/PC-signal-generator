#pragma once
#include "Gui.h"
#include "Common/WidgetUtils.h"
#include "Point2D.h"
#include "Size.h"
#include "Rect.h"


namespace Math {

	Rect expandRect(Rect& rect, float offset);
	Rect shrinkRect(Rect& rect, float offset);

	Rect minRect(Rect& a, Rect& b);
	Rect maxRect(Rect& a, Rect& b);

	bool pointInRect(Rect rect, Point2D point);
}