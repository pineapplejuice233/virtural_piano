#include <stdio.h>
#include <string>
#include <iostream>
#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "IO.h"
//#include "sound.h"

using namespace std;

void playSound() {

	YsSoundPlayer playerA;
	//YsSoundPlayer playerB;
	YsSoundPlayer::SoundData wav[15];
	string files[15] = { "40.wav", "41.wav", "42.wav", "43.wav", "44.wav",
						 "45.wav", "46.wav", "47.wav", "48.wav", "49.wav",
						 "50.wav", "51.wav", "52.wav", "53.wav", "54.wav"};
	//cout << files[1];

	playerA.Start();
	//playerB.Start();
	overallPiano thePiano;
	
	bool validInput = true;
	bool dummy[15] = { 0x0 };

	int key;
	bool terminate = false;
	while (!terminate/*validInput*/) {

		validInput = thePiano.getUserInput();
		playerA.KeepPlaying();
		
		thePiano.userNotesToPlay(dummy);
		for (int i = 0; i < 15; i++) {
			if (dummy[i]) {
				wav[i].LoadWav(files[i].c_str());
				playerA.PlayOneShot(wav[i]);
			}
		}
	}

	playerA.End();
}

int main() {

	FsOpenWindow(16, 16, 800, 600, 1);
	playSound();

	FsSwapBuffers();
	return 0;
}