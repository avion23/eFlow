/*
 * hardwareConfig.h
 *
 *  Created on: Sep 3, 2017
 *      Author: avion23
 */

#ifndef SRC_HARDWARECONFIG_H_
#define SRC_HARDWARECONFIG_H_


// These buttons are exposed on the nodemcu dev board
const auto PIN_USER_INPUT = 16; // What can we do with this button?
const auto PIN_ADMIN_MODE = 0; // If pressed within 5 seconds of power on, enter admin mode

const auto PIN_HTTP_LED = 0;     // Toggled on HTTP Status
const auto PIN_WIFI_LED = 2; // Toggled on when AP connected

const auto PIN_SSR_OUTPUT = 13; // This is where the SSR is connected
const auto PIN_INPUT_OPTOCOUPLER = 14;	// pin to sense the zero crossing

// Pins for thermocouples
const auto PIN_SPI_D0 = 4;
const auto PIN_SPI_CS_A = 12;
const auto PIN_SPI_CLK = 5;



#endif /* SRC_HARDWARECONFIG_H_ */
