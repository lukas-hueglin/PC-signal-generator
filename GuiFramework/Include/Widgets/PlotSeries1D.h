#pragma once
#include "Widgets/PlotSeries.h"

#ifdef WIN32
	#include "Platform/Win32/Win32PlotSeries1DImpl.h"
	using PlotSeries1DImpl = Win32PlotSeries1DImpl;
#endif

class GUI_API PlotSeries1D : public PlotSeries {

private:
	float* mpa_data;

	float m_lowerBound;
	float m_upperBound;

	int m_size;
	int m_head;

protected:
	PlotSeries1DImpl m_plotSeries1DImpl;

public:
	PlotSeries1D(Plot* p_parent, float* pa_data, float lower, float upper, int size, Color color);

public:
	void onUpdate() override;

	void onPaint(Math::Rect& available) override;

	void setColor(Color color) override;

	void setBounds(float lower, float upper);

	void setHead(int head);
};