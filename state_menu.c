// the menu states
#define MENUSTATE_MAIN			(0)
#define MENUSTATE_HOWTOPLAY		(1)
#define MENUSTATE_CREDITS		(2)
char menuState;
char nextMenuState;

// main menu selections
#define MENUOPT_CLASSIC		(0)
#define MENUOPT_TIMED		(1)
#define MENUOPT_MUSIC		(2)
#define MENUOPT_HOW			(3)
#define MENUOPT_CREDITS		(4)
char currentOpt = 0;

void InitMenu_Main()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(10, "Ruby Crush!");
	
	SetTile(8, 12 + currentOpt, 127);
	
	PrintStr(10, 12, "Play Classic");
	PrintStr(10, 13, "Play Timed");
	PrintStr(10, 14, "Music (on)");
	PrintStr(10, 15, "How To Play");
	PrintStr(10, 16, "Credits");
	
	// fade back in
	FadeIn(1, true);
}

void InitMenu_How()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(1, "How To Play");
	
	//             ".#.#.#.#.#.#.#.#.#.#.#.#.#.#.#"
	PrintStr(0, 3, "The goal of the game is to");
	PrintStr(0, 4, "swap two gems that are next to");
	PrintStr(0, 5, "each other and create a match");
	PrintStr(0, 6, "of three or more similar gems.");
	PrintStr(0, 7, "You can only swap gems that");
	PrintStr(0, 8, "will result in a match.");
	
	//              ".#.#.#.#.#.#.#.#.#.#.#.#.#.#.#"
	PrintStr(0, 10,  "As you make matches, the bar");
	PrintStr(0, 11, "at the bottom of the screen");
	PrintStr(0, 12, "starts to fill up. When the");
	PrintStr(0, 13, "bar is completely full, you");
	PrintStr(0, 14, "will progress on to the next");
	PrintStr(0, 15, "level. When there are no more");
	PrintStr(0, 16, "possible moves on the screen,");
	PrintStr(0, 17, "the game ends.   ");
	
	PrintStrCenter(26, "Press B to return");
	
	// fade back in
	FadeIn(1, true);
}

void InitMenu_Credits()
{
	// fill the bg
	Fill(0, 0, 30, 28, ' ');
	
	PrintStrCenter(1, "Credits");
	
	//                ".#.#.#.#.#.#.#.#.#.#.#.#.#.#.#"
	PrintStrCenter(3, "This is merely a port of");
	PrintStrCenter(4, "Bejeweled to the Uzebox. I am");
	PrintStrCenter(5, "NOT the original creator of");
	PrintStrCenter(6, "this game - PopCap is. All");
	PrintStrCenter(7, "rights belong to them.");
	
	PrintStr(1, 9, "Programming:");
	PrintStrCenter(10, "Kenton Hamaluik");
	PrintStr(1, 12, "Graphics:");
	PrintStrCenter(13, "Kenton Hamaluik");
	PrintStr(1, 15, "Music & SFX:");
	PrintStrCenter(16, "Kenton Hamaluik");
	
	PrintStrCenter(26, "Press B to return");
	
	// fade back in
	FadeIn(1, true);
}

void DoMenu_Main()
{	
	// move the selector
	if((padPressed[0] | padPressed[1]) & BTN_DOWN && currentOpt < 4)
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
			playMode = 0;
			nextState = STATE_GAME;
		}
		else if(currentOpt == MENUOPT_TIMED)
		{
			playMode = 1;
			nextState = STATE_GAME;
		}
		else if(currentOpt == MENUOPT_MUSIC)
		{
			// toggle the music
			musicOn = 1 - musicOn;
			
			// draw the music indicator
			if(!musicOn)
			{
				//StopSong();
				PrintStr(16, 14, "(Off)");
			}
			else
			{
				//StartSong(song_finalfantasy);
				PrintStr(16, 14, "(On) ");
			}
		}
		else if(currentOpt == MENUOPT_HOW)
			nextMenuState = MENUSTATE_HOWTOPLAY;
		else if(currentOpt == MENUOPT_CREDITS)
			nextMenuState = MENUSTATE_CREDITS;
	}
}

void DoMenu_How()
{
	if((padPressed[0] | padPressed[1]) & BTN_B)
		nextMenuState = MENUSTATE_MAIN;
}

void DoMenu_Credits()
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
		else if(nextMenuState == MENUSTATE_HOWTOPLAY)
			InitMenu_How();
		else if(nextMenuState == MENUSTATE_CREDITS)
			InitMenu_Credits();
		
		menuState = nextMenuState;
		nextMenuState = -1;
	}
	
	if(menuState == MENUSTATE_MAIN)
		DoMenu_Main();
	else if(menuState == MENUSTATE_HOWTOPLAY)
		DoMenu_How();
	else if(menuState == MENUSTATE_CREDITS)
		DoMenu_Credits();
}