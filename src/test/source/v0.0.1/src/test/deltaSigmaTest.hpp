/*
 * ssrTest.hpp
 *
 *  Created on: Jul 18, 2017
 *      Author: ralf
 */

#ifndef SRC_TEST_DELTASIGMATEST_HPP_
#define SRC_TEST_DELTASIGMATEST_HPP_

#include "doctest.h"
#include "deltaSigma.hpp"

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
