#include "WebServerAP.h"

WebServerAPClass webServerAP;

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();

	webServerAP.Init();
}

void loop() {
	webServerAP.HandleClient();
}