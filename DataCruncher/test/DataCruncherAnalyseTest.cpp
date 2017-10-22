/**
* DataCruncherAnalyseTest.cpp
* Purpose: implements unit-tests for analysing functions of the DataCruncher-class
*
* @author Wall.Of.Death
* @version 2.2
*/

// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!

#include "catch.hpp"
#include "DataCruncher.h"

TEST_CASE("Test DataCruncher.calcAverage") {
    DataCruncher DC;

    SECTION("calcAverage with integers") {
        DC.vData = {3,6,-3,5,7,2,1,6};
        REQUIRE (DC.calcAverage() == 3.375);

        DC.vData = {10000,234235,290294098,2340209,23232346574};
        REQUIRE (DC.calcAverage() == 4705045023.2);

        DC.vData = {-23425234,-7696858,-84863637,-82828374,-4738384};
        REQUIRE (DC.calcAverage() == -40710497.4);

        DC.vData = {0,0,0,0,0,0,0,0,0,0,0,0,0};
        REQUIRE (DC.calcAverage() == 0);

    }


}
