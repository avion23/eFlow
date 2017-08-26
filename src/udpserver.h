/*
 * udpserver.hpp
 *
 *  Created on: Apr 11, 2017
 *      Author: ralf
 */

#ifndef SRC_UDPSERVER_H_
#define SRC_UDPSERVER_H_

#include <ESP8266WiFi.h>
#include <Streaming.h>

// wrapper class for WifiServer
class udpServer {
public:
	udpServer(unsigned int port = 23) :
			server(port) {
		server.begin();
		server.setNoDelay(true);
	}

	template<class T>
	udpServer &operator<<(const T &msg) {
		this->print(msg);
		return *this;
	}
//	template<typename T>
//	friend udpServer& operator <<(udpServer& udp, const T& param) {
//		udp.print(param);
//		return udp;
//	}
	void print(const char* param) {
		for (int i = 0; i < maxClients; i++) {
			if (serverClients[i] && serverClients[i].connected()) {
				//			serverClients[i].write(sbuf, len);
//				serverClients[i].write(param, strlen(param));
				serverClients[i].print(param);
				delay(1);
			}
		}
	}
	void print(const String& param) {
		for (int i = 0; i < maxClients; i++) {
			if (serverClients[i] && serverClients[i].connected()) {
				//			serverClients[i].write(sbuf, len);
				serverClients[i].write(param.c_str(), param.length());
				delay(1);
			}
		}
	}
	template<class T>
	void print(const T& param) {
		for (int i = 0; i < maxClients; i++) {
			if (serverClients[i] && serverClients[i].connected()) {
				//			serverClients[i].write(sbuf, len);
				serverClients[i].write(param, strlen(param));
				delay(1);
			}
		}
	}
//	void print(const int& param) {
//		for (int i = 0; i < maxClients; i++) {
//			String output(param);
//			if (serverClients[i] && serverClients[i].connected()) {
//				//			serverClients[i].write(sbuf, len);
//				serverClients[i].write(output, output.len);
//				delay(1);
//			}
//		}
//	}
	void print(const enum _EndLineCode end) {
		for (int i = 0; i < maxClients; i++) {
			if (serverClients[i] && serverClients[i].connected()) {
				//			serverClients[i].write(sbuf, len);
				serverClients[i].write("\n");
				delay(1);
			}
		}
	}
private:
	static const int maxClients = 5;
	WiFiServer server;
	WiFiClient serverClients[maxClients];
};

//void udpServerLoop() {
//
//	for (int i = 0; i < MAX_SRV_CLIENTS; i++) {
//		if (serverClients[i] && serverClients[i].connected()) {
////			serverClients[i].write(sbuf, len);
//			delay(1);
//		}
//	}
//}
//	// netcat debug messages
//	uint8_t i;
//	//check if there are any new clients
//	if (serverUdp.hasClient()) {
//		for (i = 0; i < MAX_SRV_CLIENTS; i++) {
//			//find free/disconnected spot
//			if (!serverClientsUdp[i] || !serverClientsUdp[i].connected()) {
//				if (serverClientsUdp[i])
//					serverClientsUdp[i].stop();
//				serverClientsUdp[i] = serverUdp.available();
//				continue;
//			}
//		}
//		//no free/disconnected spot so reject
//		WiFiClient serverClient = serverUdp.available();
//		serverClient.stop();
//	}
//	for (i = 0; i < MAX_SRV_CLIENTS; i++) {
//		if (serverClientsUdp[i] && serverClientsUdp[i].connected()) {
////			serverClientsUdp[i].print("temperature: ");
////			serverClientsUdp[i].print(temperatureNow);
////			serverClientsUdp[i].print("\n");
////			serverClientsUdp[i].print("voltage: ");
////			serverClientsUdp[i].print(voltageNow);
////			serverClientsUdp[i].print("\n");
////			serverClientsUdp[i].print("state: ");
////			serverClientsUdp[i].print(toString(state));
////			serverClientsUdp[i].print("\n");
//		}
//	}
//}

#endif /* SRC_UDPSERVER_H_ */
