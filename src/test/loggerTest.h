/*
 * loggerTest.h
 *
 *  Created on: Jul 29, 2017
 *      Author: avion23
 */

#ifndef SRC_TEST_LOGGERTEST_H_
#define SRC_TEST_LOGGERTEST_H_

#include <espLogger.h>
#include "doctest.h"

TEST_CASE("simple"){
	espLogger l;
	l << "teststring" << " second string";

}

#endif /* SRC_TEST_LOGGERTEST_H_ */
