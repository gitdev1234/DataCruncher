#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <climits>
//---
#include "catch.hpp"
//---
#include "VectorData.h"


// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!


TEST_CASE("constructors, getters, setters") {

    SECTION("constructor" ) {

        SECTION ("standard constructor without parameters") {
            VectorData vData;
            REQUIRE(vData.getSize()==0);
            REQUIRE_FALSE(vData.getUseCutOffToRange());
            REQUIRE(vData.getMinValue()==DBL_MIN);
            REQUIRE(vData.getMaxValue()==DBL_MAX);
        }

        SECTION ("standard constructor with parameters") {
            VectorData vData(10,true,-20,20);
            REQUIRE(vData.getSize()==10);
            REQUIRE(vData.getUseCutOffToRange());
            REQUIRE(vData.getMinValue()==-20);
            REQUIRE(vData.getMaxValue()==20);

            vData[0] = 23049820348;
            vData[1] = 20.4;
            vData[2] = -234.23425;

            SECTION ("copy-constructor copies all attributes but not the data") {
                VectorData vData2(vData,false);
                REQUIRE(vData2.getSize()==vData.getSize());
                REQUIRE(vData2.getUseCutOffToRange()==vData.getUseCutOffToRange());
                REQUIRE(vData2.getMinValue()==vData.getMinValue());
                REQUIRE(vData2.getMaxValue()==vData.getMaxValue());
                REQUIRE(vData2[0] != vData[0]);
                REQUIRE(vData2[1] != vData[1]);
                REQUIRE(vData2[2] != vData[2]);
            }

            SECTION ("copy-constructor copies all attributes and the data") {
                VectorData vData2(vData,true);
                REQUIRE(vData2.getSize()==vData.getSize());
                REQUIRE(vData2.getUseCutOffToRange()==vData.getUseCutOffToRange());
                REQUIRE(vData2.getMinValue()==vData.getMinValue());
                REQUIRE(vData2.getMaxValue()==vData.getMaxValue());
                for (int i = 0; i < vData2.getSize(); i++ ) {
                    REQUIRE(vData2[i] == vData[i]);
                }
            }
        }

    }

    SECTION("getters / setters") {
            SECTION("getValueAt handles index errors") {
                VectorData vData(3);
                vData[0] = 1;
                vData[1] = 2;
                vData[2] = 3;
                REQUIRE(vData.getValueAt(-1)==1);
                REQUIRE(vData.getValueAt(-12345)==1);
                REQUIRE(vData.getValueAt(0)==1);
                REQUIRE(vData.getValueAt(1)==2);
                REQUIRE(vData.getValueAt(2)==3);
                REQUIRE(vData.getValueAt(3)==3);
                REQUIRE(vData.getValueAt(12345)==3);
            }
    }
}

TEST_CASE("min max cut-off") {
    SECTION("cut-off by direct call") {
        VectorData vData(10,true,-25.2,232323.2323);

        REQUIRE(vData.cutOffToRange(-25.1)==-25.1);
        REQUIRE(vData.cutOffToRange(-25.2)==-25.2);
        REQUIRE(vData.cutOffToRange(-25.3)==-25.2);
        REQUIRE(vData.cutOffToRange(-10000000)==-25.2);
        REQUIRE(vData.cutOffToRange(0)==0);
        REQUIRE(vData.cutOffToRange(10)==10);
        REQUIRE(vData.cutOffToRange(28.234234234)==28.234234234);
        REQUIRE(vData.cutOffToRange(232323.2322)==232323.2322);
        REQUIRE(vData.cutOffToRange(232323.2323)==232323.2323);
        REQUIRE(vData.cutOffToRange(232323.2324)==232323.2323);
        REQUIRE(vData.cutOffToRange(10000000)==232323.2323);
    }
}
