/*
 * deltaSigmaTest.hpp
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

#ifndef SRC_TEST_DELTASIGMATEST_HPP_
#define SRC_TEST_DELTASIGMATEST_HPP_

#include <deltaSigma.hpp>
#include "doctest.h"

TEST_CASE("0 percent")
{
	deltaSigma a(100);
	for (auto i = 0; i < 104; i++) {
		CHECK(a.update(0) == false);
		}
	}
TEST_CASE("100 percent")
{
	deltaSigma a(100);
	for (auto i = 0; i < 104; i++) {
		CHECK(a.update(100) == true);
		}
	}

TEST_CASE("50 percent")
{
	deltaSigma a(100);
	for (auto i = 0; i < 100; i++) {
		CHECK(a.update(50) == false);
			CHECK(a.update(50) == true);
		}
	}

TEST_CASE("25 percent")
{
	deltaSigma a(100);
	for (auto i = 0; i < 50; i++) {
		CHECK(a.update(25) == false);
			CHECK(a.update(25) == false);
			CHECK(a.update(25) == false);
			CHECK(a.update(25) == true);
		}
	}

TEST_CASE("10 percent")
{
	deltaSigma a(100);
	int percent = 10;
	for (auto i = 0; i < 12; i++) {
		CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == false);
			CHECK(a.update(percent) == true);
		}
	}

TEST_CASE("1 percent")
{
	deltaSigma a(100);
	int percent = 1;
	for (auto i = 0; i < 99; i++) {
		CHECK(a.update(percent) == false);
		}
	CHECK(a.update(percent) == true);
	}

#endif /* SRC_TEST_DELTASIGMATEST_HPP_ */
