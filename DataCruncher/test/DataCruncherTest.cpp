/**
 * VectorDataTest.cpp
 * Purpose: implement unit-tests for the DataCruncher-class
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!

#include "catch.hpp"
#include "DataCruncher.h"

TEST_CASE("constructor / destructor") {
    SECTION("constructor") {
        REQUIRE(1==1);
    }
}
