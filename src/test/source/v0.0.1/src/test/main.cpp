
/* This macro is used to conditionally compile code on the host system for unit testing */
#ifdef UNIT_TESTING

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

// list all test files here
#include "deltaSigmaTest.hpp"
#include "ssrControlTest.hpp"

#endif
