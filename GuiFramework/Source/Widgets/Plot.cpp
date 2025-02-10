#include "Gui.h"
#include "Widgets/Plot.h"
#include "Style/Style.h"
#include "Common/WidgetUtils.h"

#include <iostream>
#include <math.h>
#include <numbers>

Plot::Plot(Window* p_parent, std::wstring xAxis, std::wstring yAxis, WidgetStyle style) :
	Widget(p_parent, style),
	
	m_plotRect(Math::Rect(0.f, 0.f, 0.f, 0.f)), m_plotBounds(Math::Rect(0.f, 1.f, 1.f, 0.f)),
	m_xAxis(xAxis), m_yAxis(yAxis),
	m_xAxisScale(AxisScale::Linear), m_yAxisScale(AxisScale::Linear),
	m_lockXZoom(false), m_lockYZoom(false),
	m_xAxisUnit(Unit::Second), m_yAxisUnit(Unit::Volts),
	m_plotImpl(mp_graphics, style) { }

void Plot::onPaint() {

	// draw background
	m_widgetImpl.onPaint();

	// draw axis
	m_plotImpl.onPaintAxis(m_xAxis + L" / " + unit_symbols[m_xAxisUnit], m_yAxis + L" / " + unit_symbols[m_yAxisUnit]);

	// define prescaler
	float prescaler_x = m_xAxisUnit == Unit::Radians ? std::numbers::pi : 1.0f;
	float prescaler_y = m_yAxisUnit == Unit::Radians ? std::numbers::pi : 1.0f;

	// get width and height
	float width = m_plotBounds.getWidth() / prescaler_x;
	float height = -m_plotBounds.getHeight() / prescaler_y;

	// calculate step width
	float xStep, yStep;
	if (m_xAxisUnit == Unit::Radians) {
		xStep = calculateTickStep(width, 4, 2, 1);
	}
	else {
		xStep = calculateTickStep(width, 5, 10, 5);
	}
	if (m_yAxisUnit == Unit::Radians) {
		yStep = calculateTickStep(height, 4, 2, 1);
	}
	else {
		yStep = calculateTickStep(height, 5, 10, 5);
	}

	// calculate starting point
	// shift plot bounds magnitude_x/y numer of decimal places to the left before ceiling
	float x0 = ceil(m_plotBounds.left() / xStep / prescaler_x) * xStep;
	float y0 = ceil(m_plotBounds.bottom() / yStep / prescaler_y) * yStep;

	// create suffix (pi if unit is radians and else empty
	std::wstring xSuffix = m_xAxisUnit == Unit::Radians ? L"\u03C0" : L"";
	std::wstring ySuffix = m_yAxisUnit == Unit::Radians ? L"\u03C0" : L"";

	// draw 25 lines
	for (int i = 0; i < 25; ++i) {

		float x = x0 + xStep * i;
		float y = y0 + yStep * i;

		Math::Point2D screenSpace = plotToScreenSpace(Math::Point2D(x * prescaler_x, y * prescaler_y));

		// check if line is in plot
		if (prescaler_x * x < m_plotBounds.right()) {

			m_plotImpl.onPaintVerticalTicks(screenSpace.x(), floatToString(x) + xSuffix);
		}
		if (prescaler_y * y < m_plotBounds.top()) {
			m_plotImpl.onPaintHorizontalTicks(screenSpace.y(), floatToString(y) + ySuffix);
		}
	}

	// plot series
	for (PlotSeries* p_series : mp_series) {
		p_series->onPaint(m_plotRect);
	}
}

void Plot::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	m_plotRect = Math::shrinkRect(m_contentRect, 60);

	// update plot rect of plot implementation
	m_plotImpl.onResize(m_plotRect, Math::Rect());
}

void Plot::onMouseHover(Math::Point2D point) {

	// call parent function
	Widget::onMouseHover(point);

	if (m_mouseDown) {
		Math::Point2D translation = relativeScreenToPlotSpace(m_mouseDelta);
		m_plotBounds.topLeft() += translation;
		m_plotBounds.bottomRight() += translation;

		requestRedraw();
	}
}

void Plot::onMouseScroll(bool up, bool shift, bool ctr) {

	// get zoom factor
	float zoom = up ? 0.666f : 1.5f;

	// create variables
	float left, right, top, bottom;

	// dont scale y if shift is pressed
	if (shift) {
		top = m_plotBounds.top();
		bottom = m_plotBounds.bottom();
	}
	else {
		top = (m_plotBounds.top() - m_plotBounds.getCenter().y()) * zoom + m_plotBounds.getCenter().y();
		bottom = (m_plotBounds.bottom() - m_plotBounds.getCenter().y()) * zoom + m_plotBounds.getCenter().y();
	}

	// calculate horizontal component
	left = (m_plotBounds.left() - m_plotBounds.getCenter().x()) * zoom + m_plotBounds.getCenter().x();
	right = (m_plotBounds.right() - m_plotBounds.getCenter().x()) * zoom + m_plotBounds.getCenter().x();

	m_plotBounds = Math::Rect(left, right, top, bottom);

	requestRedraw();
}

void Plot::setLockXZoom(bool lock) {

	m_lockXZoom = lock;
}

void Plot::setLockYZoom(bool lock) {

	m_lockYZoom = lock;
}

void Plot::setXAxisScale(AxisScale scale) {

	m_xAxisScale = scale;
}

void Plot::setYAxisScale(AxisScale scale) {

	m_yAxisScale = scale;
}

void Plot::setXUnit(Unit unit) {

	m_xAxisUnit = unit;
}

void Plot::setYUnit(Unit unit) {

	m_yAxisUnit = unit;
}

void Plot::addPlotSeries(PlotSeries* p_plotSeries) {

	mp_series.push_back(p_plotSeries);
}

Math::Point2D Plot::plotToScreenSpace(Math::Point2D point) {

	float x = (point.x() - m_plotBounds.left()) / m_plotBounds.getWidth() * m_plotRect.getWidth() + m_plotRect.left();
	float y = (point.y() - m_plotBounds.bottom()) / m_plotBounds.getHeight() * m_plotRect.getHeight() + m_plotRect.bottom();

	return Math::Point2D(x, y);
}

Math::Point2D Plot::screenToPlotSpace(Math::Point2D point) {

	float x = (point.x() - m_plotRect.left()) / m_plotRect.getWidth() * m_plotBounds.getWidth() + m_plotBounds.left();
	float y = (point.y() - m_plotRect.bottom()) / m_plotRect.getHeight() * m_plotBounds.getHeight() + m_plotBounds.bottom();

	return Math::Point2D(x, y);
}

Math::Point2D Plot::relativeScreenToPlotSpace(Math::Point2D point) {

	float x = point.x() / m_plotRect.getWidth() * m_plotBounds.getWidth();
	float y = point.y() / m_plotRect.getHeight() * m_plotBounds.getHeight();

	return Math::Point2D(x, y);
}

float Plot::calculateTickStep(float width, int prefDivs, int base, float prefactor) {

	// calculate approximate step width
	float approxStep = width / prefDivs;

	// get number of digits in decimal representation
	float digits = floor(logf(approxStep) / logf(base));

	// calculate magnitude of step (base^n)
	float mag = powf(base, digits);

	// calculate real step (prefactor*base^n or base^n)
	float step = approxStep / mag >= prefactor / 2 ? prefactor * mag : mag;

	return step;
}