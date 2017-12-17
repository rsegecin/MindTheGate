#include "WebServerAP.h"

WebServerAPClass webServerAP;

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.setDebugOutput(true);
	Serial.println();
	Serial.println("Welcome");

	webServerAP.Init();
}

void loop() {
	webServerAP.HandleClient();
}