/**
 * DataCruncherTest.cpp
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

TEST_CASE("DataCruncher operators") {
    DataCruncher DC;
    SECTION("[] operator") {
        for (int i = 0; i < 10; i++) {
            DC.vData.push_back(i);
        }
        SECTION("setting values") {
            for (int i = 0; i < 10; i++) {
                DC[i] = i*2;
                REQUIRE(DC.vData[i] == i*2);
            }
        }
        SECTION("getting values") {
            for (int i = 0; i < 10; i++) {
                REQUIRE(DC[i] == DC.vData[i]);
            }
        }
    }

}

TEST_CASE("file operations") {
    DataCruncher DC;
    const double TOLERANCE = 0.000001;

    DC.vData.resize(3);
    DC[0] = 10.000;
    DC[1] = -32;
    DC[2] = 435324.234123464576;

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
            REQUIRE(DC.saveToFile(path,',',10));
        }
    }

    SECTION("load a *.csv-path as a CSV-file") {
        string path;
        DataCruncher DC2;
        for (int i = 0; i < 3; i++) {
            switch (i)  {
                case 0 : path = "test.CSV"; break;
                case 1 : path = "test.csv"; break;
                case 2 : path = "test.cSv"; break;
            }
            REQUIRE(DC2.loadFromFile(path));
            REQUIRE(DC.vData.getSize() == DC2.vData.getSize());
            for (int i2 = 0; i2 < DC.vData.getSize(); i2++) {
                REQUIRE( DC.vData.nearlyEqual(DC.vData[i2],DC2.vData[i2],TOLERANCE));
            }
        }
    }

    SECTION("save any other suffixes to a binary files") {
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

    SECTION("load any other suffixes as a binary file") {
        string path;
        DataCruncher DC2;
        for (int i = 0; i < 3; i++) {
            switch (i)  {
                case 0 : path = "test.bin"; break;
                case 1 : path = "test.TeSt"; break;
                case 2 : path = "test.12c!"; break;
            }
            REQUIRE(DC2.loadFromFile(path));
        }
    }
}
