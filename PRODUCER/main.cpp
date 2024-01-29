#include <iostream>
#include <cstring>
#include <mosquitto.h>
#include <crow.h>

#include <crow/middlewares/cors.h>

class MQTTClient {
private:
    mosquitto *mosq;
    const char *host;
    int port;
    int keepalive;

public:
    MQTTClient(const char *h, int p, int k) : host(h), port(p), keepalive(k), mosq(nullptr) {}

    bool connect() {
        mosquitto_lib_init();
        mosq = mosquitto_new(NULL, true, NULL);
        if (!mosq) {
            std::cerr << "Error: Out of memory\n";
            return false;
        }

        if (mosquitto_connect(mosq, host, port, keepalive)) {
            std::cerr << "Unable to connect to MQTT \n";
            return false;
        }
        return true;
    }

    bool publish(const char *topic, const char *message) {
        if (!mosq) {
            std::cerr << "Not connected to MQTT Broker\n";
            return false;
        }
        int msg_len = strlen(message);
        if (mosquitto_publish(mosq, NULL, topic, msg_len, message, 0, false)) {
            std::cerr << "Failed to publish message\n";
            return false;
        }
        return true;
    }

    void disconnect() {
        if (mosq) {
            mosquitto_disconnect(mosq);
            mosquitto_destroy(mosq);
        }
        mosquitto_lib_cleanup();
    }

    ~MQTTClient() {
        disconnect();
    }
};

class MyApp {
private:
    MQTTClient client;
    crow::SimpleApp app;
   

public:
    MyApp() : client("localhost", 1883, 60){
    

        CROW_ROUTE(app, "/on").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {
            crow::response res;

            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "GET");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");

            if (!client.connect()) {
                res = crow::response(500, "Failed to connect to MQTT");
                return res;
            }

            if (!client.publish("esp8266/led", "on")) {
                client.disconnect();
                res = crow::response(500, "Failed to send message");
                return res;
            }

            client.disconnect();
            
            res = crow::response(200, "LED turned on");
            return res;
        });

        CROW_ROUTE(app, "/off").methods(crow::HTTPMethod::Get)
        ([this](const crow::request& req) {
            crow::response res;

            res.add_header("Access-Control-Allow-Origin", "*");
            res.add_header("Access-Control-Allow-Methods", "GET");
            res.add_header("Access-Control-Allow-Headers", "Content-Type");

            if (!client.connect()) {
                res = crow::response(500, "Failed to connect to MQTT");
                return res;
            }

            if (!client.publish("esp8266/led", "off")) {
                client.disconnect();
                res = crow::response(500, "Failed to send message");
                return res;
            }

            client.disconnect();
          
            res = crow::response(200, "LED turned off");
            return res;
        });

    }

    void run() {
        app.port(9111).multithreaded().run();
    }
};

int main() {
    MyApp myapp;
    myapp.run();

    return 0;
}
