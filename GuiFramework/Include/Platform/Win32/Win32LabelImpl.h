#pragma once
#include "Widgets/ALabelImpl.h"

class GUI_API Win32LabelImpl : public ALabelImpl {

private:
	Math::Rect m_rect;

	ID2D1SolidColorBrush* mp_textBrush;
	IDWriteTextFormat* mp_textFormat;

public:
	Win32LabelImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32LabelImpl();

public:
	void onPaint(std::wstring text) override;
	void onResize(Math::Rect contentRect) override;

private:
	void initGraphicsResources();
};