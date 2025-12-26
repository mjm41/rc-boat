#include <WiFiS3.h>
#include <WebSocketsClient.h>
#include <Modulino.h>

static const char* BOAT_AP_SSID = "ESP8266 Access Point";
static const char* BOAT_AP_PASS = "";

static const char* BOAT_WS_HOST = "192.168.4.1";
static const uint16_t BOAT_WS_PORT = 81;
static const char* BOAT_WS_URL = "/";
static const char* BOAT_WS_PROTOCOL = "arduino";

static const uint16_t SEND_HZ = 50;
static const uint32_t SEND_PERIOD_MS = 1000UL / SEND_HZ;

static const bool INVERT_Y = false;

WebSocketsClient ws;
ModulinoJoystick joystick;
static int lastY = -1;
static int lastX = -1;
static uint32_t lastSendMs = 0;

void onWsEvent(WStype_t type, uint8_t* payload, size_t length)
{
    switch (type)
    {
        case WStype_CONNECTED:
            Serial.println("WS connected");
            break;
        case WStype_DISCONNECTED:
            Serial.println("WS disconnected");
            break;
        default:
            break;
    }
}

static inline int joyTo255(int v)
{
    int out = v + 128;
    if (out < 0) out = 0;
    if (out > 255) out = 255;
    return out;
}

static inline int joyTo180(int v)
{
    int v255 = joyTo255(v);
    int out = (v255* 180) / 255;
    if (out < 0) out = 0;
    if (out > 180) out = 180;
    return out;
}

void connectWiFi()
{
    Serial.print("Connecting to RC-BOAT: ");
    Serial.println(BOAT_AP_SSID);

    WiFi.begin(BOAT_AP_SSID); 

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(250);
        Serial.print(".");
    }
    Serial.println();

    Serial.print("WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
}

void connectWebSocket()
{
    ws.onEvent(onWsEvent);
    ws.begin(BOAT_WS_HOST, BOAT_WS_PORT, BOAT_WS_URL, BOAT_WS_PROTOCOL);
    Serial.print("WS begin -> ");
    Serial.print(BOAT_WS_HOST);
    Serial.print(":");
    Serial.println(BOAT_WS_PORT);
}

void setup()
{
    Serial.begin(115200);
    delay(200);

    Modulino.begin();
    joystick.begin();

    connectWiFi();
    connectWebSocket();
}

void loop()
{
    ws.loop();

    const uint32_t now = millis();
    if (now - lastSendMs < SEND_PERIOD_MS) return;
    lastSendMs = now;

    joystick.update();
    int rawY = (int)joystick.getY();
    int rawX = (int)joystick.getX();

    int y255 = joyTo255(rawY);
    if (INVERT_Y) y255 = 255 - y255;

    int x180 = joyTo180(rawX);

    if (y255 != lastY)
    {
        char buf[16];
        snprintf(buf, sizeof(buf), "Y:%d", y255);
        Serial.print("y=");
        Serial.print(y255);
        ws.sendTXT(buf);
        lastY = y255;
    }

    if (x180 != lastX)
    {
        char buf[16];
        snprintf(buf, sizeof(buf), "X:%d", x180);
        Serial.print(" x=");
        Serial.print(x180);
        Serial.print("\r\n");
        ws.sendTXT(buf);
        lastX = x180;
    }
}
