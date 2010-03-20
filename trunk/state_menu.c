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

void InitMenu_Main()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(10, "Ruby Crush!");
	
	SetTile(8, 12 + currentOpt, 127);
	
	PrintStr(10, 12, "Play Classic");
	PrintStr(10, 13, "Play Timed");
	PrintStr(10, 14, "Music");
	if(!musicOn)
		PrintStr(16, 14, "(Off)");
	else
		PrintStr(16, 14, "(On) ");
	PrintStr(10, 15, "High Scores");
	
	// fade back in
	FadeIn(1, true);
}

void DoMenu_Main()
{	
	// move the selector
	if((padPressed[0] | padPressed[1]) & BTN_DOWN && currentOpt < 3)
	{
		//TriggerFx(4, 0xFF, true);
		SetTile(8, 12 + currentOpt, ' ');
		currentOpt++;
		SetTile(8, 12 + currentOpt, 127);
	}
	if((padPressed[0] | padPressed[1]) & BTN_UP && currentOpt > 0)
	{
		//TriggerFx(4, 0xFF, true);
		SetTile(8, 12 + currentOpt, ' ');
		currentOpt--;
		SetTile(8, 12 + currentOpt, 127);
	}
	
	// take the selection input
	if((padPressed[0] | padPressed[1]) & BTN_A)
	{
		//TriggerFx(5, 0xFF, true);
		
		if(currentOpt == MENUOPT_CLASSIC)
		{
			playMode = MODE_CLASSIC;
			nextState = STATE_GAME;
		}
		else if(currentOpt == MENUOPT_TIMED)
		{
			playMode = MODE_TIMED;
			nextState = STATE_GAME;
		}
		else if(currentOpt == MENUOPT_MUSIC)
		{
			// toggle the music
			musicOn = 1 - musicOn;
			
			// draw the music indicator
			if(!musicOn)
			{
				StopSong();
				PrintStr(16, 14, "(Off)");
			}
			else
			{
				StartSong(song_gobby);
				PrintStr(16, 14, "(On) ");
			}
		}
		else if(currentOpt == MENUOPT_HISCORES)
			nextMenuState = MENUSTATE_HISCORES;
	}
}

void InitMenu_HiScores()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	//|          High Scores         |\\ 
	//|    classic         timed     |\\ 
	//|  KDH 9999999    KDH 9999999  |\\
	PrintStr(0, 0, " ");
	PrintStr(10, 10, "High Scores");
	PrintStr(4, 12, "Classic");
	PrintStr(19, 12, "Timed");
	
	u8 i1, i2, i3;
	u32 score;
	char buffer[8];
	for(u8 i = 0; i < 3; i++)
	{
		GetHighScore(i, &i1, &i2, &i3, &score);
		sprintf(buffer, "%c%c%c", 'A' + (char)i1, 'A' + (char)i2, 'A' + (char)i3);
		PrintStr(2, 13 + i, buffer);
		/*PrintStr(2, 13 + i, "A");
		PrintStr(3, 13 + i, "A");
		PrintStr(4, 13 + i, "A");*/
		sprintf(buffer, "%7lu", score);
		PrintStr(6, 13 + i, buffer);
	}
	for(u8 i = 0; i < 3; i++)
	{
		GetHighScore(i + 3, &i1, &i2, &i3, &score);
		sprintf(buffer, "%c%c%c", 'A' + (char)i1, 'A' + (char)i2, 'A' + (char)i3);
		PrintStr(17, 13 + i, buffer);
		/*PrintStr(17, 13 + i, "A");
		PrintStr(18, 13 + i, "A");
		PrintStr(19, 13 + i, "A");*/
		sprintf(buffer, "%7lu", score);
		PrintStr(21, 13 + i, buffer);
	}
	
	// fade back in
	FadeIn(1, true);
}

void DoMenu_HiScores()
{
	if((padPressed[0] | padPressed[1]) & (BTN_B | BTN_START))
		nextMenuState = MENUSTATE_MAIN;
}

u8 ni[3];
u8 iSel;

void InitMenu_NewHiScore()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(10, "New High Score!");
	PrintStrCenter(11, "Enter your initials:");
	
	PrintStr(13, 13, "AAA");
	SetTile(13, 14, 13);
	
	iSel = 0;
	ni[0] = 0;
	ni[1] = 0;
	ni[2] = 0;
	
	// fade back in
	FadeIn(1, true);
}

void DoMenu_NewHiScore()
{
	if(iSel < 2 && padPressed[0] & (BTN_RIGHT | BTN_A))
		iSel++;
	else if(iSel > 0 && padPressed[0] & BTN_LEFT)
		iSel--;
	
	if(padPressed[0] & BTN_UP)
	{
		if(ni[iSel] > 0)
			ni[iSel]--;
		else
			ni[iSel] = 25;
	}
	if(padPressed[0] & BTN_DOWN)
	{
		if(ni[iSel] < 25)
			ni[iSel]++;
		else
			ni[iSel] = 0;
	}
	
	if(padPressed[0] & (BTN_UP | BTN_RIGHT | BTN_DOWN | BTN_LEFT))
	{
		Fill(13, 13, 3, 2, ' ');
		SetTile(13, 13, 'A' + ni[0]);
		SetTile(14, 13, 'A' + ni[1]);
		SetTile(15, 13, 'A' + ni[2]);
		SetTile(13 + iSel, 14, 13);
	}
	
	if(padPressed[0] & BTN_START)
	{
		NewHighScore(ni[0], ni[1], ni[2], playerScore, playMode);
		nextMenuState = MENUSTATE_HISCORES;
	}
}

void InitMenu()
{
	// init the text
	InitText();
	
	// setup the default menu
	//nextMenuState = MENUSTATE_MAIN;
}

void DoMenu()
{
	// set the new menu
	if(nextMenuState > -1)
	{
		// fade out
		FadeOut(1, true);
	
		if(nextMenuState == MENUSTATE_MAIN)
			InitMenu_Main();
		else if(nextMenuState == MENUSTATE_HISCORES)
			InitMenu_HiScores();
		else if(nextMenuState == MENUSTATE_NEWHIGHSCORE)
			InitMenu_NewHiScore();
		
		menuState = nextMenuState;
		nextMenuState = -1;
	}
	
	if(menuState == MENUSTATE_MAIN)
		DoMenu_Main();
	else if(menuState == MENUSTATE_HISCORES)
		DoMenu_HiScores();
	else if(menuState == MENUSTATE_NEWHIGHSCORE)
		DoMenu_NewHiScore();
}