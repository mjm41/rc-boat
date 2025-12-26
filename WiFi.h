#ifndef WIFI_H
#define WIFI_H

#include "config.h"

void startWiFi()                                    // Start a Wi-Fi access point, and try to connect to some given access points.
{
    WiFi.softAP(ssid);                              // Start the access point
    Serial.print("Access Point \"");
    Serial.print(ssid);
    Serial.println("\" started\r\n");

    delay(250);
    Serial.println("\r\n");
    if(WiFi.softAPgetStationNum() == 0)               // If the ESP is connected to an AP
    {
        Serial.print("Connected to ");
        Serial.println(WiFi.SSID());                  // Tell us what network we're connected to
        Serial.print("IP address:\t");
        Serial.print(WiFi.localIP());                 // Send the IP address of the ESP8266 to the computer
    }
    else                                              // If a station is connected to the ESP SoftAP
    {
        Serial.print("Station connected to ESP8266 AP");
    }
    Serial.println("\r\n");
}


#endif // !WIFI_H
