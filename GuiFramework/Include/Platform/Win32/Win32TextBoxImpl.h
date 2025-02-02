#pragma once
#include "Widgets/ATextBoxImpl.h"

class GUI_API Win32TextBoxImpl : public ATextBoxImpl {

protected:
	std::wstring m_text;
	Math::Rect m_rect;

	ID2D1SolidColorBrush* mp_edgeBrush;
	ID2D1SolidColorBrush* mp_fillBrush;
	ID2D1SolidColorBrush* mp_textBrush;
	ID2D1SolidColorBrush* mp_textSelectBrush;

	ID2D1PathGeometry* mp_pathGeometry;

	IDWriteTextFormat* mp_textFormat;
	IDWriteTextLayout* mp_textLayout;

public:
	Win32TextBoxImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32TextBoxImpl();

public:
	void onResize(Math::Rect hitboxRect, Math::Rect contentRect) override;
	void onPaint(WidgetState widgetState) override;
	void onPaintCursor(int firstIndex, int lastIndex, bool dragFirstCursor, bool cursor) override;

	void setText(std::wstring text) override;

	int getMousePosition(Math::Point2D point);
	Math::Rect getCursorPosition(int cursor, bool trailing = false);

private:
	virtual void initGraphicsResources();
	void initTextLayout();
};