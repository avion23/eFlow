/*
 * ISR.h
 *
 *  Created on: Jul 30, 2017
 *      Author: avion23
 */

#ifndef SRC_ISR_H_
#define SRC_ISR_H_
#include <deltaSigma.hpp>
#include <Arduino.h>
#include <Ticker.h>
#include "hardwareConfig.h"

/* This setup is a bit complicated. I didn't want to use delays in the ISRs as those block all further ISRs
 * Alao, with the ESP, there are always wifi interrupts in the background which have to be processed
 * We need to enable the SSR output at zero crossing and hold it for some time
 *  * The holding time should be a few 100µs minimum and 10ms (one half wave) maximum
 * The SSR-25A datasheet doesn't mention this time
 * This is realized by enabling the SSR at zero crossing and starting a one shot timer which disables the SSR after a set time
 *
 * After implementing the hardware I realized that the optocoupler has a substantial phase delay of ~90°.
 * It crosses when the main line's voltage is at it's maximum. So we have to wait a bit after the pin change to meet the actual zero crossing
 * This is realized by using a one shot timer again and wait for a set amount of time (5ms is my initial guess).
 *
 * Luckily the optocoupler is triggered by rectified mains voltage. So this is symmetric for negative and positive half wave.
 * So the order is this:
 * optocoupler changes from low to high -> wait 5ms -> enable SSR -> wait 1ms -> disable SSR
 *
 * All ISRs need the ICACHE_RAM_ATTR
 */

extern Ticker oneShot; // used to synchronize the zero crossing interrupt with the actual start of a new half wave
static constexpr uint32_t Delay_MS_Zero_Crossing_Optocoupler { 0 };	/// the phases of optocoupler and power line are delayed
static constexpr uint32_t Delay_MS_SSR_Minimum_On_Time { 3 };/// the phases of optocoupler and power line are delayed

extern double Setpoint; //Input: The variable we're trying to control (double)
extern double Input; //Output: The variable that will be adjusted by the pid (double)
extern double Output; //Setpoint: The value we want to Input to maintain (double)

extern int zeroCrossingsCounter;

void ICACHE_RAM_ATTR ISRPullSSRLow();
void ICACHE_RAM_ATTR ISRZeroCrossing();
void ICACHE_RAM_ATTR ISROptocouplerZeroCrossing();

void initISR();

#endif /* SRC_ISR_H_ */
