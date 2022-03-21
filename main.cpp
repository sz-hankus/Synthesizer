#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "include/Keyboard.h"
#include "include/OctaveSelector.h"
#include "include/DropdownMenu.h"
#include "include/Button.h"

const uint SCREEN_WIDTH = sf::VideoMode::getDesktopMode().width;
const uint SCREEN_HEIGHT = sf::VideoMode::getDesktopMode().height;

const uint WINDOW_HEIGHT = SCREEN_HEIGHT/2.5;
const uint WINDOW_WIDTH = (float(WINDOW_HEIGHT)/5.0)*13;
// SCREEN_HEIGTH will be 5 units long and WINDOW_WIDTH will be 13 units long
// The keyboard itself will be 2.5 units by 11 units

int main() {
	// Turn on antialiasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Synthesizer v.1.0.0", sf::Style::Titlebar | sf::Style::Close, settings);
	window.setFramerateLimit(60); // for optimization
	
	float unit = WINDOW_WIDTH/13.0;
	float keyboardWidth = unit*11.0;
	float keyboardHeight = unit*2.5;

	Keyboard keyboard(sf::Vector2f(unit,1.5*unit), sf::Vector2f(keyboardWidth,keyboardHeight), 5, "Sine");
	
	OctaveSelector selector(sf::Vector2f(1.5*unit,0.3*unit), sf::Vector2f(unit*10.0, unit), keyboard.getOctave());

	std::vector <std::string> waveTypes = {"Sine", "Square", "Sawtooth"}; 
	DropdownMenu waveTypeMenu(sf::Vector2f(0.15*unit, 0.4*unit), sf::Vector2f(1.2*unit, 0.4*unit), waveTypes);

	Button leftButton(sf::Vector2f( 11.75*unit, 0.4*unit), sf::Vector2f(0.4*unit, 0.4*unit), "assets/arrowLeft.png");
	Button rightButton(sf::Vector2f( 12.35*unit, 0.4*unit), sf::Vector2f(0.4*unit, 0.4*unit), "assets/arrowRight.png");

	while(window.isOpen()) {
		sf::Event event;
        while (window.waitEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
			
			// HANDLING KEY PRESSES
			if (event.type == sf::Event::KeyPressed) {
				if(event.key.code == sf::Keyboard::Z) {
					// Shift the whole keyboard down an octave
					uint oct = keyboard.getOctave();
					keyboard.setOctave(oct-1);
					keyboard.loadBuffers();
					selector.setSelectorOct(oct-1);
					// Highlight the left button (the one in the interface)
					leftButton.highlight();
				} 
				else if(event.key.code == sf::Keyboard::X) {
					// Shift the whole keyboard up an octave
					uint oct = keyboard.getOctave();
					keyboard.setOctave(oct+1);
					keyboard.loadBuffers();
					selector.setSelectorOct(oct+1);
					// Highlight the right button (the one in the interface)
					rightButton.highlight();
				}
				else {
					// Play note corresponding to a key (button on the keyboard)
					uint noteIndex = keyboard.buttonToNoteIndex(event.key.code);
					if( noteIndex != -1 && keyboard.getSoundStatus(noteIndex) != sf::Sound::Playing) {
						keyboard.playSound(noteIndex);
						keyboard.highlightKey(noteIndex);
						selector.highlightKey((keyboard.getOctave()-3)*12 + noteIndex); // highlight on the selector too
					}
				}
				
			}

			// HANDLING KEY RELEASES
			if (event.type == sf::Event::KeyReleased) {
				if(event.key.code == sf::Keyboard::Z) {
					leftButton.unhighlight();
				}
				else if(event.key.code == sf::Keyboard::X) {
					rightButton.unhighlight();
				}
				else {
					uint noteIndex = keyboard.buttonToNoteIndex(event.key.code);
					if(noteIndex != -1) {
						keyboard.stopSound(noteIndex);
						keyboard.unhighlightKey(noteIndex);
						selector.unHighlightKey((keyboard.getOctave()-3)*12 + noteIndex); // unhighlight on the selector too
					}
				}
			}

			// HANDLE MOUSE EVENTS
			if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseMoved) {
				waveTypeMenu.handleMouseEvent(event);
				if (keyboard.getWaveType() != waveTypeMenu.getChosenItem()) {
					keyboard.setWavetype(waveTypeMenu.getChosenItem());
					keyboard.loadBuffers();
				}
			}
			
			// CLEARING, DRAWING AND DISPLAYING EVERYTHING
			window.clear(sf::Color::White);
			keyboard.draw(window);
			selector.draw(window);
			waveTypeMenu.draw(window);
			leftButton.draw(window);
			rightButton.draw(window);
			window.display();
        }
	}
	return 0;
}