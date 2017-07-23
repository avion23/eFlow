/*
 * deltaSigmaTestWhiteBox.hpp
 *
 *  Created on: Jul 23, 2017
 *      Author: Ralf Waldukat
 *
 Copyright (c) 2017, Ralf Waldukat
 All rights reserved.
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef SRC_TEST_DELTASIGMATESTWHITEBOX_HPP_
#define SRC_TEST_DELTASIGMATESTWHITEBOX_HPP_

#include "deltaSigma.hpp"
#include "doctest.h"
#include <iostream>

/* I was really fed up with trying to understand why my Implementation didn't work
 * I needed a way to consistently log the unit under tests behaviour. At the same time,
 * I didn't want to pollute the class with debug statements
 * This is why I implemented deltaSigmaWhiteBoxTest. It uses the functionality
 * of the base class and adds some std::cout output. You can safely ignore or delete
 * this class in case you ever change the implementation.
 */
class deltaSigmaWhiteBoxTest: deltaSigma {
	using deltaSigma::deltaSigma;	// delegate
public:
	bool update(unsigned int percent) {

		std::cout << "integrator = " << integrator << "\t polarity = "
				<< polarity << "\t dcPressure = " << dcPressure;
		bool retValue = deltaSigma::update(percent);
		std::cout << "\t result = " << retValue << std::endl;
		return retValue;
	}
};

#endif /* SRC_TEST_DELTASIGMATESTWHITEBOX_HPP_ */
