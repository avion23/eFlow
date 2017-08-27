/*
 * myLogger.h
 *
 *  Created on: Jul 29, 2017
 *      Author: avion23
 */

#ifndef SRC_ESPLOGGER_H_
#define SRC_ESPLOGGER_H_

#ifdef UNIT_TESTING
#include <iostream>
#endif

#include <logger/telnetServer.h>

espLogger logger;

// logging class which outputs logs to all possible sinks
class espLogger {
public:
	espLogger(std::string prefix = "") :
			prefix(prefix) {
	}

	template<class T>
	espLogger &operator<<(const T &msg) {
		Serial << msg;
		telnet << msg;
		return *this;
	}
//	template<class T>
//	friend Log& operator <<(Log &instance, const T& arg) {
//		instance << "[" << instance.prefix << "] " << arg;
////		Serial << "[" << instance.prefix << "] " << arg;
////		log.udp << "[" << log.prefix << "] " << arg;
//		return instance;
//	}
//	inline Print &operator <<(Print &stream, T arg) {
//		return stream;
//	}

//	ostream& operator <<(ostream &os, const Log& log) {
//		Serial << "[" << prefix << "] " << param;
////		udp << "[" << prefix << "] " << param;
//		return log;
//	}

private:
	const std::string prefix;
	telnetServer telnet;
};

#endif /* SRC_ESPLOGGER_H_ */
