#include <Wire.h>
#include <HMC5883L.h>
#include <NewPing.h>

NewPing sonar1(A0, A1, 100); //NewPing sonar(trig, echo, maxDist)
NewPing sonar2(A2, A3, 100);
NewPing sonar3(A4, A5, 100);


HMC5883L compass;


//Motor pins
int d1=8; 
int  val2=82,val=90;
int d2=9;
int brake1=4;
int brake2=12;
int op1=5;
int op2=7;
int pwm1=6;
int pwm2=11;
int td=35;

int error = 0;
String s="",s1,s2,s3;
//Final heading hard coded
/* 
 *  0   -> N
 *  90  -> E
 *  180 -> S
 *  270 -> W
 */
int fin_heading=0, curr_heading;
int m11=3,m12=4,m21=5,m22=6;
//Global variables
int t=2,e=7; //HCSR04 control pins
int d,dt; //Distance calculated
//int servoPin=9;
int trans[1000], count =0;
int dis1,dis2,dis3;
//Distance acquire
void distance()
{
  dis1=sonar1.ping_cm();
  dis2=sonar2.ping_cm();
  dis3=sonar3.ping_cm();
  
}
void heading()
{
  MagnetometerRaw raw = compass.readRawAxis();
  MagnetometerScaled scaled = compass.readScaledAxis();
  int MilliGauss_OnThe_XAxis = scaled.XAxis;
  float heading = atan2(scaled.YAxis, scaled.XAxis);
  float declinationAngle = -0.0457;
  heading += declinationAngle;
  if(heading < 0)
    heading += 2*PI;
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI;
  curr_heading=(int)headingDegrees;
  delay(66); 
}

void setup()
{
  Serial.begin(9600);
  pinMode(d1,OUTPUT);
  pinMode(d2,OUTPUT);
  pinMode(brake1,OUTPUT);
  pinMode(brake2,OUTPUT);
  pinMode(op1,OUTPUT);
  pinMode(op2,OUTPUT);
  pinMode(pwm1,OUTPUT);
  pinMode(pwm2,OUTPUT);
  Wire.begin();
  error = compass.setScale(1.3); 
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS); 
}

void loop() 
{
  String sc="+";
  heading();
  distance();
  s1=String(dis1);
  s2=String(dis2);
  s3=String(dis3);
  String head=String((int)curr_heading);
  //String head="360";
  s=sc+s1+sc+s2+sc+s3+sc+head+"arg";
  Serial.print(s);
  Serial.println();
  //Algorithm
  char cd='f';
  cd= dist_empty();
  switch(cd)
  {
    
    case 'l':
    left();
    delay(420);
    stoop();
    delay(100);
    break;
    case 'r': right();
    delay(420);
    stoop();
    delay(100);
    break;
    case 'f': forward();
    delay(150);
    stoop();
    delay(100);
    break;
    default: stoop();
  }
  Serial.println(cd);
  delay(100);
}
char dist_empty()
{
  //Follow RHR
  td=18;
  if(dis1<td&&dis1!=0)
  {
    if(dis2>td||dis2==0)
    return 'l';
    else if(dis3>td||dis3==0)
    return 'r';
    else
    return 's';
  }
  else
  {
    /*if(dis3<=10)
    return 'l';//a=l
    else if(dis2<=10)
    return 'r';//b=r
    else*/
    return 'f';
  }
}
void left()
{
  digitalWrite(brake2,LOW);
      analogWrite(pwm2,val);
      digitalWrite(d1,HIGH);
      analogWrite(pwm1,val);
      digitalWrite(d2,LOW);
      digitalWrite(brake1,LOW);
      digitalWrite(op1,LOW);
      digitalWrite(op2,LOW);
}
void right()
{
 digitalWrite(brake2,LOW);
      analogWrite(pwm2,val);
      digitalWrite(d1,LOW);
      analogWrite(pwm1,val);
      digitalWrite(d2,HIGH);
      digitalWrite(brake1,LOW);
      digitalWrite(op1,LOW);
      digitalWrite(op2,LOW);
}
void forward()
{
  digitalWrite(d1,LOW);
      analogWrite(pwm1,val);
      digitalWrite(brake2,LOW);
      analogWrite(pwm2,val2);
      digitalWrite(d2,LOW);
      digitalWrite(brake1,LOW);
      digitalWrite(op1,LOW);
      digitalWrite(op2,LOW);  
}
void stoop()
{
   digitalWrite(brake2,HIGH);
      digitalWrite(d1,LOW);
      digitalWrite(d2,LOW);
      digitalWrite(brake1,HIGH);
      digitalWrite(op1,LOW);
      digitalWrite(op2,LOW);
      analogWrite(pwm1, 0);
      analogWrite(pwm2, 0);
}
