#ifndef SERVERHANDLERS_H
#define SERVERHANDLERS_H

#include "config.h"

// forward declaration
void setThrust(int y);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED:
        {
            IPAddress ip = webSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        }
        break;
    case WStype_TEXT:
        char msg[64];
        size_t n = (length < sizeof(msg) -1) ? length : (sizeof(msg) - 1);
        memcpy(msg, payload, n);
        msg[n] = '\0';

        Serial.printf("[%u] get Text: %s\n", num, msg);
        if (n >= 3 && msg[0] == 'Y' && msg[1] == ':')
        {
            long y = strtol(&msg[2], nullptr, 10);
            if (y < 0) y = 0;
            if (y > 255) y = 255;

            setThrust((int)y);
        }
        if (n >= 3 && msg[0] == 'X' && msg[1] == ':')
        {
            long x = strtol(&msg[2], nullptr, 10);
            if (x < 0) x = 0;
            if (x > 180) x = 180;

            servo.write((int)x);
        }
        break; 
    }
}



void setMotorDir(bool forward)
{
    if (forward)
    {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin2, LOW);
    }
    else
    {
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin2, HIGH);
    }
}



void setThrust(int y)
{
    int delta = y - 128;

    if (delta == 0)
    {
        analogWrite(enable1Pin, LOW);
        analogWrite(enable2Pin, LOW);
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin2, LOW);
        Serial.println("Motor stopped");
        return;
    }

    bool forward = (delta > 0);
    int pwm = abs(delta) * 2;

    setMotorDir(forward);
    analogWrite(enable1Pin, pwm);
    analogWrite(enable2Pin, pwm);
}

#endif // !SERVERHANDLERS_H
