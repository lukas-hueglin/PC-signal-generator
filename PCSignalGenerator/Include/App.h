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
#include "Widgets/Button.h"
#include "Widgets/StateButton.h"
#include "Widgets/CheckBox.h"
#include "Widgets/PlotSeries1D.h"

#include "SignalGenerator.h"
#include "Oscilloscope.h"

class App : public Application {

private:
	SignalGenerator* mp_sigGen;
	Oscilloscope* mp_osc;

	MainWindow* mp_window;

	Plot* mp_sigGenPlot;
	Plot* mp_oscPlot;
	Plot* mp_bode;

	PlotSeries1D* mp_sigGenPlotSeries;
	PlotSeries1D* mp_oscPlotSeries;

	LinearLayout* mp_mainLayout;
	LinearLayout* mp_parameterLayout;
	LinearLayout* mp_vertPlotLayout;
	LinearLayout* mp_horPlotLayout;

	GroupBox* mp_sigGenGroup;
	GroupBox* mp_oscGroup;
	GroupBox* mp_freqResponseGroup;

	GridLayout* mp_sigGenLayout;
	GridLayout* mp_oscLayout;
	GridLayout* mp_freqResponseLayout;

	Label* mp_enableSigGenLabel;
	StateButton* mp_enableSigGenButton;

	Label* mp_waveformLabel;
	ComboBox* mp_waveformComboBox;

	Label* mp_frequencyLabel;
	Slider<float>* mp_frequencySlider;

	Label* mp_amplitudeLabel;
	Slider<float>* mp_amplitudeSlider;

	Label* mp_dutyCycleLabel;
	Slider<int>* mp_dutyCycleSlider;

	Label* mp_enableOscLabel;
	StateButton* mp_enableOscButton;

	Label* mp_aquisitionModeLabel;
	ComboBox* mp_aquisitionModeComboBox;

	Label* mp_triggerLevelLabel;
	Slider<float>* mp_triggerLevelSlider;

public:
	App(int argc, char** argv);
	~App();

private:
	void initUI() override;

	std::wstring getApplicationName();
};