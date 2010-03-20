/*
	Ruby Crush for the Uzebox
	Copyright 2010, Kenton Hamaluik

	This file is part of Ruby Crush for the Uzebox.

	Ruby Crush for the Uzebox is free software: you can redistribute
	it and/or modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation, either version 3 of the
	License, or (at your option) any later version.

	Ruby Crush for the Uzebox is distributed in the hope that it
	will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with The Uzebox Implementation of Pentago.  If not, see
	<http://www.gnu.org/licenses/>.
*/

// the menu states
#define MENUSTATE_MAIN			(0)
#define MENUSTATE_HISCORES		(1)
#define MENUSTATE_NEWHIGHSCORE	(2)
char menuState;
char nextMenuState;

// main menu selections
#define MENUOPT_CLASSIC		(0)
#define MENUOPT_TIMED		(1)
#define MENUOPT_MUSIC		(2)
#define MENUOPT_HISCORES	(3)
char currentOpt = 0;

// game stuff
u8 jewels[8][8], tempJewels[8][8];
u8 combo;
u32 level;
u32 playerScore;
u32 highScoreClassic, highScoreTimed;
u32 lastScoreLevel;
u32 nextScoreLevel;
u8 gameOver;
u8 hlX, hlY, grabX, grabY;
u32 frameCount, lastCount;
u8 movingHl, grabbing, showHint;
s32 timer, timerRate;
u32 hintsLeft;

// joypad states
int padHeld[2] = {0,0};
int padPressed[2] = {0,0};
int padReleased[2] = {0,0};
int padPrev[2] = {0,0};

// globals
char musicOn = 0;
char playMode;

// game states
#define STATE_MENU	(0)
#define STATE_GAME	(1)
char gameState;
char nextState;

// play modes
#define MODE_CLASSIC	(0)
#define MODE_TIMED		(1)
