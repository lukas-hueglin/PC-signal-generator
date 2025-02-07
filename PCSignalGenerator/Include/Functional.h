#pragma once
#include "Core/IFunctional.h"
#include "Common/Signal.h"

#include <string>

class Functional : public IFunctional {

private:
	float m_freqIncrement;

	float m_frequency;

	int m_bufferSize;
	float m_buffer[100];

	float m_timeSinceUpdate;

public:
	Functional();

public:
	int getPlotSize();
	float* getPlotData();

	float getFreqIncrement();
	void setFreqIncrement(float freqIncrement);

	Signal<> onUpdatePlot;

private:
	void onTick(float deltaTime);

	IMPLEMENT_LOADSAVE(Functional);

};