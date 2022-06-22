#include "../include/OctaveSelector.h"

const uint KB_SIZE = 12; // amount of keys in one small keyboard (there will be 5 of them displayed plus a part of one keyboard(from C to F))
const uint TOTAL_KEYS = KB_SIZE*OCTAVES + 6;

OctaveSelector::OctaveSelector(sf::Vector2f position, sf::Vector2f dimensions, uint selectorOct) {
    m_position = position;
    m_dimensions = dimensions;
    if(selectorOct < 3)
        m_selectorOct = 3;
    else if(selectorOct > 7)
        m_selectorOct = 7;
    else
        m_selectorOct = selectorOct;
    
    initKeys();
    initSelector();
}  


void OctaveSelector::initSelector() {
    float unit = m_dimensions.x / (7 * OCTAVES + 4); // Width of a single white key
    float cornerRadius = unit/3;

    m_selector.setPosition(m_position.x + (m_selectorOct-3)*7*unit, m_position.y - cornerRadius);
    m_selector.setSize(sf::Vector2f(11*unit, (2.5*unit) + (2*cornerRadius)));
    m_selector.setFillColor(sf::Color(56, 116, 240, 120));
    m_selector.setOutlineColor(sf::Color(56, 116, 240));
    m_selector.setOutlineThickness(2.5);
    m_selector.setRadius(unit/5);
    m_selector.setCornerPointCount(15);
}

void OctaveSelector::setSelectorOct(uint oct) {
    if(oct < 3)
        oct = 3;
    else if(oct > 7)
        oct = 7;


    float unit = m_dimensions.x / (7 * OCTAVES + 4); // Width of a single white key
    
    // calculate the shift in position using the recent and previous octave
    sf::Vector2f shiftPosition(int(oct - m_selectorOct)*7*unit, 0);
    sf::Vector2f oldPosition = m_selector.getPosition();

    m_selector.setPosition(oldPosition + shiftPosition);
    m_selectorOct = oct;
}

// Helper function, checks if key is white by its index
bool isKeyWhite_(uint index) {
    index = index % KB_SIZE;

	if(index <= 4) {
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
	
	return true;
}

void OctaveSelector::initKeys() {

    float unit = m_dimensions.x / (7 * OCTAVES + 4);
	sf::Vector2f whiteSize = sf::Vector2f(unit, 2.5*unit);
	sf::Vector2f blackSize = sf::Vector2f(0.5*unit, 1.5*unit);


    for (int i = 0; i < TOTAL_KEYS; i++) {
        if(isKeyWhite_(i)) {
            m_keys[i].setFillColor(sf::Color::White);
            m_keys[i].setSize(whiteSize);
        }
        else {
            m_keys[i].setFillColor(sf::Color::Black);
            m_keys[i].setSize(blackSize);
        } 
        m_keys[i].setOutlineColor(sf::Color::Black);
        m_keys[i].setOutlineThickness(1.0);
    }


    // setting all the positions
    int SI = 0; // Start Index for each small keyboard (e.g. for the first keyboard SI = 0, for the second SI = 12, etc.)
    sf::Vector2f startPos = sf::Vector2f(m_position.x, m_position.y);

    for (int oct = 3; oct <= 7; oct++) {
        m_keys[0 + SI].setPosition(startPos); // C
        m_keys[1 + SI].setPosition( startPos+sf::Vector2f(0.75*unit, 0.0)); // C#
        m_keys[2 + SI].setPosition( m_keys[0 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // D
        m_keys[3 + SI].setPosition( m_keys[1 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // D#
        m_keys[4 + SI].setPosition( m_keys[2 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // E
        m_keys[5 + SI].setPosition( m_keys[4 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // F
        m_keys[6 + SI].setPosition( m_keys[3 + SI].getPosition() + sf::Vector2f(2*unit, 0.0)); // F#
        m_keys[7 + SI].setPosition( m_keys[5 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // G
        m_keys[8 + SI].setPosition( m_keys[6 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // G#
        m_keys[9 + SI].setPosition( m_keys[7 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // A
        m_keys[10 + SI].setPosition( m_keys[8 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // A#
        m_keys[11 + SI].setPosition( m_keys[9 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // B
        

        startPos = m_keys[11 + SI].getPosition() + sf::Vector2f(unit, 0.0);
        SI += KB_SIZE;
    }
    // Set the position for the remainding keys in the last octave 
    SI-=KB_SIZE;
    m_keys[12 + SI].setPosition( m_keys[11 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // C
    m_keys[13 + SI].setPosition( m_keys[10 + SI].getPosition() + sf::Vector2f(2*unit, 0.0)); // C#
    m_keys[14 + SI].setPosition( m_keys[12 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // D
    m_keys[15 + SI].setPosition( m_keys[13 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // D#
    m_keys[16 + SI].setPosition( m_keys[14 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // E
    m_keys[17 + SI].setPosition( m_keys[16 + SI].getPosition() + sf::Vector2f(unit, 0.0)); // F
}

void OctaveSelector::highlightKey(uint index) {
    m_keys[index].setFillColor(sf::Color(107,107,107));
}

void OctaveSelector::unHighlightKey(uint index) {
    if(isKeyWhite_(index))
		m_keys[index].setFillColor(sf::Color::White);
	else
		m_keys[index].setFillColor(sf::Color::Black);
}

void OctaveSelector::unHighlightAll() {
    for (int index = 0; index < TOTAL_KEYS; index++)
        unHighlightKey(index);
}

void OctaveSelector::draw(sf::RenderWindow &window) {
    for (int i = 0; i < TOTAL_KEYS; i++) {
        if (isKeyWhite_(i))
            window.draw(m_keys[i]);
    }
    for (int i = 0; i < TOTAL_KEYS; i++) {
        if (!isKeyWhite_(i))
            window.draw(m_keys[i]);
    }
    window.draw(m_selector);
}