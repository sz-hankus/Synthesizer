ROOT := $(CURDIR)
SFML := SFML

CXX := g++
CPPFLAGS := -std=c++17 -g -Wall
LIBS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
LDFLAGS := -L$(SFML)/lib
INCLUDES := -I$(SFML)/include -I$(ROOT)/include
PROGRAM := Synthesizer


all: main.o Button.o DropdownMenu.o Keyboard.o OctaveSelector.o RoundedRectangle.o SoundLib.o
	$(CXX) --output $(PROGRAM) main.o Button.o DropdownMenu.o Keyboard.o OctaveSelector.o RoundedRectangle.o SoundLib.o $(LDFLAGS) $(LIBS)

main.o: main.cpp
	$(CXX) $(CPPFLAGS) -c main.cpp $(INCLUDES)

Button.o: src/Button.cpp
	$(CXX) $(CPPFLAGS) -c src/Button.cpp $(INCLUDES)

DropdownMenu.o: src/DropdownMenu.cpp
	$(CXX) $(CPPFLAGS) -c src/DropdownMenu.cpp $(INCLUDES)

Keyboard.o: src/Keyboard.cpp
	$(CXX) $(CPPFLAGS) -c src/Keyboard.cpp $(INCLUDES)

OctaveSelector.o: src/OctaveSelector.cpp
	$(CXX) $(CPPFLAGS) -c src/OctaveSelector.cpp $(INCLUDES)

RoundedRectangle.o: src/RoundedRectangle.cpp
	$(CXX) $(CPPFLAGS) -c src/RoundedRectangle.cpp $(INCLUDES)

SoundLib.o: src/SoundLib.cpp
	$(CXX) $(CPPFLAGS) -c src/SoundLib.cpp -I$(ROOT)/src/SoundLib.h $(INCLUDES)

run: all
	./$(PROGRAM)

clean:
	rm -f *.o $(PROGRAM)