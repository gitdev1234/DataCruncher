/**
* DataCruncherModifyTest.cpp
* Purpose: implements unit-tests for modifying functions of the DataCruncher-class
*
* @author Wall.Of.Death
* @version 2.2
*/

// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!

#include "catch.hpp"
#include "DataCruncher.h"

TEST_CASE("Test DataCruncher.zTransform") {
    DataCruncher DC;
    SECTION("test") {
        DC.vData = {3,6,-3,5,7,2,1,6};
        DC.zTransform(true);
        DC.zTransform(false);

    }
}