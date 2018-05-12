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
#include <logger/telnetServer.h>
#include <WiFiServer.h>
#include <vector>
#include <string>
#include <Streaming.h>

class telnetServer {
public:
	telnetServer(int port = 23) :
			serverInstance(port), serverClients(MAX_SERVER_CLIENTS) {

		serverInstance.begin();
		serverInstance.setNoDelay(true); // ESP BUG ?
	}

	// write to all connected clients
	template<typename T> size_t write(const T src) {
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
				i.print(src);
				delay(1);
			}
		}
	}

	telnetServer& operator<<(const int arg) {
		write(arg);
		return *this;
	}
	telnetServer& operator<<(const std::string& arg) {
		write(arg.c_str());
		return *this;
	}
	telnetServer& operator<<(const _EndLineCode arg) {
		// Everything is a string if you try hard enough
		write(((std::string) "\n\r").c_str());
		return *this;
	}

protected:
	static constexpr int MAX_SERVER_CLIENTS { 4 };
	std::vector<WiFiClient> serverClients;
	WiFiServer serverInstance;

	// ansi stuff, could always use printf instead of concat
	std::string ansiPRE = "\033"; // escape code
	std::string ansiHOME = "\033[H"; // cursor home
	std::string ansiESC = "\033[2J"; // esc
	std::string ansiCLC = "\033[?25l"; // invisible cursor

	std::string ansiEND = "\033[0m";   // closing tag for styles
	std::string ansiBOLD = "\033[1m";

	std::string ansiRED = "\033[41m"; // red background
	std::string ansiGRN = "\033[42m"; // green background
	std::string ansiBLU = "\033[44m"; // blue background

	std::string ansiREDF = "\033[31m"; // red foreground
	std::string ansiGRNF = "\033[34m"; // green foreground
	std::string ansiBLUF = "\033[32m"; // blue foreground
	std::string BELL = "\a";
};

#endif /* SRC_TELNETSERVER_H_ */

