#include "Gui.h"
#include "Widgets/PlotSeries.h"
#include "Style/Style.h"
#include "Widgets/Plot.h"

PlotSeries::PlotSeries(Plot* p_parent) : mp_parent(p_parent), mp_graphics(p_parent->mp_graphics), m_fillArea(false) { }

void PlotSeries::setFillArea(bool fillArea) {

	m_fillArea = fillArea;
}
