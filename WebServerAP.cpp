#include "WebServerAP.h"

void WebServerAPClass::HandleClient()
{
	server->handleClient();
}

void WebServerAPClass::Init()
{
	uint8 mode = 0;
	wifi_softap_set_dhcps_offer_option(OFFER_ROUTER, &mode); // Turn off DHCP server

	/* You can remove the password parameter if you want the AP to be open. */
	Serial1.print("Setting wifi AP mode ... ");
	WiFi.mode(WIFI_AP);
	IPAddress apIP(192, 168, 88, 1);
	Serial1.print("Setting soft-AP configuration ... ");
	Serial1.println(WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0)) ? "Ready" : "Failed!");
	Serial1.print("Setting soft-AP ... ");
	Serial1.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

	std::function<void()> handleRoot = std::bind(&WebServerAPClass::HandleRoot, this);

	IPAddress myIP = WiFi.softAPIP();
	Serial1.print("AP IP address: ");
	Serial1.println(myIP);
	server->on("/", handleRoot);
	server->begin();
	Serial1.println("HTTP server started");
}

void WebServerAPClass::HandleRoot() {
	server->send(200, "text/html", "<h1>You are connected</h1>");
}