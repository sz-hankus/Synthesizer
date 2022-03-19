#  A simple sound synthesizer with GUI

![showcase image](https://i.imgur.com/9ZDQqPi.png)

## Introduction
This project was written as a part of an assignment for my university. It's a sound synthesizer written in C++ and it utilizes the SFML library. The sounds are actively synthesized, meaning that their samples are calculated in the code rather than being stored in some mp3 or wav files.

## Usage
The interface is pretty self-explanatory. In order to press a given key on the virtual keyboard, you have to press the button it is labeled with on the physical keyboard (e.g. pressing `A` on the physical keyboard will result in the leftmost key being pressed and the corresponding sound playing). One can hold the key as long as they wish and the sound will continue playing.

**There are 3 types of wavetypes to be chosen : Sine, Square and Sawtooth.** In order to choose the wavetype, simply click the wavetype selector located in the upper left-hand corner and choose the desired wavetype from the list.

The element above the main keyboard is called the **Octave Selector**. It shows the entirety of a piano keyboard (with 5 octaves) and shows the user the octave that the main keyboard is currently in (the blue translucent rectangle always hoveres over the currently selected octave). **In order to change the octave, one has to press `X` to shift the keyboard down an octave, or `Z` to shift it up.**

## Quick intro
The main window and its logic is located in `main.cpp`. All of the interface elements are included in `main.cpp` and have their separate classes. The header files of these classes are in the `include` directory, while their implementations are in the `src` directory. 

`src` also contains some files which are neccessary for the implementation of the main classes. For example `src/RoundedRectangle.h` is a class that is used in all of the other main elements of the interface (e.g. `Button.h`, `Keyboard.h`)