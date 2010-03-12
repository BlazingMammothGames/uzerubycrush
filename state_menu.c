// the menu states
#define MENUSTATE_MAIN			(0)
#define MENUSTATE_HISCORES		(1)
char menuState;
char nextMenuState;

// main menu selections
#define MENUOPT_CLASSIC		(0)
#define MENUOPT_TIMED		(1)
#define MENUOPT_MUSIC		(2)
#define MENUOPT_HISCORES	(3)
char currentOpt = 0;

void InitMenu_Main()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(10, "Ruby Crush!");
	
	SetTile(8, 12 + currentOpt, 127);
	
	PrintStr(10, 12, "Play Classic");
	PrintStr(10, 13, "Play Timed");
	PrintStr(10, 14, "Music (off)");
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
	
	//|    classic         timed     |\\ 
	//|  KDH 9999999    KDH 9999999  |\\
	PrintStrCenter(10, "High Scores");
	PrintStr(4, 12, "Classic");
	PrintStr(19, 12, "Timed");
	
	u8 i1, i2, i3;
	u32 score;
	s8 buffer[8];
	for(u8 i = 0; i < 3; i++)
	{
		GetHighScore(i, &i1, &i2, &i3, &score);
		sprintf(buffer, "%c%c%c", 'A' + (s8)i1, 'A' + (s8)i2, 'A' + (s8)i3);
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
		sprintf(buffer, "%c%c%c", 'A' + (s8)i1, 'A' + (s8)i2, 'A' + (s8)i3);
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
	if((padPressed[0] | padPressed[1]) & BTN_B)
		nextMenuState = MENUSTATE_MAIN;
}

void InitMenu()
{
	// init the text
	InitText();
	
	// setup the default menu
	nextMenuState = MENUSTATE_MAIN;
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
		
		menuState = nextMenuState;
		nextMenuState = -1;
	}
	
	if(menuState == MENUSTATE_MAIN)
		DoMenu_Main();
	else if(menuState == MENUSTATE_HISCORES)
		DoMenu_HiScores();
}