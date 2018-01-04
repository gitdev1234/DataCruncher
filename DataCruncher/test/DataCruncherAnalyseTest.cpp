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
        SECTION("zTransform with small unsigned integers") {
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
                DC.vData = {3.123,6.0,3.1,5.1234,7.3,2.0,1.134,6.5};
            }

            SECTION("calc analytical values with small signed doubles") {
                DC.vData = {-3.123,-6.0,-3.1,-5.1234,-7.3,-2.0,-1.134,-6.5};
            }

            SECTION("calc analytical values with small mixed-signed doubles") {
                DC.vData = {-3.123,6.0,-3.1,-5.1234,7.3,-2.0,-1.134,-6.5};
            }

            SECTION("calc analytical values with big unsigned doubles") {
                DC.vData = {23425234.234,7696858.22222,84863637.0,82828374.125,4738384.3};
            }

            SECTION("calc analytical values with big signed integers") {
                DC.vData = {-23425234.234,-7696858.22222,-84863637.0,-82828374.125,-4738384.3};
            }

            SECTION("calc analytical values with big mixed-signed integers") {
                DC.vData = {-23425234.234,-7696858.22222,84863637.0,-82828374.125,4738384.3};
            }


    }


    SECTION("calcAverage with doubles") {
        const double TOLERANCE = 0.00001;
        DC.vData = {25234.345, -96858.2234, 863637.2342, -8374.963, 738384.234234424};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),304404.5254068850,TOLERANCE));

        DC.vData = {25234.345, 96858.2234, 863637.2342, 8374.963, 738384.234234424};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),346497.7999668850,TOLERANCE));

        DC.vData = {-23425234.345, -7696858.2234, -84863637.234235, -82828374.94563, -4738384.234243};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),-40710497.7965016000,TOLERANCE));

        DC.vData = {25.234235265234};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),25.234235265234,TOLERANCE));

        DC.vData = {979734.32345, 234.235554, 7384.2347868442};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),329117.5979302810,TOLERANCE));

        DC.vData = {2.854858, 4.585868, 8.595959, 6.503453, 4.3453, 3.3245234, 32.234234, 662.77889, 7234.765, 8.234, 9.234, 7.234234, 54.234234};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),618.3788118,TOLERANCE));

        DC.vData = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
        REQUIRE (DC.vData.nearlyEqual(DC.calcAverage(),0,TOLERANCE));

    }


}
