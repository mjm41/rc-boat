#ifndef CONFIG_H
#define CONFIG_H

#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <WebSocketsServer.h>
#include <Servo.h>

WebSocketsServer webSocket(81);              // Create a websocket server on port 81
Servo servo;

const char *ssid = "ESP8266 Access Point";   // name of the Wi-Fi network that will be created
const char *OTAName = "ESP8266";             // A name and a password for the OTA service
const char *OTAPassword = "esp8266";

// Motors 
int motor1Pin1 = 12; 
int motor1Pin2 = 14; 
int enable1Pin = 13; 
int motor2Pin1 = 4; 
int motor2Pin2 = 5; 
int enable2Pin = 15; 
int servoPin = 0;

#endif // !CONFIG_H
