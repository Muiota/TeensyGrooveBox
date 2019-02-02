#include "Equalizer.h"

ChannelSettings* settings;

bool _isLog = false;
bool _qFielddisabled = false;
bool _gainFielddisabled = false;

void EqualizerClass::handle()
{
	if (!Engine.isValidScreen)
	{
		recalc();
		Engine.isValidScreen = true;
	}
}

void EqualizerClass::onShow()
{
	Engine.assignDefaultButtons();
	settings = &Engine.songSettings.mixer.looper;

	DisplayCore.drawEncoderTitle(0, "FC (Hz)", true);
	DisplayCore.drawEncoderTitle(1, "Slope", true);
	DisplayCore.drawEncoderTitle(2, "Gain (dB)", true);
	HardwareCore.setEncoderParam(0, setFc, "FC (Hz)", 50, 20000, 50, settings->eqFc); //20-20000
	//HardwareCore.setEncoderParam(1, setQ, "Q", 100, 10000, 100, settings->eqQ);
	HardwareCore.setEncoderParam(1, setQ, "Slope", 0, 2, 0.1, settings->eqSlope);
	HardwareCore.setEncoderParam(2, setGain, "Gain (dB)", -30, 30, 1, settings->eqGain);
}

void EqualizerClass::setFc(int encoder, int value)
{
	settings->eqFc = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, settings->eqFc, 20000);
	recalc();
}

void EqualizerClass::setQ(int encoder, int value)
{
	settings->eqQ = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, settings->eqQ, 1000);
	recalc();
}

void EqualizerClass::setSlope(int encoder, int value)
{
	settings->eqSlope = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, settings->eqSlope, 2);
	recalc();
}

void EqualizerClass::setGain(int encoder, int value)
{
	settings->eqGain = static_cast<float>(value / 100);
	DisplayCore.drawEncoder(encoder, settings->eqGain, 30, true);
	recalc();
}


void EqualizerClass::recalc()
{
	int coef[5];
	AudioFilterBiquad::calcBiquad(settings->eqType, settings->eqFc, settings->eqGain, settings->eqSlope, coef);
	
	/*DisplayCore.drawText(settings->eqFc, 150, 120, true);
	DisplayCore.drawText(settings->eqGain, 150, 140, true);
	DisplayCore.drawText(settings->eqSlope, 150, 160, true);
	DisplayCore.drawText(settings->eqQ, 150, 180, true);*/
	
	
	
	switch (settings->eqType) {
	case LOWPASS:
	case HIGHPASS:
	case BANDPASS:
	case NOTCH:
		_qFielddisabled = false;
		_gainFielddisabled = true;
		break;
	case HIGH_SHELF:
	case LOW_SHELF:
		_qFielddisabled = true;
		_gainFielddisabled = false;
		break;
	default:
		_qFielddisabled = true;
		_gainFielddisabled = true;
		break;
	}


	
	

	double a0 = coef[0] / 1073741824.0;
	double a1 = coef[1] / 1073741824.0;
	double a2 = coef[2] / 1073741824.0;
	double b1 = coef[3] / 1073741824.0;
	double b2 = coef[4] / 1073741824.0;

/*	DisplayCore.drawText(a0, 10, 120, true);
	DisplayCore.drawText(a1, 10, 140, true);
	DisplayCore.drawText(a2, 10, 160, true);
	DisplayCore.drawText(b1, 10, 180, true);
	DisplayCore.drawText(b2, 10, 200, true); */
	
	double pi = 3.141592654;
	double minVal = 0;
	double maxVal = 0;
	double ymin;
	double ymax;
	uint16_t len = 280;	
	double magPlot[280];
	for (uint16_t idx = 0; idx < len; idx++) {
		double w;
		if (!_isLog)
		{
			w = idx / (static_cast<double>(len) - 1) * pi;	// 0 to pi, linear scale
		}
		else
		{
		//	w = Math.exp(Math.log(1 / 0.001) * idx / (len - 1)) * 0.001 * pi;	// 0.001 to 1, times pi, log scale
		}

		double phi = pow(sin(w / 2), 2);
		double y = log(pow(a0 + a1 + a2, 2) - 4 * (a0*a1 + 4 * a0*a2 + a1*a2)*phi + 16 * a0*a2*phi*phi) -
			log(pow(1 + b1 + b2, 2) - 4 * (b1 + 4 * b2 + b1*b2)*phi + 16 * b2*phi*phi);
		y = y * 10 / 2.302585092994046;
		if (y < -99)
		{
			y = -99;
		}

			if (!_isLog)
			{
				magPlot[idx] = y;
			
				//magPlot.push([idx / (len - 1) * Fs / 2, y]);
			}
			else
			{
				//magPlot.push([idx / (len - 1) / 2, y]);
			}

		if (idx == 0)
			minVal = maxVal = y;
		else if (y < minVal)
			minVal = y;
		else if (y > maxVal)
			maxVal = y;
	}

	// configure y-axis
	switch (settings->eqType) {
	default:
	case LOWPASS:
	case HIGHPASS:
	case BANDPASS:
	case NOTCH:
		ymin = -100;
		ymax = 0;
		if (maxVal > ymax)
			ymax = maxVal;
		break;
	
	case LOW_SHELF:
	case HIGH_SHELF:
		ymin = -10;
		ymax = 10;
		if (maxVal > ymax)
			ymax = maxVal;
		if (minVal < ymin)
			ymin = minVal;
		break;
		/*case "one-pole lp":
	case "one-pole hp":
		ymin = -40;
		ymax = 0;
		break;*/
	}
	/*
	DisplayCore.drawText(ymin, 10, 120, true);
	DisplayCore.drawText(ymax, 10, 140, true);
	DisplayCore.drawText(magPlot[0], 10, 160, true);
	DisplayCore.drawText(magPlot[150], 10, 180, true);
	DisplayCore.drawText(magPlot[300], 10, 200, true); */
	DisplayCore.drawEqChart(10, 124, ymin, ymax, len, magPlot);
	AudioCore.setLooperEqBiquad(coef);
	//calcBiquad(type, Fc, Fs, Q, gain);
}


	

