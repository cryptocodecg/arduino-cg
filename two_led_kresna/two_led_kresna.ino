float pressLength_milliSeconds = 0;
// Define the *minimum* length of time, in milli-seconds, that the button must be pressed for a particular option to occur
int optionOne_milliSeconds = 100;
int optionTwo_milliSeconds = 2000;
//The Pin your button is attached to 
int buttonPin = 2;
//Pin your LEDs are attached to 
int ledPin_Option_1 = 13;
int ledPin_Option_2 = 12;

void setup(){
// Initialize the pushbutton pin as an input pullup
// Keep in mind, when pin 2 has ground voltage applied, we know the button is being pressed
pinMode(buttonPin, INPUT_PULLUP);

//set the LEDs pins as outputs 
pinMode(ledPin_Option_1, OUTPUT); 
pinMode(ledPin_Option_2, OUTPUT);

//Start serial communication - for debugging purposes only 
Serial.begin(9600);
} // close setup

void loop() {
//Record *roughly* the tenths of seconds the button in being held down 
while (digitalRead(buttonPin) == LOW ){
  
delay(100); 

//if you want more resolution, lower this number 
pressLength_milliSeconds = pressLength_milliSeconds + 100;

//display how long button is has been held 
Serial.print("ms = "); 
Serial.println(pressLength_milliSeconds);

  }//close while
  
  if (pressLength_milliSeconds >= optionTwo_milliSeconds){ digitalWrite(ledPin_Option_2, HIGH);
}

//option 1 - Execute the first option if the button is held for the correct amount of time
else if(pressLength_milliSeconds >= optionOne_milliSeconds){ digitalWrite(ledPin_Option_1, HIGH);
  }//close if options

//every time through the loop, we need to reset the pressLength_Seconds counter
pressLength_milliSeconds = 0; 
} // close void loop
