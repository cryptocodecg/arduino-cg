int redPin = 11;
int greenPin = 10;
int bluePin = 9;
//uncomment this line if using a Common Anode LED //#define COMMON_ANODE
void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}
void loop() {
  setColor(255, 0, 0); // red 
  delay(200);
  setColor(255, 5, 10); // green 
  delay(200);
  setColor(255, 10, 20); // blue 
  delay(200);
  setColor(255, 15, 30); // yellow 
  delay(200);
  setColor(255, 20, 40); // purple 
  delay(200);
  setColor(255, 25, 50); // aqua 
  delay(200);
}
void setColor(int red, int green, int blue) 
{
  #ifdef COMMON_ANODE 
    red = 255 - red; 
    green = 255 - green; 
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red); 
  analogWrite(greenPin, green); 
  analogWrite(bluePin, blue);
  }
