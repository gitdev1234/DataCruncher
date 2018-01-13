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

TEST_CASE("Test DataCruncher calc analytical values") {
    const double TOLERANCE = 0.01;
    DataCruncher DC;


    SECTION("calc analytical values with integers") {
        SECTION("calc analytical values with small unsigned integers") {
            DC.vData = {3,6,3,5,7,2,1,6};
            REQUIRE (DC.calcAverage() == 4.125);

            DC.vData = {25};
            REQUIRE (DC.calcAverage() == 25);

            DC.vData = {2, 3, 4};
            REQUIRE (DC.calcAverage() == 3);

            DC.vData = {2, 4, 8, 6, 4, 3, 32, 66, 7, 8, 9, 7, 54};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),16.1538461538462,TOLERANCE));

            DC.vData = {0,0,0,0,0,0,0,0,0,0,0,0,0};
            REQUIRE (DC.calcAverage() == 0);
        }

        SECTION("calc analytical values with small signed integers") {
            DC.vData = {-3,-6,-3,-5,-7,-2,-1,-6};
            REQUIRE (DC.calcAverage() == -4.125);

            DC.vData = {-25};
            REQUIRE (DC.calcAverage() == -25);

            DC.vData = {-2, -3, -4};
            REQUIRE (DC.calcAverage() == -3);

            DC.vData = {-2, -4, -8, -6, -4, -3, -32, -66, -7, -8, -9, -7, -54};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-16.1538461538462,TOLERANCE));

            DC.vData = {-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0};
            REQUIRE (DC.calcAverage() == 0);
        }

        SECTION("calc analytical values with small mixed-signed integers") {
            DC.vData = {3,6,-3,5,7,2,1,6};
            REQUIRE (DC.calcAverage() == 3.375);

            DC.vData = {-25};
            REQUIRE (DC.calcAverage() == -25);

            DC.vData = {-2, 3, -4};
            REQUIRE (DC.calcAverage() == -1);

            DC.vData = {-2, 4, -8, 6, -4, 3, -32, 66, -7, -8, -9, -7, -54};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-4,TOLERANCE));

            DC.vData = {-0,-0,-0,0,-0,-0,0,-0,0,-0,-0,-0,-0};
            REQUIRE (DC.calcAverage() == 0);

        }

        SECTION("calc analytical values with big unsigned integers") {
            DC.vData = {10000,234235,290294098,2340209,23232346574};
            REQUIRE (DC.calcAverage() == 4705045023.2);

            DC.vData = {2523423423564356};
            REQUIRE (DC.calcAverage() == 2523423423564356);

            DC.vData = {2234, 3423234234, 423333};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),1141219933.66667,TOLERANCE));

            DC.vData = {2123, 467788, 8543, 62222222, 4345345, 33452456, 3223452, 623452356, 72345235, 845674567, 95678, 75678586, 545678568};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),174357455.307692,TOLERANCE));

        }

        SECTION("calc analytical values with big signed integers") {
            DC.vData = {-10000,-234235,-290294098,-2340209,-23232346574};
            REQUIRE (DC.calcAverage() == -4705045023.2);

            DC.vData = {-2523423423564356};
            REQUIRE (DC.calcAverage() == -2523423423564356);

            DC.vData = {-2234, -3423234234, -423333};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-1141219933.66667,TOLERANCE));

            DC.vData = {-2123, -467788, -8543, -62222222, -4345345, -33452456, -3223452, -623452356, -72345235, -845674567, -95678, -75678586, -545678568};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-174357455.307692,TOLERANCE));
        }

        SECTION("calc analytical values with big mixed-signed integers") {
            DC.vData = {-10000,234235,290294098,-2340209,-23232346574};
            REQUIRE (DC.calcAverage() == -4588833690);

            DC.vData = {-2523423423564356};
            REQUIRE (DC.calcAverage() == -2523423423564356);

            DC.vData = {-2234, 3423234234, -423333};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),1140936222.33333,TOLERANCE));

            DC.vData = {-2123, 467788, -8543, 62222222, -4345345, -33452456, 3223452, 623452356, -72345235, -845674567, -95678, -75678586, -545678568};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-68301175.6153846,TOLERANCE));
        }
    }

    SECTION("calc analytical values with doubles") {
        SECTION("calc analytical values with small unsigned doubles") {
            DC.vData = {3.234,6.22,3.234234,5.22,7.234,2.00,1.02,6.234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),4.29952925,TOLERANCE));

            DC.vData = {25.234234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),25.234234,TOLERANCE));

            DC.vData = {2.23525, 3.474, 4.457457};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),3.3889,TOLERANCE));

            DC.vData = {2.22, 4.33, 8.44, 6.345345, 4.55, 3.63463, 32.66, 66.77, 7.88888, 8.2342, 9.999, 7.0, 54.01};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),16.6217,TOLERANCE));

            DC.vData = {0.0,0.00,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0000,0.0,0.0};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),0.00000,TOLERANCE));
        }

        SECTION("calc analytical values with small signed doubles") {
            DC.vData = {-3.234,-6.22,-3.234234,-5.22,-7.234,-2.00,-1.02,-6.234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-4.29952925,TOLERANCE));

            DC.vData = {-25.234234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-25.234234,TOLERANCE));

            DC.vData = {-2.23525, -3.474, -4.457457};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-3.3889,TOLERANCE));

            DC.vData = {-2.22, -4.33, -8.44, -6.345345, -4.55, -3.63463, -32.66, -66.77, -7.88888, -8.2342, -9.999, -7.0, -54.01};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-16.6217,TOLERANCE));

            DC.vData = {-0.0,-0.00,-0.0,-0.0,-0.0,-0.0,-0.0,-0.0,-0.0,-0.0,-0.0000,-0.0,-0.0};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),0.00000,TOLERANCE));
        }

        SECTION("calc analytical values with small mixed-signed doubles") {
            DC.vData = {-3.234,6.22,-3.234234,5.22,-7.234,-2.00,-1.02,-6.234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-1.43952925,TOLERANCE));

            DC.vData = {-25.234234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-25.234234,TOLERANCE));

            DC.vData = {-2.23525, 3.474, -4.457457};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-1.0729023333,TOLERANCE));

            DC.vData = {-2.22, -4.33, 8.44, -6.345345, -4.55, 3.63463, 32.66, -66.77, 7.88888, -8.2342, -9.999, -7.0, -54.01};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-8.5257719231,TOLERANCE));

            DC.vData = {-0.0,-0.00,-0.0,0.0,0.0,0.0,-0.0,0.0,-0.0,-0.0,-0.0000,-0.0,-0.0};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),0.00000,TOLERANCE));
        }

        SECTION("calc analytical values with big unsigned doubles") {
            DC.vData = {10000.001,234235.002,290294098.23,2340209.234526,23232346574.142432};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),4705045023.32199,TOLERANCE));

            DC.vData = {2523423423564356.123412341234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),2523423423564356.123412341234,TOLERANCE));

            DC.vData = {2234.5235, 3423234234.334555, 423333.96969};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),1141219934.27591,TOLERANCE));

            DC.vData = {2123.234234, 467788.111, 8543.87656556, 62222222.222222, 4345345.11111, 33452456.445646, 3223452.234243, 623452356.9375967, 72345235.1, 845674567.000, 95678.134, 75678586.123552, 545678568.83758837};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),174357455.643674,TOLERANCE));
        }

        SECTION("calc analytical values with big signed integers") {
            DC.vData = {-10000.001,-234235.002,-290294098.23,-2340209.234526,-23232346574.142432};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-4705045023.32199,TOLERANCE));

            DC.vData = {-2523423423564356.123412341234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-2523423423564356.123412341234,TOLERANCE));

            DC.vData = {-2234.5235, -3423234234.334555, -423333.96969};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-1141219934.27591,TOLERANCE));

            DC.vData = {-2123.234234, -467788.111, -8543.87656556, -62222222.222222, -4345345.11111, -33452456.445646, -3223452.234243, -623452356.9375967, -72345235.1, -845674567.000, -95678.134, -75678586.123552, -545678568.83758837};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-174357455.643674,TOLERANCE));
        }

        SECTION("calc analytical values with big mixed-signed doubles") {
            DC.vData = {-10000.001,234235.002,-290294098.23,2340209.234526,-23232346574.142432};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-4704015245.62738,TOLERANCE));

            DC.vData = {-2523423423564356.123412341234};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-2523423423564356.123412341234,TOLERANCE));

            DC.vData = {-2234.5235, 3423234234.334555, -423333.96969};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),1140936221.94712,TOLERANCE));

            DC.vData = {-2123.234234, 467788.111, -8543.87656556, 62222222.222222, 4345345.11111, -33452456.445646, -3223452.234243, -623452356.9375967, 72345235.1, 845674567.000, 95678.134, -75678586.123552, -545678568.83758837};
            REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-22795788.616238,TOLERANCE));
        }
    }



}
