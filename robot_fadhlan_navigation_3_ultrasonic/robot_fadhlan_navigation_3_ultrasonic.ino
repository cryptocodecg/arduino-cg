//Libraries
#include <NewPing.h>

/* front sonar */
#define TRIG_DEPAN_ATAS  12 
#define ECHO_DEPAN_ATAS     13  

/* left sonar */
#define TRIG_KIRI  10 
#define ECHO_KIRI     11  

/* right sonar */
#define TRIG_KANAN  6 
#define ECHO_KANAN    7  

#define MAX_DISTANCE 200 
NewPing sonar(TRIG_DEPAN_ATAS, ECHO_DEPAN_ATAS, MAX_DISTANCE); 
NewPing sonar_kiri(TRIG_KIRI, ECHO_KIRI, MAX_DISTANCE); 
NewPing sonar_kanan(TRIG_KANAN, ECHO_KANAN, MAX_DISTANCE); 

//Constants
const int button = 8;     //Button pin to pin 2
//const int led    = 3;     //Led pin (throught resistor) to pin 3
//const int buzzer = 4;     //Buzzer pin to pin 4
const int motorA1= 2;     //motor A positive (+) pin to pin 6 (PWM) (from L298 module!)
const int motorA2= 3;         //motor A negative (-) pin to pin 9 (PWM)
const int motorB1= 4;     //motor B positive (+) pin to pin 10 (PWM)
const int motorB2= 5;     //motor B negative (-) pin to pin 11 (PWM)


//Variables
int distance;         //Variable to store distance from an object
int checkRight;
int checkLeft;
int function=0;         //Variable to store function of robot: '1' running or '0' stoped. By default is stoped
int buttonState=0;            //Variable to store the state of the button. By default '0'
int flag=0;           //Useful flag to keep the button state when button is released 


void setup()
{
    Serial.begin(9600);
    pinMode(button, INPUT_PULLUP);
//    pinMode(led,  OUTPUT);
//    pinMode(buzzer, OUTPUT);
    pinMode(motorA1,OUTPUT);
    pinMode(motorA2,OUTPUT);
    pinMode(motorB1,OUTPUT);
    pinMode(motorB2,OUTPUT);
  
}

void loop()
{
  //Check button state
  buttonState = digitalRead(button);
  unsigned int uS = sonar.ping(); 
  

  //unsigned long currentMillis = millis(); //counting...

  //Change main function (stoped/running) when button is pressed 
    if (buttonState == LOW) {//If button is pressed once...
      delay(500);
      if ( flag == 0){
          function = 1;
          flag=1; //change flag variable
      }
      else if ( flag == 1){  //If button is pressed twice
        function = 0;
        flag=0; //change flag variable again 
      }    
    }
    
  if (function == 0){   //If button is unpressed or pressed twice then:
    Serial.print("button is  not pressed\n");
//    myservo.write(90);    //set servo 90 degress - sensor will look forward
    stop();         //robot remain stoped
//    noTone(buzzer);     //buzzer off
//    digitalWrite(led, HIGH);// and led on
    
  }
  else if (function == 1){//If button is pressed then:
    //Read distance...
    Serial.print("button is pressed\n");
    sensor1_val = uS / US_ROUNDTRIP_CM;
    Serial.println("\nsensor depan val : ");
    Serial.print(sensor1_val); 
    Serial.print(" cm\n");

//    distance = ultrasonic.Ranging(CM); //Tip: Use 'CM' for centimeters or 'INC' for inches
//    Serial.print("Distance: ");
//    Serial.print(distance);
//    Serial.println();

    //Check for objects...
    if (distance > 10){
      forward(); //All clear, move forward!
//      noTone(buzzer);
//      digitalWrite(led,LOW);
    }
    else if (distance <=10){
      stop(); //Object detected! Stop the robot and check left and right for the better way out!
      Serial.print("object detected!\n");
      tone(buzzer,500); // play a tone
      digitalWrite(led,HIGH); // turn the led on
      //Start scanning... 
      for(pos = 0; pos < 180; pos += 1){  //goes from 0 degrees to 180 degrees 
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position 
            } 
            
            checkLeft = ultrasonic.Ranging(CM);   //Take distance from the left side
            Serial.print("Check left: ");
            Serial.print(checkLeft);
            Serial.println();
            
            for(pos = 180; pos>=0; pos-=1){     //goes from 180 degrees to 0 degrees                           
                myservo.write(pos);             //tell servo to go to position in variable 'pos' 
                delay(10);                      //waits 10ms for the servo to reach the position   
            }
            
            checkRight= ultrasonic.Ranging(CM);
            Serial.print("Check right");
            Serial.print(checkRight);
            Serial.println();
            myservo.write(90);                   // Sensor "look" forward again
            
            //Finally, take the right decision, turn left or right?
            if (checkLeft < checkRight){
              left();
              delay(400); // delay, change value if necessary to make robot turn.            
              }
            else if (checkLeft > checkRight){
              right();
              delay(400); // delay, change value if necessary to make robot turn.
            }
            else if (checkLeft <=10 && checkRight <=10){
              backward(); //The road is closed... go back and then left ;)
              left();
            }
    }
  }

}


void forward(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void backward(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void left(){
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
}

void right(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW); 
}

void stop(){
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
}
