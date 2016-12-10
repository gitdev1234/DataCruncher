/**
 * VectorDataTest.cpp
 * Purpose: implement unit-tests for the VectorData-class
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!

#include "catch.hpp"
#include "VectorData.h"
#include <iostream>
#include <sstream>
#include <climits>

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

TEST_CASE( "Test nearly equal" ) {
    VectorData vData;
    const double TOLERANCE = 0.05;
    REQUIRE(vData.nearlyEqual(0, 0.05,TOLERANCE));
    REQUIRE(vData.nearlyEqual(0,-0.05,TOLERANCE));
    REQUIRE(vData.nearlyEqual(0, 0.04,TOLERANCE));
    REQUIRE(vData.nearlyEqual(0,-0.04,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(0, 0.06,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(0,-0.06,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.02,-0.07,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.02, 0.03,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.02,-0.06,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.02, 0.02,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(-0.02,-0.08,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(-0.02, 0.04,TOLERANCE));

    REQUIRE(vData.nearlyEqual( 0.05,0,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.05,0,TOLERANCE));
    REQUIRE(vData.nearlyEqual( 0.04,0,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.04,0,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual( 0.06,0,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(-0.06,0,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.07,-0.02,TOLERANCE));
    REQUIRE(vData.nearlyEqual( 0.03,-0.02,TOLERANCE));
    REQUIRE(vData.nearlyEqual(-0.06,-0.02,TOLERANCE));
    REQUIRE(vData.nearlyEqual( 0.02,-0.02,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual(-0.08,-0.02,TOLERANCE));
    REQUIRE_FALSE(vData.nearlyEqual( 0.04,-0.02,TOLERANCE));
}

TEST_CASE("operators") {
    VectorData vData, vData2;
    for (int i = 0; i< 10; i++) {
        vData.push_back(i);
    }
    vData.setMinMaxValue(2,7);
    vData.setUseCutOffToRange(true);

    SECTION("assignment copies all attributes and data") {
        VectorData vData2 = vData;
        REQUIRE(&vData2 != &vData);
        REQUIRE(vData.getMaxValue() == vData2.getMaxValue());
        REQUIRE(vData.getMinValue() == vData2.getMinValue());
        REQUIRE(vData.getUseCutOffToRange() == vData2.getUseCutOffToRange());
        REQUIRE(vData.getSize() == vData2.getSize());
        for (int i = 0; i < vData.getSize(); i++) {
            REQUIRE(vData[i] == vData2[i]);
            REQUIRE(vData.getValueAt(i) == vData2.getValueAt(i));
        }

    }

    SECTION("checking equality and inequality of two vectorData-objects") {

        vData2 = vData;
        REQUIRE(&vData != &vData2);
        REQUIRE(vData.getMaxValue() == vData2.getMaxValue());
        REQUIRE(vData.getMinValue() == vData2.getMinValue());
        REQUIRE(vData.getUseCutOffToRange() == vData2.getUseCutOffToRange());
        REQUIRE(vData.getSize() == vData2.getSize());
        for (int i = 0; i < vData.getSize(); i++) {
            REQUIRE(vData[i] == vData2[i]);
            REQUIRE(vData.getValueAt(i) == vData2.getValueAt(i));
        }

        SECTION("identical") {
            REQUIRE((vData == vData2));
            REQUIRE_FALSE((vData != vData2));
        }

        SECTION("not identical because of attributes") {
            vData.setMinMaxValue(40,900);
            REQUIRE_FALSE((vData == vData2));
            REQUIRE((vData != vData2));
        }

         SECTION("not identical because of data") {
            vData[3] = 400;
            REQUIRE_FALSE((vData == vData2));
            REQUIRE((vData != vData2));
        }
    }

    SECTION("shift out and arithmetic operators") {

        stringstream sstr;

        SECTION ("<< operator works") {
            sstr << vData;
            REQUIRE( sstr.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
        }

        SECTION ("+ and - works with scalar values") {
            SECTION ("+  and - without cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData + 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[5,6,7,8,9,10,11,12,13,14]\n");
                vData = vData - 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION (" + with cutOff") {
                vData.setUseCutOffToRange(true);
                vData = vData + 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[5,6,7,7,7,7,7,7,7,7]\n");
            }

            SECTION (" - with cutOff") {
                vData.setUseCutOffToRange(true);
                vData = vData - 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,2,2,2,2,2,2,2,3,4]\n");
            }
        }

        SECTION ("* and / works with scalar values") {
            SECTION ("*  and / without cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData * 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                vData = vData / 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION (" * with cutOff") {
                vData.setUseCutOffToRange(true);
                vData = vData * 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,5,7,7,7,7,7,7,7,7]\n");
            }

            SECTION (" / with cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData * 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                vData.setUseCutOffToRange(true);
                vData = vData / 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,4,5,6,7,7,7]\n");
            }
        }

        SECTION("+ and - works with other VectorData-objects") {
            vData2 = vData;
            SECTION ("+ and - works for VectorData-objects without cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData + vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,2,4,6,8,10,12,14,16,18]\n");
                vData = vData - vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION ("+ and - works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(true);
                vData = vData + vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,2,4,6,7,7,7,7,7,7]\n");
                vData = vData - vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,3,2,2,2,2,2]\n");
            }
        }

        SECTION("* and / works with other VectorData-objects") {
            vData2 = vData;
            SECTION ("* and / works for VectorData-objects without cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData * vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                vData = vData / vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION ("* works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(true);
                vData = vData * vData2;
                sstr << vData;
                REQUIRE( sstr.str() ==  "[2,2,4,7,7,7,7,7,7,7]\n");
            }

            SECTION ("/ works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(false);
                vData = vData * vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                vData.setUseCutOffToRange(true);
                vData = vData / vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,4,5,6,7,7,7]\n");
            }
        }

        SECTION ("+= and -= works with scalar values") {
            SECTION ("+=  and -= without cutOff") {
                vData.setUseCutOffToRange(false);
                vData += 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[5,6,7,8,9,10,11,12,13,14]\n");
                vData -= 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION (" += with cutOff") {
                vData.setUseCutOffToRange(true);
                vData += 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[5,6,7,7,7,7,7,7,7,7]\n");
            }

            SECTION (" -= with cutOff") {
                vData.setUseCutOffToRange(true);
                vData -= 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,2,2,2,2,2,2,2,3,4]\n");
            }
        }

        SECTION ("*= and /= works with scalar values") {
            SECTION ("*=  and /= without cutOff") {
                vData.setUseCutOffToRange(false);
                vData *= 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                vData /= 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION (" *= with cutOff") {
                vData.setUseCutOffToRange(true);
                vData *= 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,5,7,7,7,7,7,7,7,7]\n");
            }

            SECTION (" /= with cutOff") {
                vData.setUseCutOffToRange(false);
                vData *= 5;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                vData.setUseCutOffToRange(true);
                vData /= 5;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,4,5,6,7,7,7]\n");
            }
        }

        SECTION("+= and -= works with other VectorData-objects") {
            vData2 = vData;
            SECTION ("+= and -= works for VectorData-objects without cutOff") {
                vData.setUseCutOffToRange(false);
                vData += vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,2,4,6,8,10,12,14,16,18]\n");
                vData -= vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION ("+= and -= works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(true);
                vData += vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[2,2,4,6,7,7,7,7,7,7]\n");
                vData -= vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,3,2,2,2,2,2]\n");
            }
        }

        SECTION("*= and /= works with other VectorData-objects") {
            vData2 = vData;
            SECTION ("*= and /= works for VectorData-objects without cutOff") {
                vData.setUseCutOffToRange(false);
                vData *= vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                vData /= vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION ("*= works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(true);
                vData *= vData2;
                sstr << vData;
                REQUIRE( sstr.str() ==  "[2,2,4,7,7,7,7,7,7,7]\n");
            }

            SECTION ("/= works for VectorData-objects with cutOff") {
                vData.setUseCutOffToRange(false);
                vData *= vData2;
                sstr << vData;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                vData.setUseCutOffToRange(true);
                vData /= vData2;
                stringstream sstr2;
                sstr2 << vData;
                REQUIRE( sstr2.str() == "[2,2,2,3,4,5,6,7,7,7]\n");
            }
        }

    }
}
