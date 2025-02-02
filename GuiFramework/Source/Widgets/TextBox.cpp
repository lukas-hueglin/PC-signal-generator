#include "Gui.h"
#include "Widgets/TextBox.h"
#include "Style/Style.h"


TextBox::TextBox(Window* p_parent, std::wstring text, WidgetStyle style) :
	Widget(p_parent, style),

	m_text(text), m_backupText(text),
	
	m_firstCursor(0), m_lastCursor(0),
	
	m_edit(false), m_dragFirstCursor(false), m_animCycle(0), m_requireDoubleClk(false),
	m_prefix(L""), m_suffix(L""),
	m_textBoxImpl(mp_graphics, style) {

	// update text for the textbox implementation
	updateText();
}

void TextBox::onTick(float deltaTime) {

	m_animCycle += deltaTime;

	if (m_animCycle > 1) {
		m_animCycle = 0;
	}
}

void TextBox::onPaint() {

	// draw background
	m_widgetImpl.onPaint();

	// draw textBox
	WidgetState state = m_mouseDown ? WidgetState::Click : m_mouseHover ? WidgetState::Hover : WidgetState::Normal;
	m_textBoxImpl.onPaint(state);
	
	// draw cursor
	m_textBoxImpl.onPaintCursor(m_firstCursor + m_prefix.size(), m_lastCursor + m_prefix.size(), m_dragFirstCursor, m_edit && (m_animCycle < 0.5));

	// call parent function
	Frame::onPaint();
}

void TextBox::onResize(Math::Rect availableRect) {

	// call parent function
	Widget::onResize(availableRect);

	m_textBoxImpl.onResize(m_hitboxRect, m_contentRect);
}

void TextBox::onMouseLeave() {

	// call parent function
	Widget::onMouseLeave();

	disableEditMode(false);
}

void TextBox::onMouseHover(Math::Point2D point) {

	if (m_edit && m_mouseDown) {

		// get cursor position
		int cursor = min(m_textBoxImpl.getMousePosition(point) - m_prefix.size(), m_text.size());

		cursor = min(cursor, m_text.size());

		if (m_dragFirstCursor) {
			if (cursor <= m_lastCursor) {
				m_firstCursor = cursor;
			}
			else {
				m_dragFirstCursor = false;
				m_lastCursor = cursor;
			}
		}
		else {
			if (cursor >= m_firstCursor) {
				m_lastCursor = cursor;
			}
			else {
				m_dragFirstCursor = true;
				m_firstCursor = cursor;
			}
		}
	}
}

void TextBox::onMouseDown(bool doubleClk, Math::Point2D point) {

	// call parent function
	Widget::onMouseDown(doubleClk, point);

	// if it is the first click/double click
	if (!m_edit && (m_requireDoubleClk ? doubleClk : true)) {

		// backup text and enable edit mode
		m_backupText = m_text;
		enableEditMode();
	}

	// if the textbox is already being edited or it is double clicked, when no double click is required
	if (m_edit || (m_requireDoubleClk ? false : doubleClk)) {

		// update cursor position
		m_firstCursor = m_lastCursor = min(m_textBoxImpl.getMousePosition(point) - m_prefix.size(), m_text.size());
	}
	else {

		// else, put the cursor to the clicked position
		m_firstCursor = m_lastCursor = m_text.size();
	}

	// reset the animation cycle
	m_animCycle = 0;
}

void TextBox::onKeyDown(Key key) {

	if (m_edit) {
		switch (key) {

		case Backspace:

			if (m_firstCursor == m_lastCursor) {
				// delete one character
				if (m_firstCursor > 0) {

					m_text.erase(m_firstCursor - 1, 1);
					m_lastCursor = (m_firstCursor -= 1);
				}
			}
			else {
				// delete multiple
				m_text.erase(m_firstCursor, m_lastCursor - m_firstCursor);

				// set them to be equal
				m_lastCursor = m_firstCursor;
			}

			updateText();
			return;

		case Enter:

			disableEditMode(false);
			return;

		case Esc:

			disableEditMode(true);
			return;

		case LeftArrow:

			if (m_firstCursor > 0) {
				// make them the same and decrement them by one
				m_lastCursor = (m_firstCursor -= 1);
			}
			return;

		case RightArrow:

			if (m_lastCursor < m_text.size()) {
				// make them the same and increment them by one
				m_firstCursor = (m_lastCursor += 1);
			}
			return;

		case Delete:

			if (m_firstCursor == m_lastCursor) {
				// delete one character
				if (m_firstCursor < m_text.size()) {
					m_text.erase(m_firstCursor, 1);
				}
			}
			else {
				// delete multiple
				m_text.erase(m_firstCursor, m_lastCursor - m_firstCursor);

				// set them to be equal
				m_lastCursor = m_firstCursor;
			}

			updateText();
			return;
		}
	}
}

void TextBox::onKeyDown(char key) {

	// check if key is allowed
	if (filterInput(key)) {

		// delete characters if cursors don't match
		if (m_firstCursor != m_lastCursor) {
		
			// delete characters in between
			m_text.erase(m_firstCursor, m_lastCursor - m_firstCursor);

			// set them to be equal
			m_lastCursor = m_firstCursor;
		}

		// insert character
		m_text.insert(m_firstCursor, std::wstring(1, key));
		m_firstCursor = (m_lastCursor += 1);

		updateText();
	}
}

void TextBox::setRequireDoubleClick(bool requireDoubleClk) {

	m_requireDoubleClk = requireDoubleClk;
}

void TextBox::setPrefix(std::wstring prefix) {

	m_prefix = prefix;
	updateText(); requestRedraw();
}

void TextBox::setSuffix(std::wstring suffix) {

	m_suffix = suffix;
	updateText(); requestRedraw();
}

void TextBox::enableEditMode() {

	// create backup
	m_backupText = m_text;

	m_edit = true;
	enableImmediateMode();
}

void TextBox::disableEditMode(bool backup) {

	// restore backup
	if (backup) {
		m_text = m_backupText;
		updateText();
	}
	else {
		EMIT(onTextChanged, m_text)
	}

	m_edit = false;
	disableImmediateMode();
	requestRedraw();
}

void TextBox::updateText() {

	m_textBoxImpl.setText(m_prefix + m_text + m_suffix);
}

bool TextBox::filterInput(char key) { return true; }
