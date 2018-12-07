//
//  DrawKeyboard_functions.cpp
//  group_project
//
//  Created by Xiaoman Wang on 11/3/18.
//  Copyright © 2018 CMU. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "DrawKeyboard_header.h"
#include <math.h>
#include "IO.h"

using namespace std;

//#define PI = 3.141592653;

void DrawKeyboard::drawButton(overallPiano& Piano) {
//    glColor3ub(255, 255, 255);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < 360; i++) {
//        glVertex2d(ButtonX - ButtonWide * cos(i * PI / 180), ButtonY + ButtonWide * sin(i * PI / 180));
//    }
//    glEnd();
//    int centerX;
//    int centerY;
//    switch (currentMode) {
//        case EASY:
//            centerX = Piano.modeButtonX[0];
//            centerY = Piano.modeButtonY[0];
//            break;
//        case MEDIEUM:
//            centerX = Piano.modeButtonX[1];
//            centerY = Piano.modeButtonY[1];
//            break;
//        case HARD:
//            centerX = Piano.modeButtonX[2];
//            centerY = Piano.modeButtonY[2];
//            break;
//        default:
//            break;
//    }
//
//    glColor3ub(128,0,0);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < 360; i++) {
//        glVertex2d(centerX - Piano.modeButtonRadius * cos(i * PI / 180), centerY + Piano.modeButtonRadius * sin(i * PI / 180));
//    }
//    glEnd();
    int cX, cY, r;
    glColor3ub(128, 0, 0);
    for (int modeToDraw = 0; modeToDraw < Piano.howManyModes(); modeToDraw++) {
        Piano.getModeButtonPosition(modeToDraw, cX, cY, r);
        glBegin(GL_POLYGON);
        for (int i = 0; i < 360; i++) {
            glVertex2d(cX - r * cos(i * PI / 180), cY + r * sin(i * PI / 180));
        }
        glEnd();
    }
}

void DrawKeyboard::highlightButton(overallPiano& Piano)
{
    int CurrentModeState = Piano.getCurrentMode();
    int cX, cY, r;
    Piano.getModeButtonPosition(CurrentModeState, cX, cY, r);
    glColor3ub(243,0,0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) 
	{
        glVertex2d(cX - r * cos(i * PI / 180), cY + r * sin(i * PI / 180));
    }
    glEnd();
}

//void DrawKeyboard::drawStart(overallpiano& Piano) {
//    glColor3ub(0,0,0);
//    glBegin(GL_QUADS);
//    glVertex2i(Piano.startX, Piano.startY);
//    glVertex2i(Piano.startX + Piano.startWidth, Piano.startY);
//    glVertex2i(Piano.startX + Piano.startWidth, Piano.startY + Piano.startHeight);
//    glVertex2i(Piano.startX, Piano.startY + Piano.startHeight);
//    glEnd();
//}

void DrawKeyboard::drawWhiteKey() {
    for(int i = 0; i < 9; i++)
    {
        glColor3ub(0,0,0);
//        glLineWidth(3.);
        glBegin(GL_POLYGON);
        glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY);
        glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight);
        for (int j = 0; j <= 180; j++) {
            if (j < 60 || j > 120) {
                glVertex2d(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI/ 180) *
					WhiteKeyWidth/2. , KeyboardOriginY + WhiteKeyHeight + sin(j * PI/ 180) * WhiteKeyWidth/2.);
            }
        }
        glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1), KeyboardOriginY + WhiteKeyHeight);
        glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1), KeyboardOriginY);
        glEnd();
        
        glColor3ub(255,255,255);
        glBegin(GL_POLYGON);
        glVertex2i(KeyboardOriginX + LineWith + WhiteKeyWidth*i, KeyboardOriginY + LineWith);
        glVertex2i(KeyboardOriginX + LineWith + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight - LineWith);
        for (int j = 0; j <= 180; j++) {
            if (j < 60 || j > 120) {
                glVertex2i(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI/ 180) * 
					(WhiteKeyWidth/2. - LineWith) , KeyboardOriginY + WhiteKeyHeight + sin(j * PI/ 180) *
					(WhiteKeyWidth/2. - LineWith));
            }
        }
        glVertex2i(KeyboardOriginX - LineWith + WhiteKeyWidth*(i+1), KeyboardOriginY + WhiteKeyHeight - LineWith);
        glVertex2i(KeyboardOriginX - LineWith + WhiteKeyWidth*(i+1), KeyboardOriginY + LineWith);
        glEnd();
    }
}

void DrawKeyboard::highlightWhiteKey(int highlightedKey)
{
   int i = highlightedKey - 1;
   glColor3ub(238,232,170);
   glBegin(GL_POLYGON);
   glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY);
   glVertex2i(KeyboardOriginX + WhiteKeyWidth*i, KeyboardOriginY + WhiteKeyHeight);
   for (int j = 0; j <= 180; j++)
   {
       if (j < 60 || j > 120)
       {
           glVertex2d(KeyboardOriginX + WhiteKeyWidth * (i + 0.5) - cos(j * PI/ 180) 
			   * WhiteKeyWidth/2. , KeyboardOriginY + WhiteKeyHeight + sin(j * PI/ 180) * WhiteKeyWidth/2.);
        }
    }
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1), KeyboardOriginY + WhiteKeyHeight);
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1), KeyboardOriginY);
        
    glEnd();
}

void DrawKeyboard::drawBlackKey() {
    for(int i = 0; i < 8; i++)
    {
        if(i != 2 && i != 6)
        {
            glColor3ub(0,0,0);
            glBegin(GL_POLYGON);
            glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) - BlackKeyWidth/2., KeyboardOriginY);
            glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + BlackKeyWidth/2., KeyboardOriginY);
            glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + BlackKeyWidth/2., KeyboardOriginY + BlackKeyHeight);
            for (int j = 1; j <= 180; j++) 
			{
                glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + cos(j * PI/ 180) * 
					BlackKeyWidth/2. , KeyboardOriginY + BlackKeyHeight + sin(j * PI/ 180) * BlackKeyWidth / 2.);
            }
            glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) - BlackKeyWidth/2., KeyboardOriginY + BlackKeyHeight);
            glEnd();
        }
    }
}

void DrawKeyboard::highlightBlackKey(int highlightedKey)
{
    int i = highlightedKey - 10;
    glColor3ub(238,232,170);
    glBegin(GL_POLYGON);
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) - BlackKeyWidth/2., KeyboardOriginY);
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + BlackKeyWidth/2., KeyboardOriginY);
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + BlackKeyWidth/2., KeyboardOriginY + BlackKeyHeight);
    for (int j = 1; j <= 180; j++) 
	{
        glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) + cos(j * PI/ 180) * BlackKeyWidth/2. , KeyboardOriginY + BlackKeyHeight + sin(j * PI/ 180) * BlackKeyWidth / 2.);
    }
    glVertex2i(KeyboardOriginX + WhiteKeyWidth*(i+1) - BlackKeyWidth/2., KeyboardOriginY + BlackKeyHeight);
    
    glEnd();
}

// this function is to draw the keyboard and decide whether we need to highlight any keys or not
void DrawKeyboard::draw()
{
    // draw the white key
    drawWhiteKey();
    // highlight the white key
    for(int i = 0; i < 15; i++)
    {
        if(highlighted[i] < 10 && highlighted[i] > 0) highlightWhiteKey(highlighted[i]);
    }

    // draw the black key
    drawBlackKey();
    // highlight the black key
    for(int i = 0; i < 15; i++)
    {
        if(highlighted[i] >= 10) highlightBlackKey(highlighted[i]);
    }

    // get text messages
    // get text messages for the white keys
    for(int i = 0; i < 9; i++)
    {
        glColor3ub(0,0,0);
        glRasterPos2i(KeyboardOriginX + WhiteKeyWidth*i + WhiteKeyWidth/2. - 10, KeyboardOriginY + WhiteKeyHeight - 50);  // sets position
        getText(i);
    }
    // get text messages for the black keys
    for(int i = 0; i < 9; i++)
    {
        if(i != 2 && i != 6)
        {
            glColor3ub(255,255,255);
            glRasterPos2i(KeyboardOriginX + WhiteKeyWidth*(i+1)-10, KeyboardOriginY + BlackKeyHeight - 50);  // sets position
            getText(i+9);
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
    for(int i = 0; i < 15; i++)
    {
        // if the boolean value is false, then zero this note with highlighted key at 0
        if(!TheSong[i]) highlighted[i] = 0;
        
        // if the boolean value is 1, then put give value to the highlighted key
        if(TheSong[i])
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
