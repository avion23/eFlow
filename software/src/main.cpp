

#ifndef UNIT_TESTING

#include <Arduino.h>
#include "hardwareConfig.h"
#include "ISR.h"
#include <wifi.h>
#include <ota.h>
#include <Streaming.h>
void setup(){
	Serial.begin(115200);

	pinMode(PIN_INPUT_OPTOCOUPLER, INPUT);
	pinMode(PIN_SSR_OUTPUT, OUTPUT);
	digitalWrite(PIN_SSR_OUTPUT, LOW);
	wifiSetup();
	otaSetup();
	initISR();

}


void loop(){
	otaLoop();
	delay(200);
	Serial << "hello" << endl;
}

#endif
