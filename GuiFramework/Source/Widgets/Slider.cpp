#include "Gui.h"
#include "Widgets/Slider.h"
#include "Style/Style.h"
#include "Common/WidgetUtils.h"

// define all types of Sliders to be used
template class Slider<float>;
template class Slider<double>;
template class Slider<int>;

template<typename T>
Slider<T>::Slider(Window* p_parent, T value, T min, T max, WidgetStyle style) : TextBox(p_parent, std::to_wstring(value), style), m_value(value), m_min(min), m_max(max), m_sliderImpl(mp_graphics, style) {

	// set requireDoubleClick to true
	m_requireDoubleClk = true;
}

template<typename T>
void Slider<T>::onPaint() {

	// draw background
	m_widgetImpl.onPaint();

	// draw textBox
	WidgetState state = m_mouseDown ? WidgetState::Click : m_mouseHover ? WidgetState::Hover : WidgetState::Normal;
	m_textBoxImpl.onPaint(state);

	// draw cursor
	m_textBoxImpl.onPaintCursor(m_firstCursor + m_prefix.size(), m_lastCursor + m_prefix.size(), m_dragFirstCursor, m_edit && (m_animCycle < 0.5));

	// draw slider
	m_sliderImpl.onPaint(m_sliderRect, state);

	// call parent function
	Frame::onPaint();
}

template<typename T>
void Slider<T>::onResize(Math::Rect availableRect) {
	
	TextBox::onResize(availableRect);

	m_sliderImpl.onResize(m_hitboxRect);

	// calculate new slider rectangle
	float ratio = (m_value - m_min) / (float)(m_max - m_min);

	m_sliderRect = m_hitboxRect;
	m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
}

template<typename T>
void Slider<T>::onMouseHover(Math::Point2D point) {

	// call parent function
	TextBox::onMouseHover(point);

	if (m_mouseDown && !m_edit) {

		// calculate new value
		float ratio = (point.x() - m_hitboxRect.left()) / m_hitboxRect.getWidth();

		if (std::is_same<T, int>::value) {
			m_value = round(m_min + ratio * (m_max - m_min));
		}
		else {
			m_value = m_min + ratio * (m_max - m_min);
		}

		// calculate slider rectangle (because of rounding it isn't done directly)
		ratio = (m_value - m_min) / (float)(m_max - m_min);
		m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;
		
		// update the text
		m_text = floatToString(m_value);

		EMIT(onValueChanged, m_value)

		updateText();
		requestRedraw();
	}
}

template<typename T>
bool Slider<T>::filterInput(char key) {

	return key == 0x2D || (0x30 <= key && key <= 0x39) || (key == 0x2E && !std::is_same<T, int>::value);
}


template<typename T>
void Slider<T>::disableEditMode(bool backup) {

	// update m_value
	if (!backup) {
		m_value = std::stof(m_text);
		m_value = max(m_min, min(m_max, m_value));

		EMIT(onValueChanged, m_value)
	}

	// calculate new slider rectangle
	float ratio = (m_value - m_min) / (float)(m_max - m_min);

	m_sliderRect = m_hitboxRect;
	m_sliderRect.right() = m_hitboxRect.left() + m_hitboxRect.getWidth() * ratio;

	// convert m_value to string
	m_text = floatToString(m_value);

	// update text
	updateText();

	m_edit = false;
	disableImmediateMode();
	requestRedraw();
}