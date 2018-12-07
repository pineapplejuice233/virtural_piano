/*
24-780 Eng Comp
Final Project: Mr Zero Virtual Piano
Component: User Input
Matthew Bartnof

2018 Dec 01 New Mode
- Added 4th mode button for free play with coordinate from Xiaoman

2018 11 30 General housekeeping
- Added more comments
- Commented out unnecessary lines of code, but did not delete
- Commented out unnecessary functions, but did not delete
*/

#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <math.h>
#include <vector>
#include <string>
#include <algorithm>
#include "fssimplewindow.h"

class overallPiano {
private:
	int currentMode = 0;					// Mode storage variable
	bool modeChanged = false;				// flag to indicate mode has changed
	bool userESC = false;					// flag to indicate user wants to end program
	bool songNotes[15] = { 0x0 };			// Array of next notes to play (visual, audio)
	bool userKeyDepressed[15] = { 0x0 };	// array to tell visual to highlight piano key
	bool userKeyFirstPressed[15] = { 0x0 };	// array to tell audio to play note

											// arrays to map user's inputs (computer keys) to musical notes (piano key)
											// These arrays also represent the order of the notes stored by the bool arrays above
	int orderOfComputerKeys[15] = { FSKEY_A, FSKEY_W, FSKEY_S, FSKEY_E, FSKEY_D,
		FSKEY_F, FSKEY_T, FSKEY_G, FSKEY_Y, FSKEY_H,
		FSKEY_U, FSKEY_J, FSKEY_K, FSKEY_O, FSKEY_L };
	std::vector<std::string> orderOfPianoKeys = { "A", "AsBf", "B", "CsDf", "C", "D",
		"DsEf", "E", "EsFf", "F", "FsGf",
		"G", "AA", "AAsBBf", "BB" };

	const int qtyModes = 4;						// How many playing modes do we have?
	int modeButtonX[4] = { 155, 265, 375, 485 };// x-coordinate of mode change buttons
	int modeButtonY[4] = { 95, 95, 95, 95 };	// y-coordinate of mode change buttons
	int modeButtonRadius = 50;					// size of mode change buttons

	void checkModeChanged(void);		// Check mouse inputs
	void checkKeyStates(void);			// Check keyboard inputs
	void setCurrentMode(int newMode);	// Sets the current mode to the parameter value.

	int checkValidNote(std::string noteToCheck); // Check if read note is part of piano and return appropriate position in bool array

public:
	int getCurrentMode(void);		// returns int of currentMode
	bool didModeChange(void);		// returns true if mode changed upon last user input
	bool didUserESC(void);			// returns true if user wants to end the program
	int howManyModes(void);			// How many modes is the program running
	bool didUserMakeInput(void);	// returns true if user made any input
	void clearModeFlagChange(void);	// returns true if user pressed a new key, changed mode, or wants to end program (ESC)

	bool readSong(std::ifstream &songToRead);		// Reads next line of song

	void resetSongNotes(void);		// Allow song instructions to be cleared
									//void resetUserNotes(void);	// Clear user inputs
	void getUserInput(void);						// Root I/O function - calls other functions. Returns false is user presses ESC

	void songNextNotes(bool whereToStore[15]);		// deep copies the songNotes to the parameter
	void userNotesToPlay(bool whereToStore[15]);	// deep copies the userKeyFirstPressed to the parameter
	void userNotesToDisplay(bool whereToStore[15]);	// deep copies the userKeyDepressed to the parameter
	void printUsersInput(void);						// terminal prints the user's keyboard input

	void getModeButtonPosition(const int mode, int &centerX, int &centerY, int &radius);	// sets the parameters to the appropriate mode button
																							//void drawBasicPiano(void);						// dummy function mostly used for testing
};
