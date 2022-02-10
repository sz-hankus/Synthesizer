#ifndef SOUNDLIB_H
#define SOUNDLIB_H

#include <SFML/Audio.hpp>
#include <math.h>
#include <iostream>

const uint SAMPLES = 44100;
const uint IDEAL_SAMPLE_RATE = 44100;
const uint DEFAULT_AMPLITUDE_SCALING = 3000; // loudness scaling factor
const double TWO_PI = 6.28318530718;

sf::SoundBuffer getFilledBuffer(double frequency, std::string waveType, uint amplitude_scaling = DEFAULT_AMPLITUDE_SCALING);

void calculateNoteFrequencies(double* array, int amount, uint octave);

#endif