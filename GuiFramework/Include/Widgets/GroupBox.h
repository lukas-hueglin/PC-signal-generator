#pragma once
#include "Widgets/Layout.h"
#include "Widgets/Label.h"
#include <vector>

class GUI_API GroupBox : public Layout {

private:
	Frame* mp_frame;
	Label* mp_label;

	Math::Rect m_childRect;

	float m_indent;

public:
	GroupBox(Window* p_parent, Frame* p_frame, std::wstring title);
	~GroupBox();

public:
	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
	void onTick(float deltaTime) override;

	void onMouseHover(Math::Point2D point) override;

	void setFrame(Frame* p_frame);

private:
	void calcMinSize() override;
};