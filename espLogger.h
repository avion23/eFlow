/*
 * myLogger.h
 *
 *  Created on: Jul 29, 2017
 *      Author: avion23
 */

#ifndef SRC_ESPLOGGER_H_
#define SRC_ESPLOGGER_H_

#include <logger/telnetServer.h>
#include <functional>
#include <string>

// logging class which outputs logs to all possible sinks
class espLogger {
public:
	espLogger(std::string prefix = "",
			std::function<uint32_t(void)> f = nullptr) :
			prefix(prefix), getTimestamp(f), startOfNewLine(true) {
	}

	espLogger& operator<<(std::string &msg) {
		if (getTimestamp && startOfNewLine) { // prepend timeStamp
			uint32_t timeNow = getTimestamp();
			Serial << timeNow << delimiter.c_str();
			telnet << timeNow << delimiter;
			startOfNewLine = false;
		}
		Serial << msg.c_str();
		telnet << msg;
		if ((msg.substr(msg.length() - 2) == (std::string) "\n\r")
				|| (msg.substr(msg.length() - 1) == (std::string) "\n")) {
			startOfNewLine = true;
		}
		return *this;
	}
	espLogger& operator<<(const char* msg) {
		if (getTimestamp && startOfNewLine) { // prepend timeStamp
			uint32_t timeNow = getTimestamp();
			Serial << timeNow << delimiter.c_str();
			telnet << timeNow << delimiter;
			startOfNewLine = false;
		}
		Serial << msg;
		telnet << msg;
		if ((msg[sizeof(msg) - 1] == '\n') || (msg[sizeof(msg) - 2] == '\n')) {
			startOfNewLine = true;
		}
		return *this;
	}

	espLogger& operator<<(const _EndLineCode arg) {
		*this << "\n\r";
		startOfNewLine = true;
		return *this;
	}

	espLogger& operator<<(const int arg) {
		Serial << arg;
		telnet << arg;
		startOfNewLine = false;
		return *this;
	}

private:
	const std::string prefix;
	telnetServer telnet;
	const std::function<uint32_t(void)> getTimestamp;bool startOfNewLine;
	const std::string delimiter { ": " }; // delimiter between timestamp and message
};

#endif /* SRC_ESPLOGGER_H_ */
