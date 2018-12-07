
#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "DrawKeyboard_header.h"
#include <math.h>
#include "IO.h"

using namespace std;

DrawKeyboard::DrawKeyboard()
{
	for (int i = 0; i < 4; i++)
	{
		switch (i) {
		case 0:
			png[i].Decode("easy15.png");
			png[i].Flip();
			pngConvert[i].Decode("easy16.png");
			pngConvert[i].Flip();
			break;
		case 1:
			png[i].Decode("medium5.png");
			png[i].Flip();
			pngConvert[i].Decode("medium7.png");
			pngConvert[i].Flip();
			break;
		case 2:
			png[i].Decode("hard3.png");
			png[i].Flip();
			pngConvert[i].Decode("hard4.png");
			pngConvert[i].Flip();
			break;
		case 3:
			png[i].Decode("play2.png");
			png[i].Flip();
			pngConvert[i].Decode("play3.png");
			pngConvert[i].Flip();
			break;
		}
	}

	backPNG.Decode("back.png");
	backPNG.Flip();

	namePNG.Decode("name2.png");
	namePNG.Flip();
}

// this is the function that draws all the buttons (easy,medium,hard & free-play)
// the button are drawn by importing images
void DrawKeyboard::drawButton(overallPiano& Piano) {


	// temporary variable to store the image position.
	int cX, cY;
	// r is here because the getModeButtonPosition function requires
	// the dimensions of the images here, however, are hard-coded
	int r;

	// drawing the four buttons
	// get the image position for mode 0 (easy)
	Piano.getModeButtonPosition(0, cX, cY, r);
	// import the easy button image
	glRasterPos2i(cX - 55, cY + 55);
	glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, png[0].rgba);

	// get the image position for mode 1 (medium)
	Piano.getModeButtonPosition(1, cX, cY, r);
	// import the medium button image
	glRasterPos2i(cX - 55, cY + 55);
	glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, png[1].rgba);

	// get the image position for mode 2 (hard)
	Piano.getModeButtonPosition(2, cX, cY, r);
	// import the hard button image
	glRasterPos2i(cX - 55, cY + 55);
	glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, png[2].rgba);

	// get the image position for mode 3 (free-play)
	Piano.getModeButtonPosition(3, cX, cY, r);
	// import the free-play button image
	glRasterPos2i(cX - 55, cY + 55);
	glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, png[3].rgba);
}


// this is the function that gets the current mode from overallPiano class
// and highlight the corresponding mode (easy/medium/hard/free-play).
// The highlighting here means that choosen mode will change its image
void DrawKeyboard::highlightButton(overallPiano& Piano)
{
	// temporary variable to store the current mode.
	int CurrentModeState = Piano.getCurrentMode();
	// temporary variable to store the image position.
	int cX, cY;
	// r is here because the getModeButtonPosition function requires
	// the dimensions of the images here, however, are hard-coded
	int r;

	// get the image position for the current mode
	Piano.getModeButtonPosition(CurrentModeState, cX, cY, r);

	// change the image for current mode
	switch (CurrentModeState) {
		// Change the image of mode 0 (when easy is pressed)
	case 0:
		glRasterPos2i(cX - 55, cY + 55);
		glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, pngConvert[0].rgba);
		break;
		// Change the image of mode 1 (when medium is pressed)
	case 1:
		glRasterPos2i(cX - 55, cY + 55);
		glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, pngConvert[1].rgba);
		break;
		// Change the image of mode 2 (when hard is pressed)
	case 2:
		glRasterPos2i(cX - 55, cY + 55);
		glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, pngConvert[2].rgba);
		break;
		// Change the image of mode 3 (when free-play is pressed)
	case 3:
		glRasterPos2i(cX - 55, cY + 55);
		glDrawPixels(114, 114, GL_RGBA, GL_UNSIGNED_BYTE, pngConvert[3].rgba);
		glRasterPos2i(cX - 55, cY + 55);
		break;
	}
}


// this function draws all the white keys
void DrawKeyboard::drawWhiteKey() {
	for (int i = 0; i < 9; i++)
	{
		glColor3ub(0, 0, 0);
		//        glLineWidth(3.);
		glBegin(GL_POLYGON);
		glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY);
		glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight);
		for (int j = 0; j <= 180; j++) {
			if (j < 60 || j > 120) {
				glVertex2d(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI / 180) *
					WhiteKeyWidth / 2., KeyboardOriginY + WhiteKeyHeight + sin(j * PI / 180) * WhiteKeyWidth / 2.);
			}
		}
		glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1), KeyboardOriginY + WhiteKeyHeight);
		glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1), KeyboardOriginY);
		glEnd();

		glColor3ub(255, 255, 255);
		glBegin(GL_POLYGON);
		glVertex2i(KeyboardOriginX + LineWith + WhiteKeyWidth*i, KeyboardOriginY + LineWith);
		glVertex2i(KeyboardOriginX + LineWith + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight - LineWith);
		for (int j = 0; j <= 180; j++) {
			if (j < 60 || j > 120) {
				glVertex2i(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI / 180) *
					(WhiteKeyWidth / 2. - LineWith), KeyboardOriginY + WhiteKeyHeight + sin(j * PI / 180) *
					(WhiteKeyWidth / 2. - LineWith));
			}
		}
		glVertex2i(KeyboardOriginX - LineWith + WhiteKeyWidth*(i + 1), KeyboardOriginY + WhiteKeyHeight - LineWith);
		glVertex2i(KeyboardOriginX - LineWith + WhiteKeyWidth*(i + 1), KeyboardOriginY + LineWith);
		glEnd();
	}
}


// this function is used to highlight the necessary white keys
// the input parameter "highlightedKey" instructs which white key to highlight
// this function only highlights one key at one time
// To highlighted n keys, need to write a for loop and call this function n times
void DrawKeyboard::highlightWhiteKey(int highlightedKey)
{
	int i = highlightedKey - 1;
	glColor3ub(238, 232, 170);
	glBegin(GL_POLYGON);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight);
	for (int j = 0; j <= 180; j++)
	{
		if (j < 60 || j > 120)
		{
			glVertex2d(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI / 180)
				* WhiteKeyWidth / 2., KeyboardOriginY + WhiteKeyHeight + sin(j * PI / 180) * WhiteKeyWidth / 2.);
		}
	}
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1), KeyboardOriginY + WhiteKeyHeight);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1), KeyboardOriginY);

	glEnd();
}


// this function draws all the black keys
void DrawKeyboard::drawBlackKey() {
	for (int i = 0; i < 8; i++)
	{
		if (i != 2 && i != 6)
		{
			glColor3ub(0, 0, 0);
			glBegin(GL_POLYGON);
			glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) - BlackKeyWidth / 2., KeyboardOriginY);
			glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + BlackKeyWidth / 2., KeyboardOriginY);
			glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight);
			for (int j = 1; j <= 180; j++)
			{
				glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + cos(j * PI / 180) *
					BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight + sin(j * PI / 180) * BlackKeyWidth / 2.);
			}
			glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) - BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight);
			glEnd();
		}
	}
}


// this function is used to highlight the necessary black keys
// the input parameter "highlightedKey" instructs which white key to highlight
// this function only highlights one key at one time
// To highlighted n keys, need to write a for loop and call this function n times
void DrawKeyboard::highlightBlackKey(int highlightedKey)
{
	int i = highlightedKey - 10;
	glColor3ub(238, 232, 170);
	glBegin(GL_POLYGON);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) - BlackKeyWidth / 2., KeyboardOriginY);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + BlackKeyWidth / 2., KeyboardOriginY);
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight);
	for (int j = 1; j <= 180; j++)
	{
		glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) + cos(j * PI / 180) * BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight + sin(j * PI / 180) * BlackKeyWidth / 2.);
	}
	glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) - BlackKeyWidth / 2., KeyboardOriginY + BlackKeyHeight);

	glEnd();
}

// this function is to draw the keyboard and decide whether we need to highlight any keys or not
void DrawKeyboard::draw()
{
	// this is to insert the backgroud picture
	glRasterPos2i(1, 699);
	glDrawPixels(1152, 720, GL_RGBA, GL_UNSIGNED_BYTE, backPNG.rgba);

	// this is to insert the name picture
	glRasterPos2i(598 - 55, 95 + 55);
	glDrawPixels(277, 114, GL_RGBA, GL_UNSIGNED_BYTE, namePNG.rgba);

	// draw the white key
	drawWhiteKey();
	// highlight the white key
	for (int i = 0; i < 15; i++)
	{
		if (highlighted[i] < 10 && highlighted[i] > 0) highlightWhiteKey(highlighted[i]);
	}

	// draw the black key
	drawBlackKey();
	// highlight the black key
	for (int i = 0; i < 15; i++)
	{
		if (highlighted[i] >= 10) highlightBlackKey(highlighted[i]);
	}

	// get text messages
	// get text messages for the white keys
	for (int i = 0; i < 9; i++)
	{
		glColor3ub(0, 0, 0);
		glRasterPos2i(KeyboardOriginX + WhiteKeyWidth*i + WhiteKeyWidth / 2. - 10, KeyboardOriginY + WhiteKeyHeight - 50);  // sets position
		getText(i);
	}
	// get text messages for the black keys
	for (int i = 0; i < 9; i++)
	{
		if (i != 2 && i != 6)
		{
			glColor3ub(255, 255, 255);
			glRasterPos2i(KeyboardOriginX + WhiteKeyWidth*(i + 1) - 10, KeyboardOriginY + BlackKeyHeight - 50);  // sets position
			getText(i + 9);
		}
	}
	//FsSwapBuffers();
	//FsSleep(500);
}

// this function is to write text on every key
// It should be called after the drawing (and the highlighting)
void DrawKeyboard::getText(int KeyNumber)
{
	switch (KeyNumber)
	{
	case 0:
		YsGlDrawFontBitmap20x32("A");
		break;
	case 1:
		YsGlDrawFontBitmap20x32("S");
		break;
	case 2:
		YsGlDrawFontBitmap20x32("D");
		break;
	case 3:
		YsGlDrawFontBitmap20x32("F");
		break;
	case 4:
		YsGlDrawFontBitmap20x32("G");
		break;
	case 5:
		YsGlDrawFontBitmap20x32("H");
		break;
	case 6:
		YsGlDrawFontBitmap20x32("J");
		break;
	case 7:
		YsGlDrawFontBitmap20x32("K");
		break;
	case 8:
		YsGlDrawFontBitmap20x32("L");
		break;
	case 9:
		YsGlDrawFontBitmap20x32("W");
		break;
	case 10:
		YsGlDrawFontBitmap20x32("E");
		break;
	case 12:
		YsGlDrawFontBitmap20x32("T");
		break;
	case 13:
		YsGlDrawFontBitmap20x32("Y");
		break;
	case 14:
		YsGlDrawFontBitmap20x32("U");
		break;
	case 16:
		YsGlDrawFontBitmap20x32("O");
		break;
	}
}

// this is the function to determine what keys should be highlighted
void DrawKeyboard::highlightKey(bool TheSong[15])
{
	// go over all the 15 booleans
	for (int i = 0; i < 15; i++)
	{
		// if the boolean value is false, then zero this note with highlighted key at 0
		if (!TheSong[i]) highlighted[i] = 0;

		// if the boolean value is 1, then put give value to the highlighted key
		if (TheSong[i])
		{
			switch (i)
			{
				// this is when the white keys are highlighted
			case 0:
				highlighted[i] = 1;
				break;
			case 2:
				highlighted[i] = 2;
				break;
			case 4:
				highlighted[i] = 3;
				break;
			case 5:
				highlighted[i] = 4;
				break;
			case 7:
				highlighted[i] = 5;
				break;
			case 9:
				highlighted[i] = 6;
				break;
			case 11:
				highlighted[i] = 7;
				break;
			case 12:
				highlighted[i] = 8;
				break;
			case 14:
				highlighted[i] = 9;
				break;
				// this is when the black keys are highlighted
			case 1:
				highlighted[i] = 10;
				break;
			case 3:
				highlighted[i] = 11;
				break;
			case 6:
				highlighted[i] = 13;
				break;
			case 8:
				highlighted[i] = 14;
				break;
			case 10:
				highlighted[i] = 15;
				break;
			case 13:
				highlighted[i] = 17;
				break;
			}
		}
	}
}


