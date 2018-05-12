/*
 * ISR.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: avion23
 */

#include "ISR.h"

Ticker delayer;	// used to delay turninig off the SSR

void ICACHE_RAM_ATTR ISRPullSSRLow() {
	interrupts();
	digitalWrite(PIN_SSR_OUTPUT, LOW);
}

void ICACHE_RAM_ATTR ISRZeroCrossing() {
	interrupts();
	static deltaSigma d(100);	// convert percent to bits
	Output = 750;
	if (d.update(Output / 10)) {
		digitalWrite(PIN_SSR_OUTPUT, HIGH);
		delayer.once_ms(Delay_MS_SSR_Minimum_On_Time, ISRPullSSRLow);// leave the SSR turned on for 1 ms
	} else {
		digitalWrite(PIN_SSR_OUTPUT, LOW);
	}
}

double Setpoint { 0 }; //Input: The variable we're trying to control (double)
double Input { 0 }; //Output: The variable that will be adjusted by the pid (double)
double Output { 0 }; //Setpoint: The value we want to Input to maintain (double)

int zeroCrossingsCounter { 0 };

void ICACHE_RAM_ATTR initISR() {
	interrupts();
	// this should be a sine wave and is highly hardware dependend
	// The PIN is pulled low through the optocoupler when the
	// voltage is at it's maximum.
	// a falling edge means that maximum is reached.
	// a rising edge means that the maximum has just passed and we are before the zero crossing
	attachInterrupt(digitalPinToInterrupt(PIN_INPUT_OPTOCOUPLER),
			ISRZeroCrossing, RISING);
}
