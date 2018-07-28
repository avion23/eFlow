/*
 * ISR.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: avion23
 */
#ifndef UNIT_TESTING

#include <Streaming.h>
#include "ISR.h"
#include "hardwareConfig.h"
//
//Ticker delayer;	// used to delay turning off the SSR
//int zeroCrossingsCounter { 0 };
//
//void ICACHE_RAM_ATTR ISRPullSSRLow() {
//	interrupts();
//	digitalWrite(PIN_SSR_OUTPUT, LOW);
//}
//
//void ICACHE_RAM_ATTR ISRZeroCrossing() {
//	interrupts();
//	zeroCrossingsCounter++;
//	static deltaSigma d(100);	// convert percent to bits
//	int Output = 750;
//	if (d.update(Output / 10)) {
//		digitalWrite(PIN_SSR_OUTPUT, HIGH);
//		delayer.once_ms(Delay_MS_SSR_Minimum_On_Time, ISRPullSSRLow); // leave the SSR turned on until the next zero cross is passed
//	} else {
//		digitalWrite(PIN_SSR_OUTPUT, LOW);
//	}
//}
//
//
//
//void ICACHE_RAM_ATTR initISR() {
//	interrupts();
//	// this should be a sine wave and is highly hardware dependend
//	// The PIN is pulled low through the optocoupler when the
//	// voltage is at it's maximum.
//	// a falling edge means that maximum is reached.
//	// a rising edge means that the maximum has just passed and we are before the zero crossing
//	attachInterrupt(digitalPinToInterrupt(PIN_INPUT_OPTOCOUPLER),
//			ISRZeroCrossing, RISING);
//	Serial << "[ISR] configured " << endl;
//}

// to be called periodically to turn on and off the SSR
void ICACHE_RAM_ATTR ISRSSRPeriodic() {
		interrupts();
		static deltaSigma d(100);	// convert percent to bits
		int Output = 750;
		if (d.update(Output / 10)) {
			digitalWrite(PIN_SSR_OUTPUT, HIGH);
		} else {
			digitalWrite(PIN_SSR_OUTPUT, LOW);
		}

}

void initISR() {
	static Ticker periodic;	// used to delay turning off the SSR
	periodic.attach_ms(500, ISRSSRPeriodic); // leave the SSR turned on until the next zero cross is passed
}

#endif
