#include "Gui.h"
#include "Widgets/PlotSeries1D.h"
#include "Widgets/Plot.h"
#include "Core/Graphics2D.h"

#include <vector>

PlotSeries1D::PlotSeries1D(Plot* p_parent, float* pa_data, float lower, float upper, int size, Color color) :
	PlotSeries(p_parent), mpa_data(pa_data), m_size(size), m_plotSeries1DImpl(mp_graphics, color), m_head(0) {

	// set bounds, that way a x data array is initialized
	setBounds(lower, upper);

	// update first time
	onUpdate();
}

void PlotSeries1D::onUpdate() {

	m_plotSeries1DImpl.onUpdate(mpa_data, m_size, m_head, m_lowerBound, m_upperBound);
}

void PlotSeries1D::onPaint(Math::Rect& available) {

	m_plotSeries1DImpl.onPaint(available, mp_parent->getPlotBounds(), m_fillArea);
}

void PlotSeries1D::setColor(Color color) {

	m_plotSeries1DImpl.setColor(color);
}

void PlotSeries1D::setBounds(float lower, float upper) {

	m_lowerBound = lower;
	m_upperBound = upper;
}

void PlotSeries1D::setHead(int head) {

	m_head = head;
}
