#include "../include/Keyboard.h"
#include "../src/SoundLib.h"


// INITIALIZER
Keyboard::Keyboard(sf::Vector2f position, sf::Vector2f dimensions, uint octave, std::string waveType) {
    m_position = position;
	m_dimensions = dimensions;
    m_octave = octave;
	m_waveType = waveType;
	initMap();
	loadBuffers();
	initKeys();
	// Load the font from file
	if( !m_letterFont.loadFromFile("/Users/szymon/Desktop/Synthesizer/assets/VeraMono.ttf") ) {
		std::cerr << "Error loading font from file." <<  std::endl;
	}
}

// DESTRUCTOR
Keyboard::~Keyboard() {
	
} 

// Initializes map 
void Keyboard::initMap() {
    m_buttonToNoteIndex[sf::Keyboard::A] = 0;
	m_buttonToNoteIndex[sf::Keyboard::W] = 1;
	m_buttonToNoteIndex[sf::Keyboard::S] = 2;
	m_buttonToNoteIndex[sf::Keyboard::E] = 3;
	m_buttonToNoteIndex[sf::Keyboard::D] = 4;
	m_buttonToNoteIndex[sf::Keyboard::F] = 5;
	m_buttonToNoteIndex[sf::Keyboard::T] = 6;
	m_buttonToNoteIndex[sf::Keyboard::G] = 7;
	m_buttonToNoteIndex[sf::Keyboard::Y] = 8;
	m_buttonToNoteIndex[sf::Keyboard::H] = 9;
	m_buttonToNoteIndex[sf::Keyboard::U] = 10;
	m_buttonToNoteIndex[sf::Keyboard::J] = 11;
	m_buttonToNoteIndex[sf::Keyboard::K] = 12;
	m_buttonToNoteIndex[sf::Keyboard::O] = 13;
	m_buttonToNoteIndex[sf::Keyboard::L] = 14;
	m_buttonToNoteIndex[sf::Keyboard::P] = 15;
	m_buttonToNoteIndex[sf::Keyboard::SemiColon] = 16;
	m_buttonToNoteIndex[sf::Keyboard::Quote] = 17;
}

// Loads buffers for sf::Sound objects (m_notes)
void Keyboard::loadBuffers() {
    double frequencies[KB_SIZE];
	std::string waveType = m_waveType;
	
	calculateNoteFrequencies(frequencies, KB_SIZE, m_octave);

	for (int i = 0; i < KB_SIZE; i++) {
		m_buffers[i] = getFilledBuffer(frequencies[i], m_waveType);
		m_notes[i].setBuffer(m_buffers[i]);
		m_notes[i].setLoop(true);
	}
}

// GETTERS
sf::Vector2f Keyboard::getPosition() {
	return m_position;
}
u_char Keyboard::getOctave() {
	return m_octave;
}
std::string Keyboard::getWaveType() {
	return m_waveType;
}
sf::Sound::Status Keyboard::getSoundStatus(uint index) {
	return m_notes[index].getStatus();
}

// SETTERS
void Keyboard::setOctave(uint octave) {
	(octave < 3 || octave > 7) ? /* do nothing */ : m_octave = octave;
}
void Keyboard::setWavetype(std::string waveType) {
	if (std::find(WAVETYPES.begin(), WAVETYPES.end(), waveType) != WAVETYPES.end()) {
		m_waveType = waveType;
	}
}

// Helper function, checks if key is white by its index
bool isKeyWhite(uint index) {
	if(index <= 4 || (index >= 12 && index <= 16)) {
		if(index%2 == 0)
			return true;
		else
			return false;
	}
	else if (index >= 5 && index <= 11) {
		if(index%2 == 0)
			return false;
		else
			return true;
	}
	else if (index == 17) 
		return true;
	
	return true;
}

// Initialize key sizes, positions etc. and also the letters
void Keyboard::initKeys() {
	float unit = m_dimensions.x / 11;
	sf::Vector2f startPos = sf::Vector2f(m_position.x, m_position.y);
	sf::Vector2f whiteSize = sf::Vector2f(unit, 2.5*unit);
	sf::Vector2f blackSize = sf::Vector2f(0.8*unit, 1.5*unit);

	for (int i = 0; i < KB_SIZE; i++) {
		if(isKeyWhite(i)) {
			m_keys[i].setFillColor(sf::Color::White);
			m_keys[i].setSize(whiteSize);
		}
		else {
			m_keys[i].setFillColor(sf::Color::Black);
			m_keys[i].setSize(blackSize);
		} 
		m_keys[i].setOutlineColor(sf::Color::Black);
		m_keys[i].setOutlineThickness(2.0);
	}

	// Set up all letters
	std::string lettersInOrder = "AWSEDFTGYHUJKOLP;'";
	for (int i = 0; i < KB_SIZE; i++) {
		m_keyLetters[i].setFont(m_letterFont);
		if(isKeyWhite(i))
			m_keyLetters[i].setFillColor(sf::Color::Black);
		else
			m_keyLetters[i].setFillColor(sf::Color::White);

		m_keyLetters[i].setString(lettersInOrder[i]);
		m_keyLetters[i].setCharacterSize(uint(unit/3));
		m_keyLetters[i].setOutlineColor(sf::Color(107,107,107));
		m_keyLetters[i].setOutlineThickness(1.0);
	}



	// This is probably the easiest and cleanest way to do this, because it can be manually tweaked

	m_keys[0].setPosition(startPos); // C
	m_keyLetters[0].setPosition( startPos + sf::Vector2f(0.15*unit, 2*unit));

	m_keys[1].setPosition( startPos + sf::Vector2f(0.75*unit, 0.0)); // C#
	m_keyLetters[1].setPosition(startPos + sf::Vector2f(0.90*unit, 1*unit));

	m_keys[2].setPosition( m_keys[0].getPosition() + sf::Vector2f(unit, 0.0)); // D
	m_keyLetters[2].setPosition( m_keyLetters[0].getPosition() + sf::Vector2f(unit, 0.0));

	m_keys[3].setPosition( m_keys[1].getPosition() + sf::Vector2f(unit, 0.0)); // D#
	m_keyLetters[3].setPosition( m_keyLetters[1].getPosition() + sf::Vector2f(unit, 0.0));

	m_keys[4].setPosition( m_keys[2].getPosition() + sf::Vector2f(unit, 0.0)); // E
	m_keyLetters[4].setPosition( m_keyLetters[2].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[5].setPosition( m_keys[4].getPosition() + sf::Vector2f(unit, 0.0)); // F
	m_keyLetters[5].setPosition( m_keyLetters[4].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[6].setPosition( m_keys[3].getPosition() + sf::Vector2f(2*unit, 0.0)); // F#
	m_keyLetters[6].setPosition( m_keyLetters[3].getPosition() + sf::Vector2f(2*unit, 0.0)); 

	m_keys[7].setPosition( m_keys[5].getPosition() + sf::Vector2f(unit, 0.0)); // G
	m_keyLetters[7].setPosition( m_keyLetters[5].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[8].setPosition( m_keys[6].getPosition() + sf::Vector2f(unit, 0.0)); // G#
	m_keyLetters[8].setPosition( m_keyLetters[6].getPosition() + sf::Vector2f(unit, 0.0));

	m_keys[9].setPosition( m_keys[7].getPosition() + sf::Vector2f(unit, 0.0)); // A
	m_keyLetters[9].setPosition( m_keyLetters[7].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[10].setPosition( m_keys[8].getPosition() + sf::Vector2f(unit, 0.0)); // A#
	m_keyLetters[10].setPosition( m_keyLetters[8].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[11].setPosition( m_keys[9].getPosition() + sf::Vector2f(unit, 0.0)); // B
	m_keyLetters[11].setPosition( m_keyLetters[9].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[12].setPosition( m_keys[11].getPosition() + sf::Vector2f(unit, 0.0)); // C
	m_keyLetters[12].setPosition( m_keyLetters[11].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[13].setPosition( m_keys[10].getPosition() + sf::Vector2f(2*unit, 0.0)); // C#
	m_keyLetters[13].setPosition( m_keyLetters[10].getPosition() + sf::Vector2f(2*unit, 0.0)); 

	m_keys[14].setPosition( m_keys[12].getPosition() + sf::Vector2f(unit, 0.0)); // D
	m_keyLetters[14].setPosition( m_keyLetters[12].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[15].setPosition( m_keys[13].getPosition() + sf::Vector2f(unit, 0.0)); // D#
	m_keyLetters[15].setPosition( m_keyLetters[13].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[16].setPosition( m_keys[14].getPosition() + sf::Vector2f(unit, 0.0)); // E
	m_keyLetters[16].setPosition( m_keyLetters[14].getPosition() + sf::Vector2f(unit, 0.0)); 

	m_keys[17].setPosition( m_keys[16].getPosition() + sf::Vector2f(unit, 0.0)); // F
	m_keyLetters[17].setPosition( m_keyLetters[16].getPosition() + sf::Vector2f(unit, 0.0)); 
}

// Returns index corresponding to (physical) button using m_buttonToIndex map
uint Keyboard::buttonToNoteIndex(sf::Keyboard::Key button) {
	return m_buttonToNoteIndex.count(button) == 0 ? -1: m_buttonToNoteIndex[button];
}

void Keyboard::playSound(uint index) {
	m_notes[index].play();
}

void Keyboard::stopSound(uint index) {
	m_notes[index].stop();
}

void Keyboard::draw(sf::RenderWindow &window) {
	// First the white keys
	for (int i = 0; i < KB_SIZE; i++) {
		if(isKeyWhite(i))
			window.draw(m_keys[i]); 
	}

	// Then the black keys
	for (int i = 0; i < KB_SIZE; i++) {
		if(!isKeyWhite(i))
			window.draw(m_keys[i]); 
	}

	// Then the letters
	for (int i = 0; i < KB_SIZE; i++) {
		window.draw(m_keyLetters[i]); 
	}
	
}

void Keyboard::highlightKey(uint index) {
	m_keys[index].setFillColor(sf::Color(107,107,107));
}

void Keyboard::unhighlightKey(uint index) {
	if(isKeyWhite(index))
		m_keys[index].setFillColor(sf::Color::White);
	else
		m_keys[index].setFillColor(sf::Color::Black);

}