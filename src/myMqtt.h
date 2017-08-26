/*
 * myMqtt.hpp
 *
 *  Created on: Oct 16, 2016
 *      Author: avion
 */

#ifndef SRC_MYMQTT_H_
#define SRC_MYMQTT_H_

//#include <AsyncMqttClient.h>

extern const String mqttClientId;

void mqttSetup();
void publishString(String str, String value);

#endif /* SRC_MYMQTT_H_ */
