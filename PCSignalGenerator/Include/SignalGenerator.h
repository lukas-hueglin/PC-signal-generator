#pragma once
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "Core/IFunctional.h"
#include "Common/Signal.h"


#define REFTIMES_PER_SEC 10000000


class SignalGenerator : public IFunctional {

private:
	IMMDevice* mp_audioDevice;
	IAudioClient* mp_audioClient;
	IAudioRenderClient* mp_audioRenderClient;

	WAVEFORMATEX* mp_format;
	unsigned int m_bufferSize;
	float m_phase;

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

	bool getOutput();
	int getWaveformType();
	float getFrequency();
	float getAmplitude();
	int getDutyCycle();

private:
	void onTick(float deltaTime);

	void fillWaveformBuffer(byte* p_buffer, unsigned int nSamples);

	IMPLEMENT_LOADSAVE(SignalGenerator);
};