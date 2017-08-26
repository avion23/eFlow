#include <Arduino.h>	// this is necessary for streaming, strings, vectors and has to be first
#include <espLogger.h>
//#include <myMqtt.h>
#include <ota.h>
#include <Ticker.h>
#include <string>
#include <Streaming.h>
#include <telnetServer.h>
#include <udpserver.h>
#include <wifi.h>

ADC_MODE(ADC_VCC);		// read internal adc
Ticker msTicker;

espLogger myLogger;

void milisecondISR() {
	static int run;
	run++;
	if (!(run % 1000)) {
		myLogger << "test " << (int) run / 1000 << endl;
//		myLogger << "test " << endl;
	}
}

void setup() {
	pinMode(2, OUTPUT);   // sets the pin as output
	Serial.begin(115200);
//	Serial << endl << "[SYS] Booting" << endl;
	wifiSetup();
	otaSetup();
//	mqttSetup();
	delay(1);
	msTicker.attach(0.001, milisecondISR);
	sei();
//	telnetSetup();
}

void loop() {
	otaLoop();
//	telnet.loop();
//	telnetLoop();
}
