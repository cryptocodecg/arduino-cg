// BT Data Logger
// BlueTooth Configuration
/* Include the software serial port library */
#include <SoftwareSerial.h>
/* to communicate with the Bluetooth module's TXD pin */
#define BT_SERIAL_TX 10
/* to communicate with the Bluetooth module's RXD pin */
#define BT_SERIAL_RX 11
/* Initialise the software serial port */
SoftwareSerial BluetoothSerial(BT_SERIAL_TX, BT_SERIAL_RX);

#include <NewPing.h>
#define TRIGGER_PIN 6 
#define ECHO_PIN 7 
#define MAX_DISTANCE 200

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


void setup() {
/* Set the baud rate for the software serial port */
BluetoothSerial.begin(9600); // Initialise BlueTooth
delay(1000);
BluetoothSerial.print("Starting ...");
}

void loop() {
// Take readings
  delay(50);
  unsigned int uS = sonar.ping_cm(); 
  Serial.print(uS); 
  Serial.println("cm");

  BluetoothSerial.print("Distance: ");
  BluetoothSerial.print(uS);
 // BluetoothSerial.print("\n");
}
