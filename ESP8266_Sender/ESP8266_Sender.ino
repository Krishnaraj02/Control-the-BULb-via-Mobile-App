#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define wifi_ssid "."
#define wifi_password "0987654321"
#define mqtt_server "37.27.5.34"
#define mqtt_topic "esp8266/led"

WiFiClient espClient;
PubSubClient client(espClient);

void sendCommandToArduinoUno(const char* command) {
    Serial.print(command);
    Serial.write('\0'); // Add null terminator to indicate the end of the string
}

void callback(char* topic, uint8_t* payload, unsigned int length) {
    if (String(topic) == mqtt_topic) {
        char command[4];
        strncpy(command, (char*)payload, length);
        command[length] = '\0';  // Null-terminate the string

        if (strncmp(command, "on", 2) == 0) {
            sendCommandToArduinoUno("0");
        } else if (strncmp(command, "off", 3) == 0) {
            sendCommandToArduinoUno("1");
        } else {
            Serial.println("Invalid command");
        }
    } else {
        Serial.println("Invalid topic");
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        // Serial.println(".");
    }
    // Serial.println("Connected to WiFi network");

    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);

    while (!client.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        // Serial.printf("Client %s attempting connection to MQTT broker\n", client_id.c_str());
        if (client.connect(client_id.c_str())) {
            Serial.println("CTMB");
            client.subscribe(mqtt_topic);
        } else {
            Serial.print("CF");
            Serial.print(client.state());
            delay(2000);
        }
    }
}

void loop() {
    client.loop();
}
