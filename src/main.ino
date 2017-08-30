#include <Arduino.h>	// this is necessary for streaming, strings, vectors and has to be first
#include <logger/espLogger.h>
//#include <myMqtt.h>
#include <ota.h>
#include <Ticker.h>
#include <string>
#include <Streaming.h>
#include <logger/telnetServer.h>
#include <wifi.h>

ADC_MODE(ADC_VCC);		// read internal adc
Ticker msTicker;

void milisecondISR() {
	static int run;
	run++;
	if (!(run % 1000)) {
		logger << "test " << (int) run / 1000 << endl;
	}
}

void setup() {
	pinMode(2, OUTPUT);   // sets the pin as output
	Serial.begin(115200);
	wifiSetup();
	otaSetup();
//	mqttSetup();
	delay(1);
	msTicker.attach(0.001, milisecondISR);
	sei();
}

void loop() {
	otaLoop();
}
