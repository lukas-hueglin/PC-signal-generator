#include "Gui.h"
#include "Widgets/GridLayout.h"

GridLayout::GridLayout(Window* p_parent, int rows, int cols) : Layout(p_parent), m_rows(rows), m_cols(cols) {
	
	// calculate size of array
	m_size = m_rows * m_cols;

	// create arrays
	ma_frames = new Frame*[m_size]();
	ma_rowWeights = new float[m_rows];
	ma_colWeights = new float[m_cols];

	// fill array with 1
	std::fill(ma_rowWeights, ma_rowWeights + m_rows, 1.0f);
	std::fill(ma_colWeights, ma_colWeights + m_cols, 1.0f);
}

GridLayout::~GridLayout() {

	delete[] ma_frames;
	delete[] ma_colWeights;
	delete[] ma_rowWeights;
}

void GridLayout::onPaint() {

	// call parent function
	Layout::onPaint();

	// iterate over all frames
	for (int i = 0; i < m_size; ++i) {

		if (ma_frames[i] != nullptr) {
			ma_frames[i]->onPaint();
		}
	}

	// call frame paint function
	Frame::onPaint();
}

void GridLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// calculate sum of weights
	float rowWeights = 0;
	float colWeights = 0;

	for (int r = 0; r < m_rows; ++r) {

		rowWeights += ma_rowWeights[r];
	}

	for (int c = 0; c < m_cols; ++c) {

		colWeights += ma_colWeights[c];
	}

	// calculate width and height per weight
	float heightPerWeight = m_contentRect.getHeight() / rowWeights;
	float widthPerWeight = m_contentRect.getWidth() / colWeights;

	// calculate width and height for each row and column
	float* height = new float[m_rows]();
	float* width = new float[m_cols]();

	// iterate over all rows
	for (int r = 0; r < m_rows; ++r) {

		// find maximum height
		float max_height = 0.0f;

		for (int c = 0; c < m_cols; ++c) {

			// calculate index
			int i = r * m_cols + c;

			if (ma_frames[i] != nullptr) {
				max_height = max(max_height, ma_frames[i]->getMinSize().height());
			}
		}

		// set height
		height[r] = max(max_height, heightPerWeight * ma_rowWeights[r]);
	}

	// iterate over all columns
	for (int c = 0; c < m_cols; ++c) {

		// find maximum width
		float max_width = 0.0f;

		for (int r = 0; r < m_rows; ++r) {

			// calculate index
			int i = r * m_cols + c;

			if (ma_frames[i] != nullptr) {
				max_width = max(max_width, ma_frames[i]->getMinSize().width());
			}
		}

		// set width
		width[c] = max(max_width, widthPerWeight * ma_colWeights[c]);
	}

	// calculate origin point
	Math::Point2D origin = m_contentRect.topLeft();

	// iterate over all frames and call on Resize
	for (int r = 0; r < m_rows; ++r) {
		for (int c = 0; c < m_cols; ++c) {

			// calculate index
			int i = r * m_cols + c;

			if (ma_frames[i] != nullptr) {

				Math::Point2D bottomRight = origin + Math::Point2D(width[c], height[r]);
				ma_frames[i]->onResize(Math::Rect(origin, bottomRight));
			}

			// add offset
			origin.x() += width[c];
		}

		// add offset
		origin.x() = m_contentRect.left();
		origin.y() += height[r];
	}

	// delete arrays
	delete[] height;
	delete[] width;
}

void GridLayout::onTick(float deltaTime) {

	// iterate over all frames
	for (int i = 0; i < m_size; ++i) {

		if (ma_frames[i] != nullptr) {
			if (ma_frames[i]->isImmediateMode())
				ma_frames[i]->onTick(deltaTime);
			if (ma_frames[i]->hasRequestedRedraw())
				ma_frames[i]->onPaint();
		}
	}
}

void GridLayout::onMouseHover(Math::Point2D point) {

	// iterate over all frames
	for (int i = 0; i < m_size; ++i) {

		if (ma_frames[i] != nullptr) {

			if (Math::pointInRect(ma_frames[i]->getHitbox(), point)) {

				// check if mouse was already hovering
				if (ma_frames[i] != m_mouseHoverFrame) {
					ma_frames[i]->onMouseEnter();
					m_mouseHoverFrame = ma_frames[i];
				}

				ma_frames[i]->onMouseHover(point);
			}
			// check if mouse is registered as hovering
			else if (ma_frames[i] == m_mouseHoverFrame) {
				ma_frames[i]->onMouseLeave();
				m_mouseHoverFrame = nullptr;
			}
		}
	}
}

void GridLayout::addFrame(Frame* p_frame, int row, int col) {

	if (row < m_rows && col < m_cols) {

		// calculate index
		int i = row * m_cols + col;

		ma_frames[i] = p_frame;
	}
}

void GridLayout::removeFrame(Frame* p_frame) {

	for (int i = 0; i < m_size; ++i) {
		
		if (ma_frames[i] == p_frame) {

			// clear entry in array
			ma_frames[i] == nullptr;
		}
	}
}

void GridLayout::setRowWeight(float weight, int row) {

	if (row < m_rows) {
		ma_rowWeights[row] = weight;
	}
}

void GridLayout::setColumnWeight(float weight, int col) {

	if (col < m_cols) {
		ma_colWeights[col] = weight;
	}
}

void GridLayout::calcMinSize() {

	// create arrays for storing the max height/width of each row/column
	float* max_height = new float[m_rows]();
	float* max_width = new float[m_cols]();

	// iterate over all frames
	for (int i = 0; i < m_size; ++i) {

		if (ma_frames[i] != nullptr) {

			// calculate row and column
			int r = i / m_cols;
			int c = i % m_cols;

			max_height[r] = max(max_height[r], ma_frames[i]->getMinSize().height());
			max_width[c] = max(max_height[c], ma_frames[i]->getMinSize().width());
		}
	}

	// sum up width and height
	float width = 0;
	float height = 0;

	for (int c = 0; c < m_cols; ++c) {
		width += max_width[c];
	}

	for (int r = 0; r < m_rows; ++r) {
		height += max_height[r];
	}

	// delete arrays
	delete[] max_height;
	delete[] max_width;

	m_minSize = Math::Size(width + 2*(m_padding + m_margin), height + 2 * (m_padding + m_margin));
}
