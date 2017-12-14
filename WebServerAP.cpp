#include "WebServerAP.h"

void WebServerAPClass::HandleClient()
{
	server->handleClient();
}

void WebServerAPClass::Init()
{
	uint8 mode = 0;
	wifi_softap_set_dhcps_offer_option(OFFER_ROUTER, &mode); // Turn off DHCP server

	server = new ESP8266WebServer(80);

	onNewStation = std::bind(&WebServerAPClass::OnNewStation, this, _1);

	/* You can remove the password parameter if you want the AP to be open. */
	Serial.print("Setting wifi AP mode ... ");
	WiFi.mode(WIFI_AP);
	IPAddress apIP(192, 168, 88, 1);
	Serial.print("Setting soft-AP configuration ... ");
	Serial.println(WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)) ? "Ready" : "Failed!");
	Serial.print("Setting soft-AP ... ");
	Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
	e1 = WiFi.onSoftAPModeStationConnected(onNewStation);

	handleRoot = std::bind(&WebServerAPClass::HandleRoot, this);
	handleChess = std::bind(&WebServerAPClass::HandleChess, this);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
	server->on("/", handleRoot);
	server->on("/chess", handleChess);
	server->begin();
	Serial.println("HTTP server started");
}

void WebServerAPClass::OnNewStation(WiFiEventSoftAPModeStationConnected sta_info)
{
	char last_mac[18];
	Serial.println("New Station :");
	sprintf(last_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
	Serial.printf("MAC address : %s %lu\r\n", last_mac, micros());
	Serial.printf("Id : %d\r\n", sta_info.aid);
}

void WebServerAPClass::HandleRoot()
{
	server->send(200, "text/html", "<h1>You are connected</h1>");
}

void WebServerAPClass::HandleChess()
{
	server->send(200, "text/html", "<h1>Check Mate!</h1>");
}
