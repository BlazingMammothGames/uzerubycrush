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
