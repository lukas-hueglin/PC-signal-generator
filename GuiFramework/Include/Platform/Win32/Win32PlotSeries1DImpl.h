#pragma once
#include "Widgets/APlotSeries1DImpl.h"
#include <vector>

class GUI_API Win32PlotSeries1DImpl : public APlotSeries1DImpl {

private:
	ID2D1SolidColorBrush* mp_edgeBrush;
	ID2D1SolidColorBrush* mp_fillBrush;

	ID2D1PathGeometry* mp_edgePathGeometry;
	ID2D1PathGeometry* mp_fillPathGeometry;

public:
	Win32PlotSeries1DImpl(Graphics2D* p_graphics, Color color);
	~Win32PlotSeries1DImpl();

public:
	void onUpdate(std::vector<Math::Point2D>* p_points) override;

	void onPaint(Math::Rect& availableRect, bool fillArea) override;

	void setColor(Color color) override;

private:
	void initGraphicsResources();
};