#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <map>
#include <vector>
#include <algorithm>
#include "RoundedRectangle.h"

/*
    NAMING: keys = graphical keys on the virtual keyboard, buttons = keys on the physical one,
    notes = sounds corresponding to keys.
    Notes, buffers and keys are all arranged in corresponding arrays.
    E.g. m_notes[0] has the buffer m_buffers[0] and the corresponding key is m_keys[0]
*/

const int KB_SIZE = 18; // size of the keyboard (the amount of keys)
const std::vector <std::string> WAVETYPES = {"Sine", "Square", "Sawtooth"}; // allowed wavetypes (s=sine, e=square, z=sawtooth)


class Keyboard {
    
    private:
        sf::Vector2f m_position;
        sf::Vector2f m_dimensions;

        uint m_octave;
        std::string m_waveType;

        sf::SoundBuffer m_buffers[KB_SIZE];
        sf::Sound m_notes[KB_SIZE];
        std::map <int, int> m_buttonToNoteIndex;
        
        RoundedRectangleShape m_keys[KB_SIZE];
        sf::Text m_keyLetters[KB_SIZE];
        sf::Font m_letterFont;

        void initMap();
        void initKeys();

    public:
        Keyboard(sf::Vector2f position, sf::Vector2f dimensions, uint octave = 4, std::string waveType = "Sine");
        ~Keyboard();
        void loadBuffers();

        sf::Vector2f getPosition() { return m_position; };
        u_char getOctave() { return m_octave; };
        std::string getWaveType() { return m_waveType; };
        sf::Sound::Status getSoundStatus(uint index) { return m_notes[index].getStatus(); };

        void setOctave(uint octave) { (octave < 3 || octave > 7) ? /* do nothing */ : m_octave = octave;};
        void setWavetype(std::string waveType);

        uint buttonToNoteIndex(sf::Keyboard::Key button) { return m_buttonToNoteIndex.count(button) == 0 ? -1: m_buttonToNoteIndex[button]; };
        void playSound(uint index) { m_notes[index].play(); };
        void stopSound(uint index) { m_notes[index].stop(); };
        void draw(sf::RenderWindow &window);
        void highlightKey(uint index);
        void unhighlightKey(uint index);
};

#endif