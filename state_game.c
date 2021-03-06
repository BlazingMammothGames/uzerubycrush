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

u32 pow10(s8 p)
{
	u32 ret = 1;
	for(s8 i = 0; i < p; i++)
		ret *= 10;
	return ret;
}

void ClearPoints()
{
	Fill(2, 20, 7, 1, MAP_SCORE_PURPLE);
}

void DrawPoints(u32 points)
{
	u8 width;
	if(points > 99999)
		width = 6;
	else if(points > 9999)
		width = 5;
	else if(points > 999)
		width = 4;
	else if(points > 99)
		width = 3;
	else if(points > 9)
		width = 2;
	else
		width = 1;

	u8 start = ((7 - width) / 2) + 3;
	SetTile(start - 1, 20, POINT_OFFSET + 10); // +
	for(u8 x = 0; x < width; x++)
		SetTile(start + x, 20, POINT_OFFSET + ((points % pow10(width - x)) / pow10(width - x - 1)));
}

void DrawScore()
{
	u8 left;
	if(playerScore > 999999)
		left = 0;
	else if(playerScore > 99999)
		left = 1;
	else if(playerScore > 9999)
		left = 2;
	else if(playerScore > 999)
		left = 3;
	else if(playerScore > 99)
		left = 4;
	else if(playerScore > 9)
		left = 5;
	else
		left = 6;
	
	Fill(2, 7, 7, 1, SCORE_BLANK);
	for(s8 x = 6; x >= left; x--)
	{
		SetTile(x + 2, 7, SCORE_OFFSET + ((playerScore % pow10((6 - x) + 1)) / pow10(6 - x)));
	}
}

void DrawHighScore()
{
	u32 highScore = (playMode == MODE_CLASSIC) ? (highScoreClassic) : (highScoreTimed);

	u8 left;
	if(highScore > 999999)
		left = 0;
	else if(highScore > 99999)
		left = 1;
	else if(highScore > 9999)
		left = 2;
	else if(highScore > 999)
		left = 3;
	else if(highScore > 99)
		left = 4;
	else if(highScore > 9)
		left = 5;
	else
		left = 6;
	
	Fill(2, 9, 7, 1, SCORE_BLANK);
	for(s8 x = 6; x >= left; x--)
	{
		SetTile(x + 2, 9, SCORE_OFFSET + ((highScore % pow10((6 - x) + 1)) / pow10(6 - x)));
	}
}

void DrawLevel()
{
	u8 left;
	if(level > 999999)
		left = 0;
	else if(level > 99999)
		left = 1;
	else if(level > 9999)
		left = 2;
	else if(level > 999)
		left = 3;
	else if(level > 99)
		left = 4;
	else if(level > 9)
		left = 5;
	else
		left = 6;
	
	Fill(2, 11, 7, 1, SCORE_BLANK);
	for(s8 x = 6; x >= left; x--)
	{
		SetTile(x + 2, 11, SCORE_OFFSET + ((level % pow10((6 - x) + 1)) / pow10(6 - x)));
	}
}

void DrawHints()
{
	u8 left;
	if(hintsLeft > 999999)
		left = 0;
	else if(hintsLeft > 99999)
		left = 1;
	else if(hintsLeft > 9999)
		left = 2;
	else if(hintsLeft > 999)
		left = 3;
	else if(hintsLeft > 99)
		left = 4;
	else if(hintsLeft > 9)
		left = 5;
	else
		left = 6;
	
	Fill(2, 13, 7, 1, SCORE_BLANK);
	for(s8 x = 6; x >= left; x--)
	{
		SetTile(x + 2, 13, SCORE_OFFSET + ((hintsLeft % pow10((6 - x) + 1)) / pow10(6 - x)));
	}
}

void DrawBar(u32 numerator, u32 denominator)
{
	//u32 scoreDone = playerScore - lastScoreLevel;
	//u32 scoreTotal = nextScoreLevel - lastScoreLevel;
	
	// calculate the number of pixel columns to display
	u32 numCol = (numerator << 7) / denominator;
	
	// calculate the number of full bars to display
	u8 numFull = (u8)(numCol / 8);
	
	// calculate the number of part bars to display
	u8 numPart = (u8)(numCol % 8);
	
	// clear the old bar
	for(u8 i = 0; i < 16; i++)
		SetTile(11 + i, 23, MAP_BAR_FILLS);
	
	// now fill the full bars in
	for(u8 i = 0; i < numFull; i++)
		SetTile(11 + i, 23, MAP_BAR_FILLS + 8);
		
	if(numFull < 16)
		SetTile(11 + numFull, 23, MAP_BAR_FILLS + numPart);
}

void SetHlXY(u8 x, u8 y)
{
	sprites[0].x = 88 + (x * 16);
	sprites[0].y = 48 + (y * 16);
	sprites[1].x = 96 + (x * 16);
	sprites[1].y = 48 + (y * 16);
	sprites[2].x = 88 + (x * 16);
	sprites[2].y = 56 + (y * 16);
	sprites[3].x = 96 + (x * 16);
	sprites[3].y = 56 + (y * 16);
}

void SetGrabXY(u8 x, u8 y)
{
	sprites[4].x = 88 + (x * 16);
	sprites[4].y = 48 + (y * 16);
	sprites[5].x = 96 + (x * 16);
	sprites[5].y = 48 + (y * 16);
	sprites[6].x = 88 + (x * 16);
	sprites[6].y = 56 + (y * 16);
	sprites[7].x = 96 + (x * 16);
	sprites[7].y = 56 + (y * 16);
}

void SetHintXY(u8 x, u8 y)
{
	sprites[8].x = 88 + (x * 16);
	sprites[8].y = 48 + (y * 16);
	showHint = 1;
}

void HideHl()
{
	sprites[0].x = 240;
	sprites[1].x = 240;
	sprites[2].x = 240;
	sprites[3].x = 240;
}

void HideGrab()
{
	sprites[4].x = 240;
	sprites[5].x = 240;
	sprites[6].x = 240;
	sprites[7].x = 240;
}

void HideHint()
{
	sprites[8].x = 240;
	showHint = 0;
}

void HideJewel(u8 x, u8 y)
{
	DrawMap2(11 + (x * 2), 6 + (y * 2), map_clear);
}

void DrawJewel(u8 x, u8 y, u8 halfStep)
{
	if(jewels[y][x] == 0)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_white);
	else if(jewels[y][x] == 1)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_purple);
	else if(jewels[y][x] == 2)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_green);
	else if(jewels[y][x] == 3)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_orange);
	else if(jewels[y][x] == 4)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_yellow);
	else if(jewels[y][x] == 5)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_blue);
	else if(jewels[y][x] == 6)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_red);
	else if(jewels[y][x] == 7)
		DrawMap2(11 + (x * 2), 6 + (y * 2) + halfStep, map_clear);
}

void DrawFlashJewel(u8 x, u8 y)
{
	if(jewels[y][x] == 0)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_white);
	else if(jewels[y][x] == 1)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_purple);
	else if(jewels[y][x] == 2)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_green);
	else if(jewels[y][x] == 3)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_orange);
	else if(jewels[y][x] == 4)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_yellow);
	else if(jewels[y][x] == 5)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_blue);
	else if(jewels[y][x] == 6)
		DrawMap2(11 + (x * 2), 6 + (y * 2), map_flash_red);
}

void HandleLevelUp()
{
	DrawMap2(13, 12, map_level_up);
	
	HideHl();
	HideGrab();
	
	// give them an extra hint
	hintsLeft++;
	DrawHints();
	
	int buttons;
	while(1)
	{
		WaitVsync(1);
		buttons = ReadJoypad(0);
		if(buttons & BTN_START)
		{
			SetHlXY(hlX, hlY);
			if(grabbing == 1) SetGrabXY(grabX, grabY);
			return;
		}
	}
}

void HandleGameOver()
{
	TriggerFx(8, 0xff, true);
	DrawMap2(13, 12, map_game_over);
	
	HideHl();
	HideGrab();
	
	// see if we got a new highscore or not
	nextMenuState = MENUSTATE_MAIN;
	u8 scoreRank = GetScoreRank(playerScore, playMode);
	if(scoreRank < 4)
		nextMenuState = MENUSTATE_NEWHIGHSCORE;
	
	gameOver = 1;
	int buttons;
	while(1)
	{
		WaitVsync(1);
		buttons = ReadJoypad(0);
		if(buttons & BTN_START)
			return;
	}
}

void HandlePause()
{
	DrawMap2(13, 10, map_pause);
	
	HideHl();
	HideGrab();
	
	u8 selector = 0;
	while(1)
	{
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
		
		// move the selecting
		if(padPressed[0] & BTN_DOWN && selector < 2)
			selector++;
		else if(padPressed[0] & BTN_UP && selector > 0)
			selector--;
			
		// check for music selection
		if(selector == 2 && padPressed[0] & BTN_RIGHT && musicOn == 1)
		{
			musicOn = 0;
			StopSong();
		}
		else if(selector == 2 && padPressed[0] & BTN_LEFT && musicOn == 0)
		{
			musicOn = 1;
			StartSong(song_gobby);
		}
		
		if(padPressed[0] & (BTN_UP | BTN_RIGHT | BTN_DOWN | BTN_LEFT))
		{
			// clear the selector
			SetTile(14, 13, MAP_DIALOG_PURPLE);
			SetTile(15, 14, MAP_DIALOG_PURPLE);
			SetTile(15, 16, MAP_DIALOG_PURPLE);
			SetTile(18, 16, MAP_DIALOG_PURPLE);
			
			// set the selector
			if(selector == 0)
				SetTile(14, 13, MAP_PAUSE_SELECT);
			else if(selector == 1)
				SetTile(15, 14, MAP_PAUSE_SELECT);
			else if(selector == 2)
			{
				if(musicOn == 1)
					SetTile(15, 16, MAP_PAUSE_SELECT);
				else
					SetTile(18, 16, MAP_PAUSE_SELECT);
			}
		}
		
		if(padPressed[0] & BTN_A && (selector == 0 || selector == 1))
		{
			for(u8 y = 0; y < 8; y++)
				for(u8 x = 0; x < 8; x++)
					DrawJewel(x, y, 0);
					
			if(selector == 1)
				HandleGameOver();
				
			SetHlXY(hlX, hlY);
			if(grabbing == 1) SetGrabXY(grabX, grabY);
			
			return;
		}
	}
}

u8 OnlyTopClear()
{
	u8 ret = 0;
	for(u8 y = 0; y < 8; y++)
	{
		for(u8 x = 0; x < 8; x++)
		{
			if(jewels[y][x] == 7)
			{
				if(y == 0)
					ret = 1;
				else
				{
					ret = 0;
					x = 8;
					y = 8;
				}
			}
		}
	}
	return ret;
}

void EnsureStart()
{
	u8 found = 0;

	// look in vertical direction first
	for(u8 x = 0; x < 8; x++)
	{
		// check each set
		for(u8 y = 2; y < 8; y++)
		{
			if(jewels[y - 2][x] == jewels[y - 1][x] && jewels[y - 1][x] == jewels[y][x])
			{
				// found a set
				found = 1;
				
				// replace a random gem
				s8 r = rand() % 3;
				if(r == 0)
					jewels[y - 2][x] = rand() % 7;
				else if(r == 1)
					jewels[y - 1][x] = rand() % 7;
				else
					jewels[y][x] = rand() % 7;
			}
		}
	}

	// look in horizontal direction next
	for(u8 y = 0; y < 8; y++)
	{
		// check each set
		for(u8 x = 2; x < 8; x++)
		{
			if(jewels[y][x - 2] == jewels[y][x - 1] && jewels[y][x - 1] == jewels[y][x])
			{
				// found a set
				found = 1;
				
				// replace a random gem
				s8 r = rand() % 3;
				if(r == 0)
					jewels[y][x - 2] = rand() % 7;
				else if(r == 1)
					jewels[y][x - 1] = rand() % 7;
				else
					jewels[y][x] = rand() % 7;
			}
		}
	}
	
	// keep iterating through the map till we're sure there's no 3-in-a-rows left
	if(found == 1)
		EnsureStart();
}

u8 AllowableSwap(u8 x1, u8 y1, u8 x2, u8 y2)
{
	// check the first gem first
	// check vertically first
	if(y1 >= 2 && jewels[y1 - 2][x1] == jewels[y1 - 1][x1] && jewels[y1 - 1][x1] == jewels[y1][x1])
		return 1; // top 3
	if(y1 >= 1 && y1 <= 6 && jewels[y1 - 1][x1] == jewels[y1][x1] && jewels[y1][x1] == jewels[y1 + 1][x1])
		return 1; // middle 3
	if(y1 <= 5 && jewels[y1][x1] == jewels[y1 + 1][x1] && jewels[y1 + 1][x1] == jewels[y1 + 2][x1])
		return 1; // bottom 3
	// check horizontally next
	if(x1 >= 2 && jewels[y1][x1 - 2] == jewels[y1][x1 - 1] && jewels[y1][x1 - 1] == jewels[y1][x1])
		return 1; // top 3
	if(x1 >= 1 && x1 <= 6 && jewels[y1][x1 - 1] == jewels[y1][x1] && jewels[y1][x1] == jewels[y1][x1 + 1])
		return 1; // middle 3
	if(x1 <= 5 && jewels[y1][x1] == jewels[y1][x1 + 1] && jewels[y1][x1 + 1] == jewels[y1][x1 + 2])
		return 1; // bottom 3
		
	// check the second gem now
	// check vertically first
	if(y2 >= 2 && jewels[y2 - 2][x2] == jewels[y2 - 1][x2] && jewels[y2 - 1][x2] == jewels[y2][x2])
		return 1; // top 3
	if(y2 >= 1 && y2 <= 6 && jewels[y2 - 1][x2] == jewels[y2][x2] && jewels[y2][x2] == jewels[y2 + 1][x2])
		return 1; // middle 3
	if(y2 <= 5 && jewels[y2][x2] == jewels[y2 + 1][x2] && jewels[y2 + 1][x2] == jewels[y2 + 2][x2])
		return 1; // bottom 3
	// check horizontally next
	if(x2 >= 2 && jewels[y2][x2 - 2] == jewels[y2][x2 - 1] && jewels[y2][x2 - 1] == jewels[y2][x2])
		return 1; // top 3
	if(x2 >= 1 && x2 <= 6 && jewels[y2][x2 - 1] == jewels[y2][x2] && jewels[y2][x2] == jewels[y2][x2 + 1])
		return 1; // middle 3
	if(x2 <= 5 && jewels[y2][x2] == jewels[y2][x2 + 1] && jewels[y2][x2 + 1] == jewels[y2][x2 + 2])
		return 1; // bottom 3
		
	return 0;
}

u8 TempAllowableSwap(u8 x1, u8 y1, u8 x2, u8 y2)
{
	// check the first gem first
	// check vertically first
	if(y1 >= 2 && tempJewels[y1 - 2][x1] == tempJewels[y1 - 1][x1] && tempJewels[y1 - 1][x1] == tempJewels[y1][x1])
		return 1; // top 3
	if(y1 >= 1 && y1 <= 6 && tempJewels[y1 - 1][x1] == tempJewels[y1][x1] && tempJewels[y1][x1] == tempJewels[y1 + 1][x1])
		return 1; // middle 3
	if(y1 <= 5 && tempJewels[y1][x1] == tempJewels[y1 + 1][x1] && tempJewels[y1 + 1][x1] == tempJewels[y1 + 2][x1])
		return 1; // bottom 3
	// check horizontally next
	if(x1 >= 2 && tempJewels[y1][x1 - 2] == tempJewels[y1][x1 - 1] && tempJewels[y1][x1 - 1] == tempJewels[y1][x1])
		return 1; // top 3
	if(x1 >= 1 && x1 <= 6 && tempJewels[y1][x1 - 1] == tempJewels[y1][x1] && tempJewels[y1][x1] == tempJewels[y1][x1 + 1])
		return 1; // middle 3
	if(x1 <= 5 && tempJewels[y1][x1] == tempJewels[y1][x1 + 1] && tempJewels[y1][x1 + 1] == tempJewels[y1][x1 + 2])
		return 1; // bottom 3
		
	// check the second gem now
	// check vertically first
	if(y2 >= 2 && tempJewels[y2 - 2][x2] == tempJewels[y2 - 1][x2] && tempJewels[y2 - 1][x2] == tempJewels[y2][x2])
		return 1; // top 3
	if(y2 >= 1 && y2 <= 6 && tempJewels[y2 - 1][x2] == tempJewels[y2][x2] && tempJewels[y2][x2] == tempJewels[y2 + 1][x2])
		return 1; // middle 3
	if(y2 <= 5 && tempJewels[y2][x2] == tempJewels[y2 + 1][x2] && tempJewels[y2 + 1][x2] == tempJewels[y2 + 2][x2])
		return 1; // bottom 3
	// check horizontally next
	if(x2 >= 2 && tempJewels[y2][x2 - 2] == tempJewels[y2][x2 - 1] && tempJewels[y2][x2 - 1] == tempJewels[y2][x2])
		return 1; // top 3
	if(x2 >= 1 && x2 <= 6 && tempJewels[y2][x2 - 1] == tempJewels[y2][x2] && tempJewels[y2][x2] == tempJewels[y2][x2 + 1])
		return 1; // middle 3
	if(x2 <= 5 && tempJewels[y2][x2] == tempJewels[y2][x2 + 1] && tempJewels[y2][x2 + 1] == tempJewels[y2][x2 + 2])
		return 1; // bottom 3
		
	return 0;
}

void SwapJewels(u8 x1, u8 y1, u8 x2, u8 y2)
{
	u8 jt = jewels[y1][x1];
	jewels[y1][x1] = jewels[y2][x2];
	jewels[y2][x2] = jt;
	DrawJewel(x1, y1, 0);
	DrawJewel(x2, y2, 0);
}

void SwapJewelsNoDraw(u8 x1, u8 y1, u8 x2, u8 y2)
{
	u8 jt = jewels[y1][x1];
	jewels[y1][x1] = jewels[y2][x2];
	jewels[y2][x2] = jt;
}

void SwapJewelsTemp(u8 x1, u8 y1, u8 x2, u8 y2)
{
	u8 jt = tempJewels[y1][x1];
	tempJewels[y1][x1] = tempJewels[y2][x2];
	tempJewels[y2][x2] = jt;
}

u8 CanFall()
{
	for(u8 y = 1; y < 8; y++)
		for(u8 x = 0; x < 8; x++)
			if(jewels[y][x] == 7)
				return 1;

	return 0;
}

u8 QueuedClears()
{
	u8 found = 0;

	// look in vertical direction first
	for(u8 x = 0; x < 8; x++)
	{
		// check each set
		for(u8 y = 2; y < 8; y++)
		{
			if(jewels[y - 2][x] == jewels[y - 1][x] && jewels[y - 1][x] == jewels[y][x])
			{
				// found a set
				found = 1;
				y = 8;
				x = 8;
			}
		}
	}

	// look in horizontal direction next
	for(u8 y = 0; y < 8; y++)
	{
		// check each set
		for(u8 x = 2; x < 8; x++)
		{
			if(jewels[y][x - 2] == jewels[y][x - 1] && jewels[y][x - 1] == jewels[y][x])
			{
				// found a set
				found = 1;
				y = 8;
				x = 8;
			}
		}
	}
	
	return found;
}

u8 PossibleMoves()
{
	// fill the temp jewel buffer
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x < 8; x++)
			tempJewels[y][x] = jewels[y][x];
			
	// now test each move..
	// vertical pairings first
	for(u8 x = 0; x < 8; x++)
	{
		for(u8 y = 0; y < 7; y++)
		{
			SwapJewelsTemp(x, y, x, y + 1);
			if(TempAllowableSwap(x, y, x, y + 1) > 0)
				return (((y * 8) + x) + 1);
			SwapJewelsTemp(x, y, x, y + 1);
		}
	}
	
	// now horizontal pairings
	for(u8 y = 0; y < 8; y++)
	{
		for(u8 x = 0; x < 7; x++)
		{
			SwapJewelsTemp(x, y, x + 1, y);
			if(TempAllowableSwap(x, y, x + 1, y) > 0)
				return (((y * 8) + x) + 1);
			SwapJewelsTemp(x, y, x + 1, y);
		}
	}
	
	return 0;
}

void InitJewels()
{
	// init the jewels
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x< 8; x++)
			jewels[y][x] = rand() % 7;
	
	// make sure we don't start with any 3-in-a-rows
	EnsureStart();
	
	// make sure we have a valid move to play
	if(PossibleMoves() == 0)
		InitJewels();
	
	// draw the jewels
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x< 8; x++)
			DrawJewel(x, y, 0);
}

u32 ClearAndDropGems()
{
	// wait to slow things down
	WaitVsync(1);
	
	// hide the hint
	HideHint();
	
	// trigger the clear FX
	TriggerFx(4, 0xff, true);
	
	// use a temporary buffer so that we can do t's and l's
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x < 8; x++)
			tempJewels[y][x] = 0;

	// first, find all gems that need to be cleared
	u8 numNumCleared[6] = { 0, 0, 0, 0, 0, 0 };
	for(u8 g = 0; g < 7; g++)
	{
		// check the horizontal directions first
		for(u8 y = 0; y < 8; y++)
		{
			u8 num = 0;
			for(u8 x = 0; x < 8; x++)
			{
				// count the number in a row
				if(jewels[y][x] == g)
					num++;
				else
				{
					// hit a different gem
					// see if we had 3 of the last ones
					if(num >= 3)
					{
						// we had them!
						for(u8 a = (x - num); a < x; a++)
						{
							/*jewels[y][a] = 7;
							DrawJewel(a, y, 0);*/
							tempJewels[y][a] = 1;
						}
						
						// increase the score counter
						numNumCleared[num - 3]++;
					}
					num = 0;
				}
			}
			
			// check for the last jewel
			if(num >= 3)
			{
				// we had them!
				for(u8 a = (8 - num); a < 8; a++)
				{
					/*jewels[y][a] = 7;
					DrawJewel(a, y, 0);*/
					tempJewels[y][a] = 1;
				}
						
				// increase the score counter
				numNumCleared[num - 3]++;
			}
		}
		
		// check the vertical directions now
		for(u8 x = 0; x < 8; x++)
		{
			u8 num = 0;
			for(u8 y = 0; y < 8; y++)
			{
				// count the number in a row
				if(jewels[y][x] == g)
					num++;
				else
				{
					// hit a different gem
					// see if we had 3 of the last ones
					if(num >= 3)
					{
						// we had them!
						for(u8 a = (y - num); a < y; a++)
						{
							/*jewels[a][x] = 7;
							DrawJewel(x, a, 0);*/
							tempJewels[a][x] = 1;
						}
						
						// increase the score counter
						numNumCleared[num - 3]++;
					}
					num = 0;
				}
			}
			
			// check for the last jewel
			if(num >= 3)
			{
				// we had them!
				for(u8 a = (8 - num); a < 8; a++)
				{
					/*jewels[a][x] = 7;
					DrawJewel(x, a, 0);*/
					tempJewels[a][x] = 1;
				}
						
				// increase the score counter
				numNumCleared[num - 3]++;
			}
		}
	}
	
	// flash the jewels to be cleared
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x < 8; x++)
			if(tempJewels[y][x] == 1)
				DrawFlashJewel(x, y);
	
	WaitVsync(5);
	
	// set the jewels buffer
	for(u8 y = 0; y < 8; y++)
	{
		for(u8 x = 0; x < 8; x++)
		{
			if(tempJewels[y][x] == 1)
			{
				jewels[y][x] = 7;
				DrawJewel(x, y, 0);
			}
		}
	}
		
	// calculate the score
	static u8 combo = 0;
	u32 score = 0;
	u32 combomod = 0;
	for(u8 i = 0; i < 6; i++)
	{
		for(u8 j = 0; j < numNumCleared[i]; j++)
		{
			combo++;
			if(combo == 1)
				combomod = 0;
			else if(combo == 2)
				combomod = 10;
			else if(combo == 3)
				combomod = 20;
			else if(combo == 4)
				combomod = 30;
			else if(combo == 5)
				combomod = 40;
			else if(combo == 6)
				combomod = 70;
			else if(combo == 7)
				combomod = 100;
			else if(combo == 8)
				combomod = 150;
			else
				combomod = 200;
				
			score += (((i + 1) * 10) + combomod);
			timer += ((i + 1) + (combomod / 10)) * 36000;
		}
	}
	score *= level;
	
	// ok, so now we have gems to drop!
	// wait to slow things down
	WaitVsync(5);
	
	while(CanFall() > 0)
	{
		for(s8 y = 6; y >= 0; y--)
		{
			// check for moving down
			for(u8 x = 0; x < 8; x++)
			{
				if(jewels[y + 1][x] == 7)
				{
					// move the jewel down
					HideJewel(x, y);
					HideJewel(x, y + 1);
					DrawJewel(x, y, 1);
					SwapJewelsNoDraw(x, y, x, y + 1);
					WaitVsync(1);
					HideJewel(x, y);
					DrawJewel(x, y + 1, 0);
				}
			}
		}
			
		// now check for an empty top row
		for(u8 x = 0; x < 8; x++)
		{
			if(jewels[0][x] == 7)
			{
				jewels[0][x] = rand() % 7;
				DrawJewel(x, 0, 0);
			}
		}
	}
	
	if(QueuedClears() > 0)
	{
		// we have gems awaiting clearance!
		// clear em!
		WaitVsync(5);
		if(OnlyTopClear())
		{
			for(u8 x = 0; x < 8; x++)
			{
				if(jewels[0][x] == 7)
				{
					jewels[0][x] = rand() % 7;
					DrawJewel(x, 0, 0);
				}
			}
		}
		WaitVsync(5);
		score += ClearAndDropGems();
	}
		
	// clear the combo
	combo = 0;
	
	return score;
}

void NextLevel()
{
	// trigger the level fx
	TriggerFx(7, 0xff, true);
	
	// calculate the next level score
	level++;
	DrawLevel();
	if(playMode == MODE_CLASSIC)
	{
		lastScoreLevel = nextScoreLevel;
		nextScoreLevel = 500 * level * level;
	}
	else if(playMode == MODE_TIMED)
	{
		timer = 1000000;
		if(level == 1)
			timerRate = 185;
		else if(level == 2)
			timerRate = 222;
		else if(level == 3)
			timerRate = 277;
		else if(level == 4)
			timerRate = 370;
		else if(level == 5)
			timerRate = 555;
		else
			timerRate = 1111;
	}
	
	// handle the level up
	HandleLevelUp();
	
	// flash the gems
	for(u8 y = 0; y < 8; y++)
		for(u8 x = 0; x < 8; x++)
			DrawFlashJewel(x, y);
	
	WaitVsync(5);
	
	// clear the gems
	for(u8 y = 0; y < 8; y++)
	{
		for(u8 x = 0; x < 8; x++)
		{
			jewels[y][x] = 7;
			DrawJewel(x, y, 0);
		}
	}
	
	WaitVsync(20);

	InitJewels();
	HideGrab();
}

void InitGame()
{
	SetTileTable(tiles_game);
	SetSpritesTileTable(tiles_hl);
	DrawMap2(0, 0, map_screen);
	Fill(0, 24, 22, 4, 0);
	
	InitJewels();
	
	// setup the sprites
	sprites[0].tileIndex = 0;
	sprites[1].tileIndex = 1;
	sprites[2].tileIndex = 2;
	sprites[3].tileIndex = 3;
	sprites[4].tileIndex = 4;
	sprites[5].tileIndex = 5;
	sprites[6].tileIndex = 6;
	sprites[7].tileIndex = 7;
	sprites[8].tileIndex = 8;
	
	// reset the variables
	playerScore = 0;
	level = 1;
	lastScoreLevel = 0;
	nextScoreLevel = 500;
	frameCount = 0;
	lastCount = 0;
	hlX = 0;
	hlY = 0;
	timer = 1000000;
	timerRate = 185;
	if(playMode == MODE_CLASSIC)
		hintsLeft = 3;
	else
		hintsLeft = 0;
	
	// do the overlay sprites
	SetHlXY(0, 0);
	HideGrab();
	HideHint();
	
	// draw the score stuff
	DrawScore();
	DrawHighScore();
	DrawLevel();
	DrawHints();
	
	// fade back in
	FadeIn(1, true);
}

void DoGame()
{
	// game over
	if(gameOver == 1)
	{
		nextState = STATE_MENU;
		gameOver = 0;
		HideHl();
		HideGrab();
		HideHint();
		return;
	}

	// check for paused
	if(padPressed[0] & BTN_START)
		HandlePause();
		
	// check for hint
	if(padPressed[0] & BTN_SELECT)
	{
		if(playMode == MODE_CLASSIC && hintsLeft > 0)
		{
			u8 ndx = PossibleMoves() - 1;
			SetHintXY(ndx % 8, ndx / 8);
			hintsLeft--;
			DrawHints();
		}
		else if(playMode == MODE_TIMED)
		{
			u8 ndx = PossibleMoves() - 1;
			SetHintXY(ndx % 8, ndx / 8);
			timer -= timerRate * 60 * 10; // remove 10 seconds from the clock!
			DrawBar(timer, 2000000);
			hintsLeft++;
			DrawHints();
		}
	}
	
	// decrement the timer
	if(playMode == MODE_TIMED)
	{
		timer -= timerRate;
		DrawBar(timer, 2000000);
	}

	// move the highlight around
	// if we're holding the buttons down for more than 1/6 of a second, scroll them
	if(movingHl && frameCount - lastCount >= 10)
	{
		// check the d-pad
		if(padHeld[0] & BTN_LEFT && hlX > 0)
			hlX--;
		if(padHeld[0] & BTN_RIGHT && hlX < 7)
			hlX++;
		if(padHeld[0] & BTN_UP && hlY > 0)
			hlY--;
		if(padHeld[0] & BTN_DOWN && hlY < 7)
			hlY++;
			
		// if we are still holding down, update the hl
		if(padHeld[0] & (BTN_DOWN | BTN_UP | BTN_RIGHT | BTN_LEFT))
		{
			SetHlXY(hlX, hlY);
			TriggerFx(6, 0xff, true);
			ClearPoints();
		}
		// no long holding down, don't move the HL anymore!
		else
			movingHl = 0;
		
		lastCount = frameCount;
	}
	// check for initiation of the hl
	else if(!movingHl)
	{
		// check D-pad
		if(padHeld[0] & BTN_LEFT && hlX > 0)
			hlX--;
		if(padHeld[0] & BTN_RIGHT && hlX < 7)
			hlX++;
		if(padHeld[0] & BTN_UP && hlY > 0)
			hlY--;
		if(padHeld[0] & BTN_DOWN && hlY < 7)
			hlY++;
		// if we hit the d-pad
		if(padHeld[0] & (BTN_DOWN | BTN_UP | BTN_RIGHT | BTN_LEFT))
		{
			// update things
			SetHlXY(hlX, hlY);
			movingHl = 1;
			lastCount = frameCount;
			TriggerFx(6, 0xff, true);
			ClearPoints();
		}
	}
	
	// check to see if we were grabbing and tried to move
	if(grabbing == 1 && (hlX != grabX || hlY != grabY))
	{
		// swap the gems
		SwapJewels(hlX, hlY, grabX, grabY);
		
		// check to see if we tried an invalid swap
		if(AllowableSwap(hlX, hlY, grabX, grabY) == 0)
		{
			TriggerFx(5, 0xff, true);
		
			// wait for a bit
			WaitVsync(10);
			
			// swap the jewels back
			SwapJewels(hlX, hlY, grabX, grabY);
			
			// set the highlight
			hlX = grabX;
			hlY = grabY;
			
			SetHlXY(hlX, hlY);
		}
		else
		{
			// we made an allowable move, now clear those gems!
			u32 points = ClearAndDropGems();
			DrawPoints(points);
			playerScore += points;
			DrawScore();
			if(playMode == MODE_CLASSIC)
			{
				if(playerScore > highScoreClassic)
				{
					highScoreClassic = playerScore;
					DrawHighScore();
				}
			}
			else
			{
				if(playerScore > highScoreTimed)
				{
					highScoreTimed = playerScore;
					DrawHighScore();
				}
			}
			
			// check for game over
			if(PossibleMoves() == 0)
			{
				if(playMode == MODE_CLASSIC)
				{
					// in regular mode, quit
					HandleGameOver();
				}
				else
				{
					// in timed mode, recreate the board
					// flash the gems
					for(u8 y = 0; y < 8; y++)
						for(u8 x = 0; x < 8; x++)
							DrawFlashJewel(x, y);
					
					WaitVsync(5);
					InitJewels();
				}
			}
			
			// check for new level
			if(playMode == MODE_CLASSIC)
			{
				if(playerScore >= nextScoreLevel)
					NextLevel();
									
				// update the bar
				DrawBar(playerScore - lastScoreLevel, nextScoreLevel - lastScoreLevel);
			}
			else if(playMode == MODE_TIMED)
			{
				if(timer >= 2000000)
					NextLevel();
			
				// update the bar
				DrawBar(timer, 2000000);
			}
				
		}
		
		HideGrab();
		grabbing = 0;
	}
	
	// check to see if we want to start swapping
	if(grabbing == 0 && (padPressed[0] & BTN_A))
	{
		SetGrabXY(hlX, hlY);
		grabX = hlX;
		grabY = hlY;
		grabbing = 1;
	}
	else if(grabbing == 1 && (padPressed[0] & (BTN_A | BTN_B)))
	{
		grabbing = 0;
		HideGrab();
	}
			
	// check for time out
	if(playMode == MODE_TIMED && timer <= 0)
	{
		HandleGameOver();
	}
	
	// update frame count
	frameCount++;
}