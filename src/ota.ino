/*
 * ota.cpp
 *
 *  Created on: Apr 9, 2017
 *      Author: avion
 */

#include <ESP8266mDNS.h>
#include <ota.h>
#include <Streaming.h>


uint32_t linToLog(uint32_t in, uint32_t range) {
	// magic
	// source: https://diarmuid.ie/blog/pwm-exponential-led-fading-on-arduino-or-other-platforms/
	float R = (range * log10(2)) / log10(range);
	float retValue = pow(2, in / R) - 1;
	return (int) retValue;
}

void otaSetup() {
	const auto ledPin = 2;	// onboard led for ESP-12E
	pinMode(ledPin, OUTPUT);   // sets the pin as output
	// Port defaults to 8266
	// ArduinoOTA.setPort(8266);

	// Hostname defaults to esp8266-[ChipID]
	// ArduinoOTA.setHostname("myesp8266");

	// No authentication by default
	// ArduinoOTA.setPassword((const char *)"123");

	ArduinoOTA.onStart([]() {
		Serial << "[OTA] Starting" << endl;
		analogWrite(ledPin, 1000);

	});
	ArduinoOTA.onEnd([]() {
		Serial << "\n[OTA] Finished" << endl;
		for (int i=0;i<30;i++)
		{
			analogWrite(ledPin,(i*100) % 1001);
			delay(50);
		}
		Serial << "[OTA] rebooting" << endl;
		ESP.restart();
	});
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
		digitalWrite(ledPin, progress %2);
		Serial << "[OTA] Progress: " << (progress / (total / 100)) << "\r";

	});
	ArduinoOTA.onError([](ota_error_t error) {
		Serial << "[OTA] Error: "<< error << endl;
		switch(error) {
			case OTA_AUTH_ERROR:
			Serial << "[OTA] Auth Failed" << endl;
			break;
			case OTA_BEGIN_ERROR:
			Serial << "[OTA] Begin Failed" << endl;
			break;
			case OTA_CONNECT_ERROR :
			Serial << "[OTA] Connect Failed" << endl;
			break;
			case OTA_RECEIVE_ERROR:
			Serial << "[OTA] Receive Failed" << endl;
			break;
			case OTA_END_ERROR:
			Serial << "[OTA] End Failed" << endl;
			break;
			default:
			Serial << "[OTA] unknown error " << endl;
		}
		Serial.println("[OTA] restarting");
		ESP.restart();
	});
	ArduinoOTA.begin();
	Serial.println("[OTA] Configured");
	Serial.print("[OTA] IP address: ");
	Serial.println(WiFi.localIP());
}

void otaLoop() {
	ArduinoOTA.handle();
}
