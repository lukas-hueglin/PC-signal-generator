#pragma once
#include "Core/Application.h"
#include "Core/MainWindow.h"

#include "Widgets/LinearLayout.h"
#include "Widgets/GridLayout.h"
#include "Widgets/Plot.h"
#include "Widgets/GroupBox.h"
#include "Widgets/Label.h"
#include "Widgets/ComboBox.h"
#include "Widgets/Slider.h"

#include "Functional.h"

class App : public Application {

private:
	Functional* mp_functional;

	MainWindow* mp_window;

	Plot* mp_sigGenPlot;
	Plot* mp_oscPlot;
	Plot* mp_bodeMagnitude;
	Plot* mp_bodePhase;

	LinearLayout* mp_mainLayout;
	LinearLayout* mp_parameterLayout;
	GridLayout* mp_plotLayout;

	GroupBox* mp_sigGenGroup;
	GroupBox* mp_oscGroup;
	GroupBox* mp_freqResponseGroup;

	GridLayout* mp_sigGenLayout;
	GridLayout* mp_oscLayout;
	GridLayout* mp_freqResponseLayout;

	Label* mp_waveformLabel;
	ComboBox* mp_waveformComboBox;

	Label* mp_frequencyLabel;
	Slider<float>* mp_frequencySlider;

	Label* mp_amplitudeLabel;
	Slider<float>* mp_amplitudeSlider;

	Label* mp_dutyCycleLabel;
	Slider<int>* mp_dutyCycleSlider;

public:
	App(int argc, char** argv);
	~App();

private:
	void initUI() override;

	std::wstring getApplicationName();
};