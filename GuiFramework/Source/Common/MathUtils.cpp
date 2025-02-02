#include "Gui.h"
#include "Common/MathUtils.h"


Math::Rect Math::expandRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left() - offset, rect.right() + offset, rect.top() - offset, rect.bottom() + offset);
}

Math::Rect Math::shrinkRect(Math::Rect& rect, float offset) {
	return Math::Rect(rect.left() + offset, rect.right() - offset, rect.top() + offset, rect.bottom() - offset);
}

Math::Rect Math::minRect(Math::Rect& a, Math::Rect& b) {
	return Math::Rect(max(a.left(), b.left()), min(a.right(), b.right()), max(a.top(), b.top()), min(a.bottom(), b.bottom()));
}

Math::Rect Math::maxRect(Math::Rect& a, Math::Rect& b) {
	return Math::Rect(min(a.left(), b.left()), max(a.right(), b.right()), min(a.top(), b.top()), max(a.bottom(), b.bottom()));
}

bool Math::pointInRect(Rect rect, Point2D point) {

	return rect.left() < point.x() && rect.right() > point.x() && rect.top() < point.y() && rect.bottom() > point.y();
}
