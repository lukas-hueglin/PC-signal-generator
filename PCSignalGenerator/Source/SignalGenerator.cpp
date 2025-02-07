#include "Gui.h"
#include "SignalGenerator.h"
#include "Common/Reflection/Internal.h"

#include <numbers>
#include <assert.h>

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

SignalGenerator::SignalGenerator() : m_output(false), m_waveformType(0), m_phase(0.0f) {

	// add members to reflection
	ADD_FIELD(int, m_waveformType);
	ADD_FIELD(float, m_frequency);
	ADD_FIELD(float, m_amplitude);
	ADD_FIELD(int, m_dutyCycle);

	// initialize audio devices
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

	// create enumerator
	IMMDeviceEnumerator* p_enumerator;

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator,
		NULL,
		CLSCTX_ALL,
		IID_IMMDeviceEnumerator,
		(void**)&p_enumerator
	);
	assert(SUCCEEDED(hr));

	// create audio device
	hr = p_enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &mp_audioDevice);
	assert(SUCCEEDED(hr));

	hr = mp_audioDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&mp_audioClient);
	assert(SUCCEEDED(hr));

	// release enumerator
	hr = p_enumerator->Release();
	assert(SUCCEEDED(hr));

	// get audio format
	hr = mp_audioClient->GetMixFormat(&mp_format);
	assert(SUCCEEDED(hr));

	// initialize audio client
	hr = mp_audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SEC, 0, mp_format, NULL);
	assert(SUCCEEDED(hr));

	// create render client
	hr = mp_audioClient->GetService(IID_IAudioRenderClient, (void**)&mp_audioRenderClient);
	assert(SUCCEEDED(hr));

	// get buffer size
	hr = mp_audioClient->GetBufferSize(&m_bufferSize);
	assert(SUCCEEDED(hr));


	// create buffer
	byte* p_buffer;

	// get all available buffer space
	hr = mp_audioRenderClient->GetBuffer(m_bufferSize, &p_buffer);
	assert(SUCCEEDED(hr));

	// fill buffer
	fillWaveformBuffer(p_buffer, m_bufferSize);

	// write buffer
	hr = mp_audioRenderClient->ReleaseBuffer(m_bufferSize, 0);
	assert(SUCCEEDED(hr));
}

SignalGenerator::~SignalGenerator() {

	mp_audioClient->Stop();

	mp_audioRenderClient->Release();
	mp_audioClient->Release();
	mp_audioDevice->Release();

	CoUninitialize();
}

void SignalGenerator::enableOutput(bool output) {

	m_output = output;

	// start audio
	HRESULT hr;
	if (m_output) {
		hr = mp_audioClient->Start();
		assert(SUCCEEDED(hr));
	}
	else {
		hr = mp_audioClient->Stop();
		assert(SUCCEEDED(hr));
	}
}

void SignalGenerator::setWaveformType(int waveformType) {

	m_waveformType = waveformType;
}

void SignalGenerator::setFrequency(float frequency) {

	m_frequency = frequency;
}

void SignalGenerator::setAmplitude(float amplitude) {

	m_amplitude = amplitude;
}

void SignalGenerator::setDutyCycle(int dutyCycle) {

	m_dutyCycle = dutyCycle;
}

bool SignalGenerator::getOutput() {

	return m_output;
}

int SignalGenerator::getWaveformType()
{
	return m_waveformType;
}

float SignalGenerator::getFrequency() {

	return m_frequency;
}

float SignalGenerator::getAmplitude() {

	return m_amplitude;
}

int SignalGenerator::getDutyCycle() {

	return m_dutyCycle;
}


void SignalGenerator::onTick(float deltaTime) {

	// create hresult
	HRESULT hr;

	unsigned int padding;
	unsigned int availableFrames;

	// get padding size
	hr = mp_audioClient->GetCurrentPadding(&padding);
	assert(SUCCEEDED(hr));
	
	// calculate available space
	availableFrames = m_bufferSize - padding;

	// if one quarters of buffer is used up, refill
	if (availableFrames > 0.1 * m_bufferSize) {

		// create buffer
		BYTE* p_buffer;

		// get all available buffer space
		hr = mp_audioRenderClient->GetBuffer(availableFrames, &p_buffer);
		assert(SUCCEEDED(hr));

		// fill buffer
		fillWaveformBuffer(p_buffer, availableFrames);
		DEBUG_PRINTLN("REFRESH!")

		// write buffer
		hr = mp_audioRenderClient->ReleaseBuffer(availableFrames, 0);
		assert(SUCCEEDED(hr));
	}
}

void SignalGenerator::fillWaveformBuffer(byte* p_buffer, unsigned int nSamples) {

	// cast to float
	float* p_floatBuffer = (float*)p_buffer;

	switch (m_waveformType) {

	case 0: // sine waveform
	{
		// calculate radians per sample
		float radPerSample = 2 * std::numbers::pi * m_frequency / mp_format->nSamplesPerSec;

		for (int i = 0; i < nSamples; ++i) {

			// calculate value
			float value = m_amplitude * sin(radPerSample * i + m_phase);

			for (int c = 0; c < mp_format->nChannels; ++c) {
				p_floatBuffer[mp_format->nChannels * i + c] = value;
			}
		}

		// calculate new phase
		m_phase += radPerSample * nSamples;
		int turns = m_phase / (2 * std::numbers::pi);
		m_phase -= turns * 2 * std::numbers::pi;

		return;
	}
	case 1: // rectangular waveform

		return;

	case 2: // triangular waveform

		return;

	case 3: // sawtooth waveform

		return;
	}
}
