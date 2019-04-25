
//Libraries
#include <Servo.h>

//Constants
const int button = 2;     //Button pin to pin 2
const int led    = 3;     //Led pin (throught resistor) to pin 3
const int buzzer = 4;     //Buzzer pin to pin 4
const int motorA1 = 6;    //motor A positive (+) pin to pin 6 (PWM) (from L298 module!)
const int motorA2 = 9;        //motor A negative (-) pin to pin 9 (PWM)
const int motorB1 = 10;   //motor B positive (+) pin to pin 10 (PWM)
const int motorB2 = 11;   //motor B negative (-) pin to pin 11 (PWM)
// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = 12;
const int echoPin = 13;

Servo myServo;          //Create Servo object to control a servo

//Variables
long duration;
int distance;         //Variable to store distance from an object
int checkRight;
int checkLeft;
int function = 0;       //Variable to store function of robot: '1' running or '0' stoped. By default is stoped
int buttonState = 0;          //Variable to store the state of the button. By default '0'
int pos = 90;           //Variable to store the servo position. By default 90 degrees - sensor will 'look' forward
int flag = 0;         //Useful flag to keep the button state when button is released


void setup()
{
  myServo.attach(7);      //Servo pin connected to pin 5
  myServo.write(pos);        // tell servo to go to position in variable 'pos'
  pinMode(button, INPUT_PULLUP);
  pinMode(led,  OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  //Check button state
  buttonState = digitalRead(button);
  unsigned long currentMillis = millis(); //counting...

  //Change main function (stoped/running) when button is pressed
  if (buttonState == LOW) {//If button is pressed once...
    delay(500);
    if ( flag == 0) {
      function = 1;
      flag = 1; //change flag variable
    }
    else if ( flag == 1) { //If button is pressed twice
      function = 0;
      flag = 0; //change flag variable again
    }
  }

  if (function == 0) {  //If button is unpressed or pressed twice then:
    myServo.write(90);    //set servo 90 degress - sensor will look forward
    stop();         //robot remain stoped
    noTone(buzzer);     //buzzer off
    digitalWrite(led, HIGH);// and led on

  }
  else if (function == 1) { //If button is pressed then:
    //Read distance...
    distance = calculateDistance(); //Tip: Use 'CM' for centimeters or 'INC' for inches

    //Check for objects...
    if (distance > 10) {
      forward(); //All clear, move forward!
      noTone(buzzer);
      digitalWrite(led, LOW);
    }
    else if (distance <= 10) {
      stop(); //Object detected! Stop the robot and check left and right for the better way out!
      tone(buzzer, 500); // play a tone
      digitalWrite(led, HIGH); // turn the led on
      //Start scanning...
      // for (pos = 0; pos < 180; pos += 1){  //goes from 0 degrees to 180 degrees
      for (int i = 165; i > 15; i++) {
        myServo.write(i);             //tell servo to go to position in variable 'pos'
        delay(10);                      //waits 10ms for the servo to reach the position
        distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
        Serial.print(i); // Sends the current degree into the Serial Port
        Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
        Serial.print(distance); // Sends the distance value into the Serial Port
        Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      }

      checkLeft = calculateDistance();   //Take distance from the left side

      //      for(pos = 180; pos>=0; pos-=1){     //goes from 180 degrees to 0 degrees
      for (int i = 165; i > 15; i--) {
        myServo.write(i);             //tell servo to go to position in variable 'pos'
        delay(10);                      //waits 10ms for the servo to reach the position
        distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree
  
        Serial.print(i); // Sends the current degree into the Serial Port
        Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
        Serial.print(distance); // Sends the distance value into the Serial Port
        Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
      }

      checkRight = calculateDistance;

      myServo.write(90);                   // Sensor "look" forward again

      //Finally, take the right decision, turn left or right?
      if (checkLeft < checkRight) {
        left();
        delay(400); // delay, change value if necessary to make robot turn.
      }
      else if (checkLeft > checkRight) {
        right();
        delay(400); // delay, change value if necessary to make robot turn.
      }
      else if (checkLeft <= 10 && checkRight <= 10) {
        backward(); //The road is closed... go back and then left ;)
        left();
      }
    }
  }

}

int calculateDistance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;
  return distance;
}

void forward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void backward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
}

void stop() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
