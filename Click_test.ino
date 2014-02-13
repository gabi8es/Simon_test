/*
  Simon_test.ino - Test code to the Simon says project.
  Created by Gabriel Pallares, January, 2014.
  Released into the public domain.
*/
// 

//***********************************************************************
//					DEFINES
//***********************************************************************


#define ledPin 7


//BUTON INPUTS
#define buttonPin 5

int val, state, lastButtonPress;
int pressed = 0;

void setup() {

	pinMode(ledPin, OUTPUT); 	
	pinMode(buttonPin, INPUT); 
    digitalWrite(buttonPin, 1);
	Serial.begin(9600);	
	state = LOW;
	digitalWrite(ledPin, HIGH);
	delay(1000);
	digitalWrite(ledPin, LOW);
	delay(500);
	digitalWrite(ledPin, HIGH);
	delay(1000);
	digitalWrite(ledPin, LOW);
	lastButtonPress = millis();
}


// Main loop. Update menu, game or game over depending on current state.
void loop() {

	val = digitalRead(buttonPin);
	if ((val != HIGH) && (!pressed))
	{
		if (millis()-lastButtonPress > 100)
		{
                        pressed = 1;
			Serial.write("Click\n");
			if (state == LOW)
			{
				state = HIGH;
				Serial.write("Estado Encendido\n");
			}
			else
			{
				state = LOW;
				Serial.write("Estado apagado\n");
			}
			lastButtonPress = millis();
		}
		else
		{
			Serial.write("Click descartado\n");
		}
	}
        else
        {
          if(val == HIGH)
          {
            pressed = 0;
          }
        }
	digitalWrite(ledPin, state);
	delay(100);
}

