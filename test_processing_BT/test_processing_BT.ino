// BT Data Logger
// BlueTooth Configuration
/* Include the software serial port library */
#include <SoftwareSerial.h>
/* to communicate with the Bluetooth module's TXD pin */
#define BT_SERIAL_TX 10
/* to communicate with the Bluetooth module's RXD pin */
#define BT_SERIAL_RX 11
/* Initialise the software serial port */
SoftwareSerial BT(BT_SERIAL_TX, BT_SERIAL_RX);

void setup() {
  /* Set the baud rate for the software serial port */
//  Serial.begin(38400)
  //BluetoothSerial.begin(9600); // Initialise BlueTooth
  BT.begin(9600); // Initialise BlueTooth
  delay(1000);
  //Serial.print("Starting ...");
  //BluetoothSerial.print("Starting ...");
  BT.print("Starting ...");
}

void loop() {
  //  Serial.print("Hello to Processing via Bluetooth");
  //  BluetoothSerial.print("Hello to Processing via Bluetooth ");
  BT.print("Hello to Processing via Bluetooth ");
  // BluetoothSerial.print("\n");
}
