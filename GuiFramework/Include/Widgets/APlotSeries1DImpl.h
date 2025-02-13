#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"
#include "Style/Color.h"

#include <vector>

class GUI_API APlotSeries1DImpl {

protected:
	Color m_color;
	Graphics2D* mp_graphics;

public:
	APlotSeries1DImpl(Graphics2D* p_graphics, Color color) : mp_graphics(p_graphics), m_color(color) { };

public:
	virtual void onUpdate(float* pa_data, int size, int head, float lowerBound, float upperBound) = 0;

	virtual void onPaint(Math::Rect availableRect, Math::Rect plotBounds, bool fillArea) = 0;

	virtual void setColor(Color color) = 0;
};