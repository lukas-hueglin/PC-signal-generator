#pragma once
#include "Widgets/AButtonImpl.h"

class GUI_API Win32ButtonImpl : public AButtonImpl {

private:
	ID2D1SolidColorBrush* mp_edgeBrush;
	ID2D1SolidColorBrush* mp_fillBrush;

	ID2D1PathGeometry* mp_pathGeometry;

public:
	Win32ButtonImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32ButtonImpl();

public:
	void onPaint(WidgetState widgetState) override;
	void onResize(Math::Rect hitboxRect) override;

private:
	void initGraphicsResources();
};