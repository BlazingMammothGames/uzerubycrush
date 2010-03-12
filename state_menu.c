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
	
	PrintStrCenter(10, "High Scores");
	
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