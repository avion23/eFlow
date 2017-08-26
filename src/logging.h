/*
 * logging.h
 *
 *  Created on: Jul 29, 2017
 *      Author: avion23
 */

#ifndef SRC_LOGGING_H_
#define SRC_LOGGING_H_

#include <Streaming.h>
//#include <iostream>

using namespace std;

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct structlog {
    bool headers = false;
    typelog level = WARN;
};

extern structlog LOGCFG;

class LOG {
public:
    LOG() {}
    LOG(typelog type) {
        msglevel = type;
        if(LOGCFG.headers) {
            operator << ("["+getLabel(type)+"]");
        }
    }
    ~LOG() {
        if(opened) {
//            cout << std::endl;
        	Serial << endl;
        }
        opened = false;
    }
    template<class T>
    LOG &operator<<(const T &msg) {
        if(msglevel >= LOGCFG.level) {
//            cout << msg;
            Serial << msg;
            opened = true;
        }
        return *this;
    }
private:
    bool opened = false;
    typelog msglevel = DEBUG;
    inline String getLabel(typelog type) {
        String label;
        switch(type) {
            case DEBUG: label = "DEBUG"; break;
            case INFO:  label = "INFO "; break;
            case WARN:  label = "WARN "; break;
            case ERROR: label = "ERROR"; break;
        }
        return label;
    }
};




#endif /* SRC_LOGGING_H_ */
