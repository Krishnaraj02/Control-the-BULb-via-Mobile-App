#include <RH_ASK.h>

RH_ASK rfDriver;

const int ledPin = 13; // Change this to the pin where your LED is connected

void setup() {
    Serial.begin(115200);
    pinMode(ledPin, OUTPUT);
    if (!rfDriver.init())
        Serial.println("RF driver initialization failed");
    Serial.println("RF driver initialization success");


}

void loop() {
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if (rfDriver.recv(buf, &buflen)) {
        // Message received successfully
        char command = buf[0];

        Serial.print("Received command: ");
        Serial.println(command);

        sendCommandToLED(command);
    }

    delay(10);
}

void sendCommandToLED(char command) {
    if (command == '0') {
        // 'on' command received
        digitalWrite(ledPin, HIGH);
        Serial.println("LED is ON");
    } else if (command == '1') {
        // 'off' command received
        digitalWrite(ledPin, LOW);
        Serial.println("LED is OFF");
    } else {
        Serial.println("Invalid command");
    }
}
