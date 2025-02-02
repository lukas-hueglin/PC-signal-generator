#include "Gui.h"
#include "Widgets/LinearLayout.h"

LinearLayout::LinearLayout(Window* p_parent, Orientation orientation) : Layout(p_parent), m_orientation(orientation) { }

void LinearLayout::onPaint() {

	// call parent function
	Layout::onPaint();

	// iterate over all frames
	for (Frame* w : m_frames) {
		w->onPaint();
	}

	// call frame paint function
	Frame::onPaint();
}

void LinearLayout::onResize(Math::Rect availableRect) {

	// call parent function
	Layout::onResize(availableRect);

	// calculate the sum of all weights
	float sumExpandWeights = 0;

	for (int i = 0; i < m_frames.size(); ++i) {

		if (m_frames.at(i)->getFillMode() == FillMode::Expand) {
			sumExpandWeights += m_weights.at(i);
		}
	}

	// iterate over all frames again and set their available space
	Math::Rect minRect(availableRect.getCenter().x() - m_minSize.width() / 2, availableRect.getCenter().x() + m_minSize.width() / 2,
		availableRect.getCenter().y() - m_minSize.height() / 2, availableRect.getCenter().y() + m_minSize.height() / 2);

	Math::Rect avRect = Math::maxRect(availableRect, minRect);

	// calculate space required for shrink widgets and space left for expanding widgets
	float spaceLeft = availableRect.getSize()[m_orientation] - m_minSize[m_orientation];

	// calculate integral sizes
	float expandSpan;
	float frameSpan;

	// check if expanding widgets are present
	if (sumExpandWeights == 0) {

		// if not align the content
		avRect.topLeft()[m_orientation] += spaceLeft / 2 * (int)getJustification(m_alignment, m_orientation);
	}
	else {

		// if there are calculate the size of each one.
		expandSpan = spaceLeft / sumExpandWeights;
	}

	// iterate over all frames and set their sizes
	for (int i = 0; i < m_frames.size(); ++i) {

		frameSpan = m_frames.at(i)->getMinSize()[m_orientation];

		if (m_frames.at(i)->getFillMode() == FillMode::Expand)
			 frameSpan += expandSpan * m_weights.at(i);
			

		// resize avRect
		avRect.bottomRight()[m_orientation] = avRect.topLeft()[m_orientation] + frameSpan;

		// resize frame
		m_frames.at(i)->onResize(avRect);

		// set left for next one
		avRect.topLeft()[m_orientation] = avRect.bottomRight()[m_orientation];
	}
	
}

void LinearLayout::onTick(float deltaTime) {

	// iterate over all frames
	for (Frame* w : m_frames) {
		if (w->isImmediateMode())
			w->onTick(deltaTime);
		if (w->hasRequestedRedraw())
			w->onPaint();
	}
}

void LinearLayout::onMouseHover(Math::Point2D point) {

	// iterate over all frames
	for (Frame* w : m_frames) {

		if (Math::pointInRect(w->getHitbox(), point)) {

			// check if mouse was already hovering
			if (w != m_mouseHoverFrame) {
				w->onMouseEnter();
				m_mouseHoverFrame = w;
			}

			w->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (w == m_mouseHoverFrame) {
			w->onMouseLeave();
			m_mouseHoverFrame = nullptr;
		}
	}
}

void LinearLayout::addFrame(Frame* p_frame, float weight) {

	m_frames.push_back(p_frame);
	m_weights.push_back(weight);

	onResize(m_usedRect);
}

void LinearLayout::removeFrame(Frame* p_frame) {

	// find index
	int index = std::distance(m_frames.begin(), std::find(m_frames.begin(), m_frames.end(), p_frame));

	m_frames.erase(m_frames.begin() + index);
	m_weights.erase(m_weights.begin() + index);
}

void LinearLayout::calcMinSize() {

	float width = 0.0f;
	float height = 0.0f;

	if (m_orientation == Orientation::Horizontal) {

		for (int i = 0; i < m_frames.size(); ++i) {

			width += m_frames.at(i)->getMinSize().width();
			height = max(height, m_frames.at(i)->getMinSize().height());
		}
	}
	else {

		for (int i = 0; i < m_frames.size(); ++i) {

			width = max(width, m_frames.at(i)->getMinSize().width());
			height += m_frames.at(i)->getMinSize().height();
		}
	}

	m_minSize = Math::Size(width, height);
}