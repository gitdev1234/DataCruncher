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

    SECTION("constructor" ) {


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
        }

        SECTION ("copy-constructor copies all attributes but not the data") {

            REQUIRE(true);

        }
    }

}
