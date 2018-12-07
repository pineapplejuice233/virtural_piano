//// This is the header file to draw the keyboard
////
//// create at 2018.11.03 by Xiaoman
////      only parameters related to static keyboard are created
////
//
#ifndef DrawKeyboard_header_h
#define DrawKeyboard_header_h
#include "IO.h"
#include "yspng.h"

class DrawKeyboard
{
private:
	enum Mode { EASY, MEDIEUM, HARD };
	const int LineWith = 2;
	const int WhiteKeyWidth = 80;
	const int WhiteKeyHeight = 400;
	const int BlackKeyWidth = 50;
	const int BlackKeyHeight = 250;
	const int KeyboardOriginX = 100;
	const int KeyboardOriginY = 550 - WhiteKeyHeight;
	const int ButtonX = 150;
	const int ButtonY = 80;
	const int ButtonWide = 40;
	const double PI = 3.1415926;
	int highlighted[15];
	YsRawPngDecoder png[4];
	YsRawPngDecoder pngConvert[4];
	YsRawPngDecoder backPNG;
	YsRawPngDecoder namePNG;

	void getText(int KeyNumber); // this is to get the text message on each key
	void drawWhiteKey();
	void highlightWhiteKey(int highlightedKey);
	void drawBlackKey();
	void highlightBlackKey(int highlightedKey);

public:
	Mode currentMode;

	DrawKeyboard(); // constructor    
	void draw(); // this is to draw the keyboard
	void drawButton(overallPiano& Piano); // this is to draw the mode button
	void highlightButton(overallPiano& Piano); // this is to highlight the mode button
	void highlightKey(bool theSong[15]); // this is to highlight the key according to the reading file
};
#endif /* DrawKeyboard_h */

