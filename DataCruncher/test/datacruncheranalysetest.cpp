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
    DataCruncher dCruncher;
    SECTION("calcAverage with integers") {
        dCruncher.vData.push_back(3);
        dCruncher.vData.push_back(6);
        dCruncher.vData.push_back(-3);
        dCruncher.vData.push_back(5);
        dCruncher.vData.push_back(7);
        dCruncher.vData.push_back(2);
        dCruncher.vData.push_back(1);
        dCruncher.vData.push_back(6);
        REQUIRE (dCruncher.calcAverage() == 3.375);

    }
}
