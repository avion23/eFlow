/*
 * wifi.cpp
 *
 *  Created on: Apr 9, 2017
 *      Author: avion
 */

#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <Streaming.h>

const auto ledPin = 13; 	// ESP-12E

void wifiSetup() {
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);	// inverted
	static WiFiManager wifiManager;
	wifiManager.setDebugOutput(true);

	wifiManager.setAPCallback(
			[](WiFiManager *myWiFiManager) {
				Serial << "[Wifimanager] Entered config mode. IP: " << WiFi.softAPIP() << endl;
				Serial << "[Wifimanager] my SSID: " << myWiFiManager->getConfigPortalSSID() << endl;
			});
	wifiManager.autoConnect();

	digitalWrite(ledPin, HIGH);	// inverted

//	WiFi.mode(WIFI_STA);
//	WiFi.begin(ssid, password);
//	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
//		Serial.println("[OTA] Connection Failed! Rebooting...");
//		delay(5000);
//		ESP.restart();
//	}
}
