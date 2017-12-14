#pragma once

#ifndef _WEB_SERVER_AP_h
#define _WEB_SERVER_AP_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <functional>

extern "C" {
#include "user_interface.h"
}

class WebServerAPClass
{
private:
	const char *ssid = "ESPchess";
	const char *password = "thereisnospoon";
	ESP8266WebServer * server;
	WiFiEventHandler e1;
	void HandleRoot();

public:
	void Init();
	void HandleClient();
};

#endif
