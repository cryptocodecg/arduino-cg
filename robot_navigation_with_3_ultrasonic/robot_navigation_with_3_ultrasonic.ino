/*
Simple wheeled robot motoric with 3 sensor(s) - front, left and right
Made by : Antonius (sw0rdm4n)

http://www.ringlayer.net

*/
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

/* Modified from http://itp.nyu.edu/physcomp/Labs/DCMotorControl */

int motorkanan_arah_depan = 4;    
int motorkanan_arah_belakang = 5;   
int enablePin = 9;   
int motorkiri_arah_depan = 2;    
int motorkiri_arah_belakang = 3;    
unsigned int sensor1_val = 0;
unsigned int sensorkiri_val = 0;
unsigned int sensorkanan_val= 0;
int i = 0;

void setup() {
    Serial.begin(9600);
    pinMode(motorkanan_arah_depan, OUTPUT); 
    pinMode(motorkanan_arah_belakang, OUTPUT); 
    pinMode(motorkiri_arah_depan, OUTPUT); 
    pinMode(motorkiri_arah_belakang, OUTPUT); 
    digitalWrite(enablePin, HIGH); 
}
void mundur_long()
{
      digitalWrite(motorkanan_arah_depan, LOW);  
      digitalWrite(motorkanan_arah_belakang, HIGH);  
      digitalWrite(motorkiri_arah_depan, LOW);   
      digitalWrite(motorkiri_arah_belakang, HIGH);  
      delay(500); 
}
void berhenti()
{
    digitalWrite(motorkanan_arah_depan, LOW);  
    digitalWrite(motorkanan_arah_belakang, LOW);
      
    digitalWrite(motorkiri_arah_depan, LOW);  
    digitalWrite(motorkiri_arah_belakang, LOW);
    delay(500);
}
void maju()
{
      unsigned int uS = sonar.ping(); 
     
      sensor1_val = uS / US_ROUNDTRIP_CM;
      Serial.println("\nsensor depan val : ");
      Serial.print(sensor1_val);
      Serial.print(" cm\n");
      if (sensor1_val < 50 && sensor1_val > 0) {
          mundur_long();
          avoid();
      }
      Serial.println("\nmaju\n");
      digitalWrite(motorkanan_arah_depan, HIGH);   //right
      digitalWrite(motorkanan_arah_belakang, LOW);
      digitalWrite(motorkiri_arah_depan, HIGH);   //left 
      digitalWrite(motorkiri_arah_belakang, LOW);
      delay(50);
       
}
void op()
{
    maju();  
}
void avoid()
{
       int loopback;
       unsigned int uSkiri = sonar_kiri.ping();
       unsigned int uSkanan = sonar_kanan.ping();
     
       sensorkiri_val = uSkiri / US_ROUNDTRIP_CM;
       sensorkanan_val = uSkanan / US_ROUNDTRIP_CM;
       Serial.println("if block executed");
       Serial.println("\nsensor kiri val : ");
       Serial.print(sensorkiri_val);
       Serial.print(" cm\n");
       Serial.println("\nsensor kanan val : ");
       Serial.print(sensorkanan_val);
       Serial.print(" cm\n");
       if (sensorkiri_val > 60) {
           Serial.println("belok kiri"); 
           berhenti();
           belok_kiri(); 
      } 
      else if (sensorkanan_val > 60){
           Serial.println("belok kanan"); 
           berhenti();
           belok_kanan(); 
      } 
      else {
           for (loopback = 0; loopback < 2; loopback++) {
               mundur_long(); 
           }
      }
}
void belok_kanan()
{
      digitalWrite(motorkanan_arah_depan, LOW);  
      digitalWrite(motorkanan_arah_belakang, HIGH);  
      digitalWrite(motorkiri_arah_depan, LOW);  
      digitalWrite(motorkiri_arah_belakang, LOW);
      delay(500); 
}
void belok_kiri()
{
      digitalWrite(motorkanan_arah_depan, HIGH);  
      digitalWrite(motorkanan_arah_belakang, LOW);  
      digitalWrite(motorkiri_arah_depan, LOW);   
      digitalWrite(motorkiri_arah_belakang, HIGH);
      delay(500); 
}
void loop() {
   op();
}
