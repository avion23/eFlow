///*
// * deltaSigmaTest.hpp
// *
// *  Created on: Jul 18, 2017
// *      Author: ralf
// *
// *
// Copyright (c) 2017, Ralf Waldukat
// All rights reserved.
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// */
//
//#ifndef SRC_TEST_DELTASIGMATEST_HPP_
//#define SRC_TEST_DELTASIGMATEST_HPP_
//
//#include "doctest.h"
//#include "deltaSigmaTestWhiteBox.hpp"
//
//TEST_CASE("0 percent")
//{
//	deltaSigma a(100);
//	for (auto i = 0; i < 104; i++) {
//		CHECK(a.update(0) == false);
//		}
//	}
//TEST_CASE("100 percent")
//{
//	deltaSigma a(100);
//	for (auto i = 0; i < 104; i++) {
//		CHECK(a.update(100) == true);
//		}
//	}
//
//TEST_CASE("50 percent")
//{
//	deltaSigma a(100);
//	for (auto i = 0; i < 100; i++) {
//		CHECK(a.update(50) == false);
//			CHECK(a.update(50) == true);
//		}
//	}
//
//TEST_CASE("25 percent")
//{
//	deltaSigma a(100);
//	for (auto i = 0; i < 50; i++) {
//		CHECK(a.update(25) == false);
//			CHECK(a.update(25) == false);
//			CHECK(a.update(25) == false);
//			CHECK(a.update(25) == true);
//		}
//	}
//
//TEST_CASE("10 percent")
//{
//	deltaSigma a(100);
//	int percent = 10;
//	for (auto i = 0; i < 12; i++) {
//		CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == true);
//		}
//	}
//
//TEST_CASE("1 percent")
//{
//	deltaSigma a(100);
//	int percent = 1;
//	for (auto i = 0; i < 99; i++) {
//		CHECK(a.update(percent) == false);
//		}
//	CHECK(a.update(percent) == true);
//	}
//
//TEST_CASE("10 percent to 90 percent")
//{
//	deltaSigma a(100);
//	int percent = 10;
//	for (auto i = 0; i < 3; i++) {
//		CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == true);
//		}
//	percent = 90;
//	CHECK(a.update(percent) == (false));
//	for (auto i = 0; i < 3; i++) {
//		CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == true);
//			CHECK(a.update(percent) == false);
//		}
//	}
//
//TEST_CASE("dc")
//{
//	int percent = 33;
//	deltaSigma a(100);
//	for (auto i = 0; i < 10; i++) {
//		CHECK(a.update(percent+1) == false);
//			CHECK(a.update(percent) == false);
//			CHECK(a.update(percent) == true);
//		}
//	}
//
//// I'm using a functor here because this function has a state (tracks if dc is there)
//// and has to be called in multiple tests
//class testForDc {
//public:
//	testForDc() :
//			dcPart(0), even(true) {
//	}
//
//	int operator()() {
//		return dcPart;
//	}
//	int operator()(bool param) {
//		if (param) {
//			if (even) {
//				dcPart++;
//			} else {
//				dcPart--;
//			}
//		}
//		even ^= true;
//		return dcPart;
//	}
//
//private:
//	int dcPart;
//	bool even;
//};
//
//TEST_CASE("test helper function")
//{
//	testForDc t;
//	for (auto i = 0; i < 50; i++) {
//		t(true);
//	}
//	CHECK(0 == t(false));
//	}
//
//TEST_CASE("test helper function")
//{
//	testForDc t;
//	for (auto i = 0; i < 50; i++) {
//		t(false);
//	}
//	CHECK(0 == t(false));
//	}
//
//TEST_CASE("test helper function")
//{
//	testForDc t;
//	for (auto i = 0; i < 50; i++) {
//		t(true);
//	}
//	CHECK(0 == t());
//	}
//
//TEST_CASE("test helper function")
//{
//	testForDc t;
//	for (auto i = 0; i < 50; i++) {
//		t(false);
//		t(true);
//	}
//	CHECK(-50 == t());
//	}
//TEST_CASE("test helper function")
//{
//	testForDc t;
//	for (auto i = 0; i < 50; i++) {
//		t(true);
//		t(false);
//	}
//	CHECK(50 == t(false));
//	}
//
//TEST_CASE("dc-free 50 percent check average")
//{
//	auto percent = 50;
//	deltaSigma a(100, true);
//	auto sum = 0;
//	for (auto i = 0; i < 100; i++) {
//		sum += a.update(percent);
//	}
//	CHECK(50 == sum);
//	}
//
//TEST_CASE("dc-free 50 percent check dc part")
//{
//	auto percent = 50;
//	deltaSigma a(100, true);
//	testForDc t;
//	for (auto i = 0; i < 100; i++) {
//		t(a.update(percent));
//	}
//	CHECK(abs(t()) <= 2 );
//	}
//
//TEST_CASE("dc-free 25 percent check average")
//{
//	auto percent = 25;
//	deltaSigma a(100, true);
//	auto sum = 0;
//	for (auto i = 0; i < 100; i++) {
//		sum += a.update(percent);
//	}
//	CHECK(percent >= sum - 1);
//	CHECK(percent <= sum + 1);
//	}
//
//TEST_CASE("dc-free 25 percent check dc part")
//{
//	auto percent = 25;
//	deltaSigma a(100, true);
//	testForDc t;
//	for (auto i = 0; i < 100; i++) {
//		t(a.update(percent));
//	}
//	CHECK(abs(t()) <= 2 );
//	}
//TEST_CASE("dc-free 33 percent check average")
//{
//	auto percent = 33;
//	deltaSigma a(100, true);
//	auto sum = 0;
//	for (auto i = 0; i < 100; i++) {
//		sum += a.update(percent);
//	}
//	CHECK(33 == sum);
//	}
//
//TEST_CASE("dc-free 33 percent check dc part")
//{
//	auto percent = 33;
//	deltaSigma a(100, true);
//	testForDc t;
//	for (auto i = 0; i < 100; i++) {
//		t(a.update(percent));
//	}
//	CHECK(abs(t()) <= 2 );
//	}
//TEST_CASE("dc-free 20 percent check average")
//{
//	auto percent = 20;
//	deltaSigma a(100, true);
//	auto sum = 0;
//	for (auto i = 0; i < 100; i++) {
//		sum += a.update(percent);
//	}
//	CHECK(percent >= sum - 1);
//	CHECK(percent <= sum + 1);
//	}
//
//TEST_CASE("dc-free 20 percent check dc part")
//{
//	auto percent = 20;
//	deltaSigma a(100, true);
//	testForDc t;
//	for (auto i = 0; i < 100; i++) {
//		t(a.update(percent));
//	}
//	CHECK(abs(t()) <= 2 );
//	}
//
//TEST_CASE("dc-free 19 percent check dc part")
//{
//	auto percent = 19;
//	deltaSigma a(100, true);
//	testForDc t;
//	for (auto i = 0; i < 100; i++) {
//		t(a.update(percent));
//	}
//	CHECK(abs(t()) <= 5);
//	}
//
//TEST_CASE("dc-free sweep check average")
//{
//	for (int percent = 0; percent <= 100; percent++) {
//		deltaSigma a(100, true);
//		auto sum = 0;
//		for (auto i = 0; i < 100; i++) {
//			sum += a.update(percent);
//		}
//		CHECK(percent >= sum - 3);
//		CHECK(percent <= sum + 3);
//		}
//	}
//
//TEST_CASE("dc-free sweep check dc part")
//{
//	for (int percent = 0; percent <= 100; percent++) {
//		deltaSigma a(100, true);
//		testForDc t;
//		for (auto i = 0; i < 100; i++) {
//			t(a.update(percent));
//		}
//		CHECK(abs(t()) <= 2);
//		}
//	}
//
//TEST_CASE("dc-free sweep check average for full 8 bit")
//{
//	for (int percent = 0; percent <= 255; percent++) {
//		deltaSigma a(255, true);
//		auto sum = 0;
//		for (auto i = 0; i < 255; i++) {
//			sum += a.update(percent);
//		}
//		CHECK(percent >= sum - 3);
//		CHECK(percent <= sum + 3);
//		}
//	}
//
//TEST_CASE("dc-free sweep check dc part for full 8 bit")
//{
//	for (int percent = 0; percent <= 255; percent++) {
//		deltaSigma a(255, true);
//		testForDc t;
//		for (auto i = 0; i < 255; i++) {
//			t(a.update(percent));
//		}
//		CHECK(abs(t()) <= 2);
//		}
//	}
//#endif /* SRC_TEST_DELTASIGMATEST_HPP_ */
