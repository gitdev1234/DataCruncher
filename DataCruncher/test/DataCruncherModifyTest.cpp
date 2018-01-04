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
    const double TOLERANCE = 0.01;

    DataCruncher DCBefore, DCAfter;

    SECTION("zTransform with integers") {
        SECTION("zTransform with small unsigned integers") {
            DCBefore.vData = {3,6,3,5,7,2,1,6};
        }

        SECTION("zTransform with small signed integers") {
            DCBefore.vData = {-3,-6,-3,-5,-7,-2,-1,-6};
        }

        SECTION("zTransform with small mixed-signed integers") {
            DCBefore.vData = {3,6,-3,5,7,2,-1,-6};
        }

        SECTION("zTransform with big unsigned integers") {
            DCBefore.vData = {23425234,7696858,84863637,82828374,4738384};
        }

        SECTION("zTransform with big signed integers") {
            DCBefore.vData = {-23425234,-7696858,-84863637,-82828374,-4738384};
        }

        SECTION("zTransform with big mixed-signed integers") {
            DCBefore.vData = {-23425234,7696858,84863637,-82828374,-4738384};
        }
    }

    SECTION("zTransform with doubles") {
        SECTION("zTransform with small unsigned doubles") {
            DCBefore.vData = {3.123,6.0,3.1,5.1234,7.3,2.0,1.134,6.5};
        }

        SECTION("zTransform with small signed doubles") {
            DCBefore.vData = {-3.123,-6.0,-3.1,-5.1234,-7.3,-2.0,-1.134,-6.5};
        }

        SECTION("zTransform with small mixed-signed doubles") {
            DCBefore.vData = {-3.123,6.0,-3.1,-5.1234,7.3,-2.0,-1.134,-6.5};
        }

        SECTION("zTransform with big unsigned doubles") {
            DCBefore.vData = {23425234.234,7696858.22222,84863637.0,82828374.125,4738384.3};
        }

        SECTION("zTransform with big signed integers") {
            DCBefore.vData = {-23425234.234,-7696858.22222,-84863637.0,-82828374.125,-4738384.3};
        }

        SECTION("zTransform with big mixed-signed integers") {
            DCBefore.vData = {-23425234.234,-7696858.22222,84863637.0,-82828374.125,4738384.3};
        }
    }

    DCAfter = DCBefore;

    DCAfter.zTransform(true);
    REQUIRE(DCAfter.vData.nearlyEqual(DCAfter.calcAverage(),0,TOLERANCE));
    REQUIRE(DCAfter.vData.nearlyEqual(DCAfter.calcVariance(),1,TOLERANCE));
    DCAfter.undoZTransform(DCBefore.calcAverage(),DCBefore.calcStdDeviation(),true);
    REQUIRE(DCAfter.vData.nearlyEqual(DCBefore.calcAverage(),DCAfter.calcAverage(),TOLERANCE));
    REQUIRE(DCAfter.vData.nearlyEqual(DCBefore.calcStdDeviation(),DCAfter.calcStdDeviation(),TOLERANCE));
    for (int i = 0; i < DCAfter.vData.getSize(); i++) {
        REQUIRE(DCBefore.vData.nearlyEqual(DCBefore.vData[i],DCAfter.vData[i],TOLERANCE));
    }



}
