#include "SoundLib.h"

sf::SoundBuffer getFilledBuffer(double frequency, std::string waveType, uint amplitude_scaling) {
	// This is neccessary if we want the sound to loop and be smooth
    double spc = IDEAL_SAMPLE_RATE / frequency; // samples per cycle
	const int adjustedNumberOfSamples = ceil(spc)*ceil(frequency);
	sf::Int16 samples[adjustedNumberOfSamples]; //array of samples

	double increment = frequency/(ceil(spc)*frequency);
	double x = 0.0;

	if (waveType == "Sine") {
		// SINE WAVE
		for (int i = 0; i < adjustedNumberOfSamples; i++) {
			samples[i] = sin(x*TWO_PI) * amplitude_scaling;
			x += increment;
		}
	}
	if (waveType == "Square") {
		// SQUARE WAVE
		for (int i = 0; i < adjustedNumberOfSamples; i++) {
			if( sin(x*TWO_PI) > 0.0)
				samples[i] = 1.0 * amplitude_scaling;
			else
				samples[i] = -1.0 * amplitude_scaling;
			x += increment;
		}
	}
	if (waveType == "Sawtooth") {
		// SAWTOOTH WAVE
		double period = 1.0/frequency;
		for (int i = 0; i < adjustedNumberOfSamples; i++) {
			samples[i] = frequency * fmod(x*period, period) * float(amplitude_scaling);
			x += increment;
		}
	}

	
	sf::SoundBuffer toReturn;
	if (!toReturn.loadFromSamples(samples, adjustedNumberOfSamples, 1, adjustedNumberOfSamples)) {
		std::cerr << "Error loading buffer from samples!" << std::endl;
	}
	return toReturn;
}

void calculateNoteFrequencies(double* array, int amount, uint octave) {
	double C_5 = 440.0 * pow(2.0, 3.0/12.0); //Calculate C5 and then C0 according to Equal temperament tuning
    double C_0 = C_5 * pow(2.0, -5.0); 
    double C_octave = C_0 * pow(2.0, static_cast<double> (octave)); //calculate C note in desired octave

    array[0] = C_octave;
	for (int i = 1; i < amount; i++) {
		array[i] = array[i-1] * pow(2.0, 1.0/12.0);
	}
}
