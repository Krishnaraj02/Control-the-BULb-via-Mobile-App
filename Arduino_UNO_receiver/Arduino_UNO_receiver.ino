// const int ledPin = 13; // Change this to the pin where your LED is connected

// void setup() {
//   Serial.begin(115200); // Make sure the baud rate matches the one in your ESP8266 code
//   pinMode(ledPin, OUTPUT);
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char command = Serial.read();
//     if (command == 'o') {
//       // 'on' command received
//       digitalWrite(ledPin, HIGH);
//       Serial.println("LED is ON");
//     } else if (command == 'f') {
//       // 'off' command received
//       digitalWrite(ledPin, LOW);
//       Serial.println("LED is OFF");
//     }
//   }
// }



#include <RH_ASK.h>

RH_ASK rfDriver;

void setup() {
    Serial.begin(115200);
    if (!rfDriver.init())
        Serial.println("RF driver initialization failed");
    Serial.println("RF driver initialization success");
}

void loop() {
    if (Serial.available() > 0) {
        char command = Serial.read();
        Serial.print("Transmitting command: ");
        Serial.println(command);
        rfDriver.send((uint8_t*)&command, sizeof(command));
        rfDriver.waitPacketSent();
    }
}




