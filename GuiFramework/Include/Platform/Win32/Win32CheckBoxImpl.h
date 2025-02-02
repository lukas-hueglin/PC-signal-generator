#pragma once
#include "Widgets/ACheckBoxImpl.h"

class GUI_API Win32CheckBoxImpl : public ACheckBoxImpl {

private:
	Math::Rect m_textRect;
	Math::Rect m_boxRect;

	ID2D1SolidColorBrush* mp_textBrush;
	IDWriteTextFormat* mp_textFormat;

	ID2D1SolidColorBrush* mp_edgeBrush;
	ID2D1SolidColorBrush* mp_fillBrush;

	ID2D1PathGeometry* mp_pathGeometry;

public:
	Win32CheckBoxImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32CheckBoxImpl();

public:
	void onResize(Math::Rect textRect, Math::Rect boxRect) override;
	void onPaint(std::wstring text, WidgetState widgetState) override;

private:
	void initGraphicsResources();
};