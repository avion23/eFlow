/*
 * deltaSigma.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ralf
 *
 *
 Copyright (c) 2017, Ralf Waldukat
 All rights reserved.
 Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#ifndef SRC_DELTASIGMA_HPP_
#define SRC_DELTASIGMA_HPP_
/**
 * This class was intended to provide an easy way to convert a PWM / Duty cycle value
 * into a series of half ways on the AC mains power
 *
 * The dc free option is intended to avoid driving transformers into saturation
 */
class deltaSigma {
public:
	/** @param: when is a full cycle finished? e.g. 100 percent = 100
	 */
	deltaSigma(unsigned int delta) :
			deltaSigma(delta, false) {
	}

	/** @param: when is a full cycle finished? e.g. 100 percent = 100
	 *  @param true if this should be without DC
	 *  @warning this feature introduces a delay
	 */
	deltaSigma(unsigned int max, bool dcFree) :
			integrator(0), threshold(max), dcFreeFeature(dcFree), dcPressure(
					0), polarity(1) {
	}

	/** updates the delta sigma converter with a new value and fetches the next state
	 * @param the current desired percent valueb
	 * @return true if the threshold has been reached, false otherwise
	 */
	bool update(unsigned int percent);

protected:
	// private -> protected for white box test
	int integrator;			/// integrates the percent argument
	const int threshold;		/// the value at which true should be returned
	const bool dcFreeFeature;	/// enables the dc-free functionality
	int dcPressure;	 /// tracks which polarity's side has a surplus
	int polarity;	/// tracks the current half wave's polarity
	static constexpr int maxDcPressure = 2; /// how many half waves in the wrong direction are allowed
};

#endif /* SRC_DELTASIGMA_HPP_ */
