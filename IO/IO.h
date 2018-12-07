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
	bool userESC = false;
	bool songNotes[15] = { 0x0 };			// Array of next notes to play (visual, audio)
	bool userKeyDepressed[15] = { 0x0 };	// array to tell visual to highlight piano key
	bool userKeyFirstPressed[15] = { 0x0 };	// array to tell audio to play note
	int orderOfComputerKeys[15] = { FSKEY_A, FSKEY_W, FSKEY_S, FSKEY_E, FSKEY_D, 
									FSKEY_F, FSKEY_T, FSKEY_G, FSKEY_Y, FSKEY_H, 
									FSKEY_U, FSKEY_J, FSKEY_K, FSKEY_O, FSKEY_L };
	std::vector<std::string> orderOfPianoKeys = { "A", "AsBf", "B", "CsDf", "C", "D", 
													"DsEf", "E", "EsFf", "F", "FsGf", 
														"G", "AA", "AAsBBf", "BB"};

	const int qtyModes = 3;
	int modeButtonX[3] = { 160, 320, 480 };
	int modeButtonY[3] = { 100, 100, 100 };
	int modeButtonRadius = 40;

	void checkModeChanged(void);		// Check mouse inputs
	void checkKeyStates(void);			// Check keyboard inputs
	void setCurrentMode(int newMode);	// Sets the current mode to the parameter value.

	int checkValidNote(std::string noteToCheck);

public:
	int getCurrentMode(void);		// returns int of currentMode
	bool didModeChange(void);		// returns boolean if mode changed upon last user input
	bool didUserESC(void);
	int howManyModes(void);			// How many modes is the program running
	bool didUserMakeInput(void);
	void clearModeFlagChange(void);

	bool readSong(std::ifstream &songToRead);		// Reads next line of song
	
	void resetSongNotes(void);		
	void resetUserNotes(void);
	void getUserInput(void);						// Root I/O function - calls other functions. Returns false is user presses ESC

	void songNextNotes(bool whereToStore[15]);		// deep copies the songNotes to the parameter
	void userNotesToPlay(bool whereToStore[15]);	// deep copies the userKeyFirstPressed to the parameter
	void userNotesToDisplay(bool whereToStore[15]);	// deep copies the userKeyDepressed to the parameter
	void printUsersInput(void);						// terminal prints the user's keyboard input

	void getModeButtonPosition(const int mode, int &centerX, int &centerY, int &radius);	// sets the parameters to the appropriate mode button
	void drawBasicPiano(void);						// dummy function mostly used for testing
};

void drawCircle_testing(int cx, int cy, int rad, bool fill);