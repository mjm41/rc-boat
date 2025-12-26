#include "config.h"
#include "OTA.h"
#include "ServerHandlers.h"
#include "WiFi.h"
#include "WebSocket.h"

void setup() 
{
    analogWriteRange(255);
    // sets the pins as outputs:
    pinMode(motor1Pin1, OUTPUT);
    pinMode(motor1Pin2, OUTPUT);
    pinMode(enable1Pin, OUTPUT);
    pinMode(motor2Pin1, OUTPUT);
    pinMode(motor2Pin2, OUTPUT);
    pinMode(enable2Pin, OUTPUT);
    servo.attach(servoPin);

    Serial.begin(115200);
    delay(10);
    Serial.println("\r\n");

    startWiFi();                            // Start a Wi-Fi access point + connect to some given access points.
    startOTA();                             // Start the OTA service
    startWebSocket();                       // Start a WebSocket server
}

void loop() 
{
    webSocket.loop();                       // constantly check for websocket events
    ArduinoOTA.handle();                    // listen for OTA events
}
