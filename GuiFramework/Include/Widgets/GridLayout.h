#pragma once
#include "Widgets/Layout.h"

class GUI_API GridLayout : public Layout {

protected:
	Frame** ma_frames;

	float* ma_colWeights;
	float* ma_rowWeights;

private:
	int m_rows;
	int m_cols;
	int m_size;

public:
	GridLayout(Window* p_parent, int rows, int cols);
	~GridLayout();

public:
	void onPaint() override;
	void onResize(Math::Rect availableRect) override;
	void onTick(float deltaTime) override;

	void onMouseHover(Math::Point2D point) override;

	void addFrame(Frame* p_frame, int row, int col);
	void removeFrame(Frame* p_frame);

	void setRowWeight(float weight, int row);
	void setColumnWeight(float weight, int col);

private:
	void calcMinSize() override;
};