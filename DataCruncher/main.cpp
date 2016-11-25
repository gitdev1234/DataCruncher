#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <climits>
//---
#include "catch.hpp"
//---
#include "DataCruncher.h"


// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!


TEST_CASE("constructors, getters, setters") {

    SECTION ("standard constructor without parameters") {
        DataCruncher dataC;
        REQUIRE(dataC.getSize()==0);
        REQUIRE_FALSE(dataC.getUseCutOffToRange());
        REQUIRE(dataC.getMinValue()==DBL_MIN);
        REQUIRE(dataC.getMaxValue()==DBL_MAX);
    }

    SECTION ("standard constructor with parameters") {
        DataCruncher dataC(10,true,-20,20);
        REQUIRE(dataC.getSize()==10);
        REQUIRE(dataC.getUseCutOffToRange());
        REQUIRE(dataC.getMinValue()==-20);
        REQUIRE(dataC.getMaxValue()==20);

        dataC[0] = 23049820348;
        dataC[1] = 20.4;
        dataC[2] = -234.23425;

        SECTION ("copy-constructor copies all attributes but not the data") {
            DataCruncher dataC2(dataC,false);
            REQUIRE(dataC2.getSize()==dataC.getSize());
            REQUIRE(dataC2.getUseCutOffToRange()==dataC.getUseCutOffToRange());
            REQUIRE(dataC2.getMinValue()==dataC.getMinValue());
            REQUIRE(dataC2.getMaxValue()==dataC.getMaxValue());
            REQUIRE(dataC2[0] != dataC[0]);
            REQUIRE(dataC2[1] != dataC[1]);
            REQUIRE(dataC2[2] != dataC[2]);
        }

        SECTION ("copy-constructor copies all attributes and the data") {
            DataCruncher dataC2(dataC,true);
            REQUIRE(dataC2.getSize()==dataC.getSize());
            REQUIRE(dataC2.getUseCutOffToRange()==dataC.getUseCutOffToRange());
            REQUIRE(dataC2.getMinValue()==dataC.getMinValue());
            REQUIRE(dataC2.getMaxValue()==dataC.getMaxValue());
            for (int i = 0; i < dataC2.getSize(); i++ ) {
                REQUIRE(dataC2[i] == dataC[i]);
            }
        }
    }
}
