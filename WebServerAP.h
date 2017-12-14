#pragma once

#ifndef _WEB_SERVER_AP_h
#define _WEB_SERVER_AP_h

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <functional>

using namespace std::placeholders;

extern "C" {
#include "user_interface.h"
}

class WebServerAPClass
{
private:
	const char *ssid = "ESPap";
	const char *password = "thereisnospoon";

	ESP8266WebServer * server;
	WiFiEventHandler e1;
	std::function<void(WiFiEventSoftAPModeStationConnected)> onNewStation;
	void OnNewStation(WiFiEventSoftAPModeStationConnected sta_info);

	std::function<void(void)> handleRoot;
	void HandleRoot();
	std::function<void(void)> handleChess;
	void HandleChess();

public:
	void Init();
	void HandleClient();
};

#endif
