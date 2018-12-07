#include "IO.h"


int main() {
	overallPiano thePiano;
	std::ifstream songToRead("easy.txt");
	bool validInput = true;

	FsOpenWindow(16, 16, 300, 300, 1);  // Draw new screen
	bool dummy[15] = { 0x0 };

	while (validInput) {
		thePiano.drawBasicPiano();
		
		validInput = thePiano.readSong(songToRead);

		if (validInput) {
			thePiano.songNextNotes(dummy);

			for (int i = 0; i < 15; i++) {
				std::cout << dummy[i];
			}
			std::cout << std::endl;

			FsSleep(100);
		}
		else {
			std::cout << "Song over!" << std::endl;
		}


	}
	return 0;
}

