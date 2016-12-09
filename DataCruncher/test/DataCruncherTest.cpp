/**
 * VectorDataTest.cpp
 * Purpose: implements unit-tests for the DataCruncher-class
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
        DataCruncher DC;
    }
}

TEST_CASE("file operations") {
    DataCruncher DC;

    // TODO fill DC with values;

    SECTION("do not save path without suffix") {
        REQUIRE_FALSE(DC.saveToFile("test"));
    }

    SECTION("save a *.csv-path to a CSV-file") {
        string path;
        for (int i = 0; i < 3; i++) {
            switch (i)  {
                case 0 : path = "test.CSV"; break;
                case 1 : path = "test.csv"; break;
                case 2 : path = "test.cSv"; break;
            }
            REQUIRE(DC.saveToFile(path));
        }
    }

    SECTION("save any other paths with suffixes to a binary file") {
        string path;
        for (int i = 0; i < 3; i++) {
            switch (i)  {
                case 0 : path = "test.bin"; break;
                case 1 : path = "test.TeSt"; break;
                case 2 : path = "test.12c!"; break;
            }
            REQUIRE(DC.saveToFile(path));
        }
    }
}
