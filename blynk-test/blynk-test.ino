#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial


#include <SoftwareSerial.h>
SoftwareSerial SwSerial(10, 11); // RX, TX
    
#include <BlynkSimpleSerialBLE.h>
//#include <SoftwareSerial.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "1d272958d2a74c4fa18a34c82a60ebde";

//SoftwareSerial SerialBLE(10, 11); // RX, TX

void setup()
{
  // Debug console
  Serial.begin(38400);

//  SerialBLE.begin(9600);
//  Blynk.begin(SerialBLE, auth);

  Serial.begin(38400);
  Blynk.begin(Serial, auth);

  Serial.println("Waiting for connections...");
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
