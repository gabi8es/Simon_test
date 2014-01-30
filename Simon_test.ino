/*
  Simon_test.ino - Test code to the Simon says project.
  Created by Gabriel Pallares, January, 2014.
  Released into the public domain.
*/
// 
// Serial_Comunication.ino
// LCD conected to Analog pins 4(SDA) and 5(SLC)
// LEDS connected to Digital pins:
//		-	RED 7
//		-	GREEN 6
//		-	YELLOW 5
//		-	BLUE 4

// include the library code:
#include "SoftwareSerial.h"
#include <string.h>
#include <Wire.h>
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include "DHT.h"  //Añadimos la libreria con la cual trabaja nuestro sensor
#include "RTClib.h"


//***********************************************************************
//					DEFINES
//***********************************************************************
//LEDS INPUTS
#define numLeds 4

#define redLed 7
#define greenLed 6
#define yellowLed 5
#define blueLed 4


//BUTON INPUTS
#define redButton 10
#define greenButton 11
#define yellowButton 12
#define blueButton 13

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
};

//***********************************************************************
//					VARIABLES
//***********************************************************************
// 0 - RED
// 1 - GREEEN
// 2 - BLUE
// 3 - YELLOW

// C runtime variables
// -------------------
extern unsigned int __bss_end;
extern unsigned int __heap_start;
extern void *__brkval;

const int leds[] = {redLed,greenLed,yellowLed,blueLed };
const int buttons[] = {redButton, greenButton, yellowButton, blueButton};

// initialize the library with the numbers of the interface pins
LiquidCrystal_I2C lcd(0x20, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE);  // Set the LCD I2C address

int state = STATE_START_MENU;
int level = 0;
int longitude = initLongitude;


void setup() {
	Serial.begin(9600);
  	lcd.begin(16,2);
  	lcd.clear();
  	lcd.setCursor(0,0);
  	lcd.print("MAYTE SAYS!!!");
    lcd.setCursor(0,1);
    lcd.print("Nivel: 0");	
	randomSeed(analogRead(0));
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
 // readCombination();
  if (state = STATE_GAME)
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
    lcd.setCursor(0,1);
    lcd.print("Nivel: "); lcd.print(level);
	//Flash all leds 5 times
	for (int led=0;led<numLeds;led++)
	{
		digitalWrite(leds[led], LOW); 
	}
	for (led=0;led<longitude;led++)
	{
		digitalWrite(leds[combination[led]], HIGH);
		delay(500); 
		digitalWrite(leds[combination[led]], LOW);
		delay(500);
	}
	for (led=0;led < 3; led++)
	{
	 	flashLeds(1);
	}		
}
void showCombination_serial(int *combination, int longitude)
{
	int led = 0;

	//Flash all leds 5 times
  Serial.write("Free memory: ");
  Serial.println(freeMemory());
        Serial.write("Combinacion a mostrar: ");
	for (led=0;led<longitude;led++)
	{
		if (led > 0)
		{
			Serial.write(", ");
		}
		Serial.print(leds[combination[led]]);
	}
	Serial.write("\n");		
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

void testGame()
{
 int i = 0;
 int generado;

  if ((level !=0) && (!(level % diffucultyGranurality))&&(longitude<=10))
  {
  	longitude++;
  }

  int *combination = (int*) malloc(sizeof(int) * longitude);
  Serial.write("Combinacion generada: ");
  for (i=0; i<longitude;i++)
  {
        if (i>0)
        {
          Serial.write(",");
        }
        generado =  random(numLeds);
  	combination[i] = generado;
        Serial.print(generado);
  }
  Serial.write("\n");
  showCombination(combination,longitude);
  //showCombination_serial(combination,longitude);
  //readCombination();
 //  if (stat = STATE_GAME)
 //  {
	//   delay(2000);
	//   if (level==maxLevel)
	//   {
	//   	  for (i=0; i<10;i++)
	//   	  {
	//   	  	flashLeds(2);
	//   	  }
	//   	  state = STATE_GAME_OVER;
	//   }
	//   else
	//   {
	//   	  level++;
	//   }
	// }
  free(combination);
  level++;

}

// Prepares game state for a new game.
void startNewGame() {
  state = STATE_GAME;
  level = 0;
  // set random seed, so that every game has a different sequence
  randomSeed(millis());
}

/*!
 @function   freeMemory
 @abstract   Return available RAM memory
 @discussion This routine returns the ammount of RAM memory available after
 initialising the C runtime.
 @param      
 @return     Free RAM available.
 */
static int freeMemory ( void ) 
{
   int free_memory;
   
   if((int)__brkval == 0)
   free_memory = ((int)&free_memory) - ((int)&__bss_end);
   else
   free_memory = ((int)&free_memory) - ((int)__brkval);
   
   return free_memory;
}

// Main loop. Update menu, game or game over depending on current state.
void loop() {
  // if(state == STATE_START_MENU)
  //   startMenu();
  // else if(state == STATE_GAME)
  //   playGame();
  // else
  //   gameOver();
  testGame();
  Serial.write("Free memory: ");
  Serial.println(freeMemory());
  delay(3000);
}

