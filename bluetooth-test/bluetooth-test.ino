#define BLYNK_USE_DIRECT_CONNECT
// You could use a spare Hardware Serial on boards that have it (like Mega)
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "d5120056b9a443a2a45b400ceeecc6c9";
void setup()
{
// Debug console
  DebugSerial.begin(38400);
  DebugSerial.println("Waiting for connections...");
// Blynk will work through Serial
// 9600 is for HC-06. For HC-05 default speed is 38400
// Do not read or write this serial manually in your sketch
  Serial.begin(9600);
  Blynk.begin(Serial, auth);
}
void loop()
{
  Blynk.run();
}
