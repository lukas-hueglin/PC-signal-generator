#include "Gui.h"
#include "Core/IWindow.h"

#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"

#include "Widgets/Layout.h"
#include "Widgets/DropDown.h"

#include "Style/Style.h"

// define all types that should be able to be created
template MainWindow* IWindow::create(std::wstring title);

IWindow::IWindow() : mp_graphics(nullptr), mp_layout(nullptr), m_rect(Math::Rect(0.f, 0.f, 0.f, 0.f)), m_layoutMouseHover(false), m_dropDownMouseHover(false) { }

void IWindow::setLayout(Layout* p_layout) {

	mp_layout = p_layout;
	mp_layout->onResize(m_rect);
}

void IWindow::registerDropDown(DropDown* p_dropDown) {

	// remove old dropdown
	unregisterDropDown();

	// add new dropdown
	mp_dropDown = p_dropDown;
}

Graphics2D* IWindow::getGraphics() {

	return mp_graphics;
}

void IWindow::onTick(float deltaTime) {

	// begin painting
	mp_graphics->beginPaint();

	// update layout
	if (mp_layout != nullptr) {
		mp_layout->onTick(deltaTime);
	}

	// draw dropdown
	if (mp_dropDown != nullptr) {
		mp_dropDown->onPaint();
	}

	// end painting
	mp_graphics->endPaint();
}

void IWindow::onBegin() {

	mp_graphics->createGraphicsAssets();

	// redraw all
	onResize(m_rect);
	onPaint();
}


void IWindow::onPaint() {

	// begin painting
	mp_graphics->beginPaint();

	// draw layout
	if (mp_layout != nullptr) {
		mp_layout->onPaint();
	}

	// draw dropdown
	if (mp_dropDown != nullptr) {
		mp_dropDown->onPaint();
	}

	// end painting
	mp_graphics->endPaint();
}

void IWindow::onDestroy() {

	mp_graphics->discardGraphicsAssets();
}

void IWindow::onResize(Math::Rect rect) {

	// update rect
	m_rect = rect;

	// resize canvas on graphics object
	mp_graphics->resizeCanvas();

	// resize layout
	if (mp_layout != nullptr) {
		mp_layout->onResize(m_rect);
	}

	// delete dropdown if it exists
	unregisterDropDown();
}

void IWindow::onMouseMove(Math::Point2D point) {

	// check if mouse hovers over dropdown
	if (mp_dropDown != nullptr && Math::pointInRect(mp_dropDown->getHitbox(), point)) {

		if (Math::pointInRect(mp_dropDown->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_dropDownMouseHover) {
				mp_dropDown->onMouseEnter();
				m_dropDownMouseHover = true;
				m_layoutMouseHover = false;
			}

			mp_dropDown->onMouseHover(point);
			return;
		}
		// check if mouse is registered as hovering
		else if (m_dropDownMouseHover) {
			mp_dropDown->onMouseLeave();
			m_dropDownMouseHover = false;
		}
	}

	// check if a layout exists
	if (mp_layout != nullptr) {

		if (Math::pointInRect(mp_layout->getHitbox(), point)) {

			// check if mouse was already hovering
			if (!m_layoutMouseHover) {
				mp_layout->onMouseEnter();
				m_layoutMouseHover = true;
				m_dropDownMouseHover = false;
			}

			mp_layout->onMouseHover(point);
		}
		// check if mouse is registered as hovering
		else if (m_layoutMouseHover) {
			mp_layout->onMouseLeave();
			m_layoutMouseHover = false;
		}
	}
}

void IWindow::onMouseDown(bool doubleClk, Math::Point2D point) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hover over dropdown
		if (mp_dropDown != nullptr && Math::pointInRect(mp_dropDown->getHitbox(), point)) {
			mp_dropDown->onMouseDown(doubleClk, point);
		}

		// check if mouse hovers over layout
		else if (m_layoutMouseHover) {

			// delete dropdown if it exists
			unregisterDropDown();

			mp_layout->onMouseDown(doubleClk, point);
		}
	}
}

void IWindow::onMouseRelease(Math::Point2D point) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over dropdown
		if (m_dropDownMouseHover) {
			mp_dropDown->onMouseRelease(point);
		}

		// check if mouse hovers over layout
		else if (m_layoutMouseHover) {
			mp_layout->onMouseRelease(point);
		}
	}
}

void IWindow::onMouseScroll(bool up, bool shift, bool ctr) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onMouseScroll(up, shift, ctr);
		}
	}
}

void IWindow::onKeyDown(Key key) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}
}

void IWindow::onKeyDown(char key) {

	// check if a layout exists
	if (mp_layout != nullptr) {

		// check if mouse hovers over layout
		if (m_layoutMouseHover) {
			mp_layout->onKeyDown(key);
		}
	}
}

void IWindow::unregisterDropDown() {

	if (mp_dropDown != nullptr) {
		delete mp_dropDown;
		mp_dropDown = nullptr;

		// repaint all
		onPaint();
	}
}


template<class DERIVED_TYPE>
DERIVED_TYPE* IWindow::create(std::wstring title) {

	// create and initialize window
	DERIVED_TYPE* p_window = new DERIVED_TYPE;
	((IWindow*)p_window)->initialize(title);

	return p_window;
}
