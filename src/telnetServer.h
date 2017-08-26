/*
 * telnet.h
 *
 *  Created on: Aug 5, 2017
 *      Author: avion23
 */

#ifndef SRC_TELNETSERVER_H_
#define SRC_TELNETSERVER_H_

#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <telnetServer.h>
#include <WiFiServer.h>
#include <vector>
#include <Streaming.h>

// ansi stuff, could always use printf instead of concat
String ansiPRE = "\033"; // escape code
String ansiHOME = "\033[H"; // cursor home
String ansiESC = "\033[2J"; // esc
String ansiCLC = "\033[?25l"; // invisible cursor

String ansiEND = "\033[0m";   // closing tag for styles
String ansiBOLD = "\033[1m";

String ansiRED = "\033[41m"; // red background
String ansiGRN = "\033[42m"; // green background
String ansiBLU = "\033[44m"; // blue background

String ansiREDF = "\033[31m"; // red foreground
String ansiGRNF = "\033[34m"; // green foreground
String ansiBLUF = "\033[32m"; // blue foreground
String BELL = "\a";

class telnetServer {
public:
	telnetServer(int port = 23) :
			serverInstance(port), serverClients(MAX_SERVER_CLIENTS) {

		serverInstance.begin();
		Serial << "[TLN] Starting telnet server on port " << (String) port
				<< endl;
		serverInstance.setNoDelay(true); // ESP BUG ?
	}

	// write to all connected clients
	template<typename T> size_t write(const T &src) {
		//check if there are any new clients
		if (serverInstance.hasClient()) {
			for (auto &i : serverClients) {
				//find free/disconnected spot
				if (!i || !i.connected()) {
					if (i)
						i.stop();
					i = serverInstance.available();
					continue;
				}
			}
			//no free/disconnected spot so reject
			WiFiClient serverClient = serverInstance.available();
			serverClient.stop();
		}
		//check clients for data
		for (auto &i : serverClients) {
			if (i && i.connected()) {
				// receiving
				if (i.available()) {
					//get data from the telnet client and push it to the UART
					while (i.available())
						Serial.write(i.read());
				}
			}
		}
		for (auto &i : serverClients) {
			if (i && i.connected()) {
				// sending
				i.write(src);
				delay(1);
			}
		}
	}

	telnetServer& operator<<(const int arg) {
		write(((String) arg).c_str());
		return *this;
	}
	telnetServer& operator<<(const String& arg) {
		write(arg.c_str());
		return *this;
	}
	telnetServer& operator<<(const _EndLineCode arg) {
		// Everything is a string if you try hard enough
		write(((String) "\n\r").c_str());
		return *this;
	}

protected:
	static constexpr int MAX_SERVER_CLIENTS { 4 };
	std::vector<WiFiClient> serverClients;
	WiFiServer serverInstance;
};

#endif /* SRC_TELNETSERVER_H_ */

