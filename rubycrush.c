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

#include <stdbool.h>
#include <avr/io.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <uzebox.h>

// graphics
#include "gfx_game.c"
#include "gfx_highlight.c"
#include "gfx_atascii.c"

// sounds
#include "sfx_patches.c"
#include "msc_gobby.c"

// utilities
#include "globals.c"
#include "text.c"
#include "hiscores.c"

// states
#include "state_menu.c"
#include "state_game.c"

// intro screen
void DoIntro()
{
	// random number generator seed
	u16 rndSeed = 0;
	
	// fade out
	FadeOut(1, true);
	
	// set the screen tiles
	SetTileTable(tiles_atascii);
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	DrawMap2(11, 9, map_mammoth_top);
	DrawMap2(11, 13, map_mammoth_bot);
	PrintStrCenter(17, "Blazing Mammoth Games");
	
	// fade in
	FadeIn(1, true);
	
	// game loop
	char quit = 0;
	while(!quit)
	{
		// wait for v sync
		WaitVsync(1);
		
		// update the seed
		rndSeed += 7;
		
		if(ReadJoypad(0) & BTN_START)
			quit = 1;
	}
	
	// seed the prng
	srand(rndSeed);
}

int main()
{
	// init sound
	InitMusicPlayer(patches);
	
	// init the hiscores eeprom
	InitHighScores();
	
	u8 ii;
	u32 score;
	GetHighScore(0, &ii, &ii, &ii, &score);
	highScoreClassic = score;
	GetHighScore(3, &ii, &ii, &ii, &score);
	highScoreTimed = score;

	// show the intro screen
	DoIntro();
	
	// set the initial state
	nextState = STATE_MENU;
	nextMenuState = MENUSTATE_MAIN;
	
	// now the game loop
	while(1)
	{
		// wait for v sync
		WaitVsync(1);
		
		// handle the input
		padHeld[0] = ReadJoypad(0);
		padPressed[0] = padHeld[0] & (padHeld[0] ^ padPrev[0]);
		padReleased[0] = padPrev[0] & (padHeld[0] ^ padPrev[0]);
		padPrev[0] = padHeld[0];
		padHeld[1] = ReadJoypad(1);
		padPressed[1] = padHeld[1] & (padHeld[1] ^ padPrev[1]);
		padReleased[1] = padPrev[1] & (padHeld[1] ^ padPrev[1]);
		padPrev[1] = padHeld[1];
		
		// need to load a new state
		if(nextState > -1)
		{
			// fade out
			FadeOut(1, true);
		
			// load the new state
			if(nextState == STATE_MENU)
				InitMenu();
			else if(nextState == STATE_GAME)
				InitGame();
				
			// set the states
			gameState = nextState;
			nextState = -1;
		}
		
		// handle the current state
		if(gameState == STATE_MENU)
			DoMenu();
		else if(gameState == STATE_GAME)
			DoGame();
	}
}
