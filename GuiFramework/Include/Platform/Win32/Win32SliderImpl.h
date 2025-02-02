#pragma once
#include "Widgets/ASliderImpl.h"

class GUI_API Win32SliderImpl : public ASliderImpl {

private:
	ID2D1SolidColorBrush* mp_fillBrush;

	ID2D1PathGeometry* mp_pathGeometry;

public:
	Win32SliderImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32SliderImpl();

public:
	void onPaint(Math::Rect sliderRect, WidgetState widgetState) override;
	void onResize(Math::Rect hitboxRect) override;

private:
	void initGraphicsResources();
};