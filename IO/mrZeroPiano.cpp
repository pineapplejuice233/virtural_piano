#include "IO.h"
#include "DrawKeyboard_header.h"
#include <string>
#include "yssimplesound.h"

int main()
{
	YsSoundPlayer playerA;				// create object of YsSoundPlayer
	YsSoundPlayer::SoundData wav[15];	// make array of wav 
	std::string files[15] = { "40.wav", "41.wav", "42.wav", "43.wav", "44.wav",
		"45.wav", "46.wav", "47.wav", "48.wav", "49.wav",
		"50.wav", "51.wav", "52.wav", "53.wav", "54.wav" };

	playerA.Start();	// start sound player

	std::string fileName = "easy.txt";	// default file name for song to load
	std::ifstream songToRead(fileName);	// 
	bool run = true;					// variable to control the program run
	overallPiano thePiano;				// create object of overallPiano class
	DrawKeyboard theKeyboard;			// create object of the DrawKeyboard class

	FsOpenWindow(16, 16, 900, 700, 1);  // open 900 x 900 screen
	bool notes[15] = { 0x0 };			// set notes to all false

	while (run)
	{

		//if (thePiano.getCurrentMode() == 3) {
		//	// set ifstream cursor to start
		//}

		if (thePiano.didModeChange())
		{
			// change filename of song based on current mode
			switch (thePiano.getCurrentMode())
			{
			case 0:
				fileName = "easy.txt";
				break;
			case 1:
				fileName = "medium.txt";
				break;
			case 2:
				fileName = "hard.txt";
				break;
			}
			// read song based on filename (easy/med/hard)
			songToRead.close();
			songToRead.open(fileName);
			thePiano.clearModeFlagChange();
			continue;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear double buffer
		run = thePiano.readSong(songToRead);	// read next line of instruction
		thePiano.songNextNotes(notes);			// loads instruction in notes array
		theKeyboard.highlightKey(notes);		// translates boolean notes array to position integer
		theKeyboard.draw();						// draw base layer
		theKeyboard.drawButton(thePiano);		// draw the mode buttons
		theKeyboard.highlightButton(thePiano);	// mode button highlight
		FsSwapBuffers();						// buffer swap


		// wait for user input
		while (!thePiano.didUserMakeInput()) {
			FsSleep(50);
		}

		if (thePiano.didUserESC()) {
			run = false;
			break;
		}
	
		playerA.KeepPlaying();
		thePiano.userNotesToPlay(notes);

		for (int i = 0; i < 15; i++) {
			if (notes[i]) {
				wav[i].LoadWav(files[i].c_str());
				playerA.PlayOneShot(wav[i]);
			}
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// clear double buffer
		thePiano.resetSongNotes();
		thePiano.songNextNotes(notes);
		theKeyboard.highlightKey(notes);
		theKeyboard.draw();
		theKeyboard.drawButton(thePiano);		// draw the mode buttons
		theKeyboard.highlightButton(thePiano);	// mode button highlight
		FsSwapBuffers();
		FsSleep(25);
	}

	return 0;
}

