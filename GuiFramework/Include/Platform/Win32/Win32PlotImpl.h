#pragma once
#include "Widgets/APlotImpl.h"

class GUI_API Win32PlotImpl : public APlotImpl {

private:
	ID2D1SolidColorBrush* mp_edgeBrush;
	ID2D1SolidColorBrush* mp_fillBrush;

	ID2D1SolidColorBrush* mp_axisBrush;
	ID2D1SolidColorBrush* mp_textBrush;

	IDWriteTextFormat* mp_xTextFormat;
	IDWriteTextFormat* mp_yTextFormat;

	ID2D1PathGeometry* mp_pathGeometry;	

public:
	Win32PlotImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32PlotImpl();

public:
	void onResize(Math::Rect plotRect, Math::Rect legendRect);

	void onPaintAxis(std::wstring xAxisText, std::wstring yAxisText);

	void onPaintHorizontalTicks(float value, std::wstring text);
	void onPaintVerticalTicks(float value, std::wstring text);

	//void onPaintLegend(std::vector<std::wstring>* names);

private:
	void drawArrow(Math::Point2D a, Math::Point2D b, float size);

	void initGraphicsResources();
};