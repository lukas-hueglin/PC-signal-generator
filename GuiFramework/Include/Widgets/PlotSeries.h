#pragma once
#include "Style/Color.h"
#include "Core/Graphics2D.h"
#include "Common/MathUtils.h"

// forward declare Plot
class Plot;

class GUI_API PlotSeries {

protected:
	Plot* mp_parent;
	Graphics2D* mp_graphics;

	bool m_fillArea;

public:
	PlotSeries(Plot* p_parent);

public:
	virtual void onUpdate() = 0;

	virtual void onPaint(Math::Rect& available) = 0;

	virtual void setColor(Color color) = 0;

	void setFillArea(bool fillArea);

};