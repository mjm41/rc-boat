#ifndef OTA_H
#define OTA_H

#include "config.h"

void startOTA()                                      // Start the OTA service
{
    ArduinoOTA.setHostname(OTAName);
    ArduinoOTA.setPassword(OTAPassword);
    ArduinoOTA.onStart([]() {
        Serial.println("Start");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin2, LOW);
        });
    ArduinoOTA.onEnd([]() {
        Serial.println("\r\nEnd");
        });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });
    ArduinoOTA.begin();
    Serial.println("OTA ready\r\n");
}

#endif // !OTA_H
