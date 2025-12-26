#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include "config.h"

void startWebSocket()
{
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    Serial.println("WebSocket server started.");
}

#endif // !WEBSOCKET_H
