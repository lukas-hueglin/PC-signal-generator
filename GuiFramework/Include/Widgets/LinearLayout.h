#pragma once
#include "Widgets/Layout.h"
#include <vector>

class GUI_API LinearLayout : public Layout {

protected:
	std::vector<Frame*> m_frames;
	std::vector<float> m_weights;

private:
	Orientation m_orientation;

public:
	LinearLayout(Window* p_parent, Orientation orientation);

public:
	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
	void onTick(float deltaTime) override;

	void onMouseHover(Math::Point2D point) override;

	void addFrame(Frame* p_frame, float weight = 1.0f);
	void removeFrame(Frame* p_frame);

private:
	void calcMinSize() override;
};