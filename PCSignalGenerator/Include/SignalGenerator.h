#pragma once
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "Core/IFunctional.h"
#include "Common/Signal.h"


#define SIGGEN_PLOT_SIZE 1024

class SignalGenerator : public IFunctional {

private:
	IMMDevice* mp_audioDevice;
	IAudioClient* mp_audioClient;
	IAudioRenderClient* mp_audioRenderClient;

	WAVEFORMATEX* mp_format;
	unsigned int m_bufferSize;
	float m_phase;

	float ma_plotData[SIGGEN_PLOT_SIZE];

	bool m_output;
	int m_waveformType;
	float m_frequency;
	float m_amplitude;
	int m_dutyCycle;

public:
	SignalGenerator();
	~SignalGenerator();

public:
	void enableOutput(bool output);
	void setWaveformType(int waveformType);
	void setFrequency(float frequency);
	void setAmplitude(float amplitude);
	void setDutyCycle(int dutyCycle);

	float* getPlotData();
	int getPlotDataSize();
	bool isOutputEnabled();
	int getWaveformType();
	float getFrequency();
	float getAmplitude();
	int getDutyCycle();

public:
	Signal<> onPlotUpdate;

private:
	void onTick(float deltaTime) override;
	void onBegin() override;
	void onClose() override;

	void fillWaveformBuffer(byte* p_buffer, unsigned int nSamples);
	void calculatePlotWaveform();

	IMPLEMENT_LOADSAVE(SignalGenerator);
};