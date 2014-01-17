// Simon_test.ino

//***********************************************************************
//					DEFINES
//***********************************************************************
//LEDS INPUTS
#define numLeds 4

#define redLed 0
#define greenLed 1
#define yellowLed 2
#define blueLed 3


//BUTON INPUTS
#define redButton 4
#define greenButton 5
#define yellowButton 6
#define blueButton 7

//CONFIGURATION
#define diffucultyGranurality 4
#define initLongitude 3
#define diffultyLongIncrement 1
#define maxLevel 10

//***********************************************************************
//					TYPES
//***********************************************************************
enum {
  STATE_START_MENU,
  STATE_GAME,
  STATE_GAME_OVER
};
enum{
	MUSIC_START_GAME,
	MUSIC_PLAYING_GAME,
	MUSIC_WIN_GAME,
	MUSIC_LOST_GAME
}

//***********************************************************************
//					VARIABLES
//***********************************************************************
// 0 - RED
// 1 - GREEEN
// 2 - BLUE
// 3 - YELLOW
const int leds[] = { redLed, greenLed, yellowLed, blueLed };
const int buttons[] = {redButton, greenButton, yellowButton, blueButton};

int state = STATE_START_MENU;
int level = 0;
int longitude = initLongitude;


void setup() {

	//Set all led pins in output mode
	for (int i=0; i<numLeds; i++)
	{
		pinMode(leds[i], OUTPUT); 	
	}
	//Set all buttons pins in input mode
	for (int i=0; i<numLeds; i++)
	{
		pinMode(buttons[i], INPUT); 	
	}
}

void startMenu()
{

}

void playGame()
{
  int i = 0;

  if ((level !=0) && (level % diffucultyGranurality))
  {
  	longitude++;
  }

  int *combination = (int *)malloc(sizeof(int) * longitude);

  for (i=0; i<longitude;i++)
  {
  	combination[i] = random(numLeds);
  }
  showCombination(combination,longitude);
  readCombination();
  if (stat = STATE_GAME)
  {
	  delay(2000);
	  if (level==maxLevel)
	  {
	  	  for (i=0; i<10;i++)
	  	  {
	  	  	flashLeds(2);
	  	  }
	  	  state = STATE_GAME_OVER;
	  }
	  else
	  {
	  	  level++;
	  }
	}
  free(combination);
}

void showCombination(int *combination, int longitude)
{
	int led = 0;

	//Flash all leds 5 times
	for (int led=0;led<numLeds;led++)
	{
		digitalWrite(leds[led], LOW); 
	}
	for (led=0;led<longitude;led++)
	{
		digitalWrite(leds[combination[led]], HIGH);
		delay(1000); 
		digitalWrite(leds[combination[led]], LOW);
	}
	for (led=0;led < 3; led++)
	{
		flashLeds(1);
	}		
}

void flashLeds(int segs)
{
	int led = 0;

	//Flash all leds 5 times
	for (led=0;led<numLeds;led++)
	{
			digitalWrite(leds[led], LOW); 
	}
	for (led=0;led<numLeds;led++)
	{
		digitalWrite(leds[led], HIGH); 
	}
	delay(1000 * segs);
	for (led=0;led<numLeds;led++)
	{
		digitalWrite(leds[led], LOW); 
	}		
}

void gameOver()
{
	//Flash all leds 5 times
	for (int i=0; i<5; i++)
	{
		flashLeds(2);
	}
}


// Prepares game state for a new game.
void startNewGame() {
  state = STATE_GAME;
  level = 0;
  // set random seed, so that every game has a different sequence
  randomSeed(millis());
}

// Main loop. Update menu, game or game over depending on current state.
void loop() {
  if(state == STATE_START_MENU)
    startMenu();
  else if(state == STATE_GAME)
    playGame();
  else
    gameOver();
}

