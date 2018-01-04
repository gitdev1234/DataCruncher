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
    }
    SECTION("test") {
        DC.vData = {6,6};
    }

        double averageBeforeZ  = DC.calcAverage();
        double varianceBeforeZ = DC.calcVariance();
        DC.zTransform(true);
        double averageAfterZ  = DC.calcAverage();
        double varianceAfterZ = DC.calcVariance();
        REQUIRE(averageAfterZ == 0);
        REQUIRE(varianceAfterZ == 1);
        DC.undoZTransform(averageBeforeZ,varianceAfterZ,true);
        REQUIRE(averageAfterZ == averageBeforeZ);
        REQUIRE(varianceAfterZ == varianceBeforeZ);
        REQUIRE(DC.vData[0] ==  3);
        REQUIRE(DC.vData[0] ==  6);
        REQUIRE(DC.vData[0] == -3);
        REQUIRE(DC.vData[0] ==  5);
        REQUIRE(DC.vData[0] ==  7);
        REQUIRE(DC.vData[0] ==  2);
        REQUIRE(DC.vData[0] ==  1);
        REQUIRE(DC.vData[0] ==  6);


}
