#include "WebServerAP.h"

WebServerAPClass webServerAP;

void setup() {
	delay(1000);
	Serial1.begin(115200);
	Serial1.println();

	webServerAP.Init();
}

void loop() {
	webServerAP.HandleClient();
}