#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <iostream>
#include <climits>
//---
#include "catch.hpp"
//---
#include "include/SignalProcessor.h"


// !!!! TEST_CASE IN COMBINITION WITH REQUIRE IS LIKE A LOOP STRUCTURE !!!!
// !!!! THE TEST_CASE IS EXECUTED FOR EVERY SECTION !!!!


TEST_CASE("comparing and copying a signalProcessor","signalprocessor") {
    SignalProcessor s;
    for (int i = 0; i< 10; i++) {
        s.push_back(i);
    }

    SECTION("copy - constructor" ) {
        SECTION ("copy-constructor copies all attributes but not the data") {
            SignalProcessor s2(s,false);
            REQUIRE(&s != &s2);
            REQUIRE(s.getMaxValue() == s2.getMaxValue());
            REQUIRE(s.getMinValue() == s2.getMinValue());
            REQUIRE(s.getUseCutOffToRange() == s2.getUseCutOffToRange());
        }
        SECTION ("copy-constructor copies all attributes and data") {
            SignalProcessor s2(s,true);
            REQUIRE(&s != &s2);
            REQUIRE(s.getMaxValue() == s2.getMaxValue());
            REQUIRE(s.getMinValue() == s2.getMinValue());
            REQUIRE(s.getUseCutOffToRange() == s2.getUseCutOffToRange());
            REQUIRE(s.getSize() == s2.getSize());
            for (int i = 0; i < s.getSize(); i++) {
                REQUIRE(s[i] == s2[i]);
                REQUIRE(s.getValueAt(i) == s2.getValueAt(i));
            }
        }
    }
    SECTION("assignment copies all attributes and data") {
        SignalProcessor s2 = s;
        REQUIRE(&s != &s2);
        REQUIRE(s.getMaxValue() == s2.getMaxValue());
        REQUIRE(s.getMinValue() == s2.getMinValue());
        REQUIRE(s.getUseCutOffToRange() == s2.getUseCutOffToRange());
        REQUIRE(s.getSize() == s2.getSize());
        for (int i = 0; i < s.getSize(); i++) {
            REQUIRE(s[i] == s2[i]);
            REQUIRE(s.getValueAt(i) == s2.getValueAt(i));
        }

    }
}


TEST_CASE("checking equality of two signalProcessors") {
    SignalProcessor s, s2;
    for (int i = 0; i< 10; i++) {
        s.push_back(i);
    }
    s.setMinMaxValue(2,7);
    s.setUseCutOffToRange(true);
    s2 = s;
    REQUIRE(&s != &s2);
    REQUIRE(s.getMaxValue() == s2.getMaxValue());
    REQUIRE(s.getMinValue() == s2.getMinValue());
    REQUIRE(s.getUseCutOffToRange() == s2.getUseCutOffToRange());
    REQUIRE(s.getSize() == s2.getSize());
    for (int i = 0; i < s.getSize(); i++) {
        REQUIRE(s[i] == s2[i]);
        REQUIRE(s.getValueAt(i) == s2.getValueAt(i));
    }

    SECTION("identical") {
        REQUIRE(s == s2);
        REQUIRE_FALSE(s != s2);
    }

    SECTION("not identical because of attributes") {
        s.setMinMaxValue(40,900);
        REQUIRE_FALSE(s == s2);
        REQUIRE(s != s2);
    }

     SECTION("not identical because of data") {
        s[3] = 400;
        REQUIRE_FALSE(s == s2);
        REQUIRE(s != s2);
    }
}

TEST_CASE( "outputting, analyzing, histogram and modifying a signalprocessor", "[signalprocessor]" ) {

    SignalProcessor s, s2;
    for (int i = 0; i< 10; i++) {
        s.push_back(i);
        s2.push_back(i);
    }


    stringstream sstr, sstr2;

    SECTION( "for channelsCount == 0" ) {
        SECTION ("<< operator works") {
            sstr << s;
            REQUIRE( sstr.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
        }

        vector<int> temp = {5};
        SECTION ("modify works") {
            SECTION ("ADD and SUBTRACT works") {
                s = s.modifySignalProcessor(ModificationType::ADD ,temp);
                sstr << s;
                REQUIRE( sstr.str() == "[5,6,7,8,9,10,11,12,13,14]\n");
                s = s.modifySignalProcessor(ModificationType::SUBTRACT ,temp);
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("MULTIPLY and DIVIDE works") {
                s = s.modifySignalProcessor(ModificationType::MULTIPLY ,temp);
                sstr << s;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                s = s.modifySignalProcessor(ModificationType::DIVIDE ,temp);
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("ADD and SUBTRACT works for signals") {
                s = s.modifySignalProcessor(ModificationType::ADD_SIGNALPROCESSOR ,s2);
                sstr << s;
                REQUIRE( sstr.str() == "[0,2,4,6,8,10,12,14,16,18]\n");
                s = s.modifySignalProcessor(ModificationType::SUBTRACT_SIGNALPROCESSOR ,s2);
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("MULTIPLY and DIVIDE works for signals") {
                s = s.modifySignalProcessor(ModificationType::MULTIPLY_SIGNALPROCESSOR ,s2);
                sstr << s;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                s = s.modifySignalProcessor(ModificationType::DIVIDE_SIGNALPROCESSOR ,s2);
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("threshold works" ) {
                s = s.modifySignalProcessor(ModificationType::THRESHOLD,temp);
                sstr << s;
                REQUIRE( sstr.str() == "[0,0,0,0,0,5,6,7,8,9]\n");
            }
            SECTION ("binary threshold works" ) {
                s = s.modifySignalProcessor(ModificationType::BINARY_THRESHOLD,temp);
                sstr << s;
                REQUIRE( sstr.str() == "[0,0,0,0,0,1,1,1,1,1]\n");
            }

            SECTION ("MOVING_AVERAGE works") {
                temp[0] = 3; // neighbourhoodCount
                s = s.modifySignalProcessor(ModificationType::MOVING_AVERAGE,temp);
                sstr << s;
                REQUIRE( sstr.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
                s[6] = 15;
                s = s.modifySignalProcessor(ModificationType::MOVING_AVERAGE,temp);
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,8,9,10,8,9]\n");
            }
            SECTION ("GRADIENT works") {
                SECTION ("GRADIENT works with positiv slopes") {
                    s = s.modifySignalProcessor(ModificationType::GRADIENT_NORMAL);
                    sstr << s;
                    REQUIRE( sstr.str() == "[1,1,1,1,1,1,1,1,1,1]\n");
                }
                SECTION ("GRADIENT works negativ slopes") {
                    s[6] = 15;
                    SECTION("GRADIENT_NORMAL works with negativ slopes and without cutoff") {
                        s = s.modifySignalProcessor(ModificationType::GRADIENT_NORMAL);
                        sstr << s;
                        REQUIRE( sstr.str() == "[1,1,1,1,1,6,1,-4,1,1]\n");
                    }
                    SECTION("GRADIENT_NORMAL works with negativ slopes and with cutoff") {
                        s.setMinMaxValue(0,5);
                        s.setUseCutOffToRange(true);
                        s = s.modifySignalProcessor(ModificationType::GRADIENT_NORMAL);
                        sstr << s;
                        REQUIRE( sstr.str() == "[1,1,1,1,1,5,1,0,1,1]\n");
                    }
                    SECTION("GRADIENT_ABS works with negativ slopes and without cutoff") {
                        s = s.modifySignalProcessor(ModificationType::GRADIENT_ABS);
                        sstr << s;
                        REQUIRE( sstr.str() == "[1,1,1,1,1,6,1,4,1,1]\n");
                    }
                    SECTION("GRADIENT_ABS works with negativ slopes and with cutoff") {
                        s.setMinMaxValue(0,5);
                        s.setUseCutOffToRange(true);
                        s = s.modifySignalProcessor(ModificationType::GRADIENT_ABS);
                        sstr << s;
                        REQUIRE( sstr.str() == "[1,1,1,1,1,5,1,4,1,1]\n");
                    }
                }
            }




        }

        SECTION("arithmetic operators work") {
            SECTION ("+ and - works") {
                s = s + 5;
                sstr << s;
                REQUIRE( sstr.str() == "[5,6,7,8,9,10,11,12,13,14]\n");
                s = s - 5;
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("* and / works") {
                s = s * 5;
                sstr << s;
                REQUIRE( sstr.str() == "[0,5,10,15,20,25,30,35,40,45]\n");
                s = s / 5;
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("+ and - works for signals") {
                s = s + s2;
                sstr << s;
                REQUIRE( sstr.str() == "[0,2,4,6,8,10,12,14,16,18]\n");
                s = s - s2;
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
            SECTION ("* and / works for signals") {
                s = s*s2;
                sstr << s;
                REQUIRE( sstr.str() == "[0,1,4,9,16,25,36,49,64,81]\n");
                s = s/s2;
                stringstream sstr2;
                sstr2 << s;
                REQUIRE( sstr2.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }
        }

        SECTION("Min and Max cuttoff works") {
            SECTION("You cannot set min max, if max<=min") {
                s.setUseCutOffToRange(true);
                s.setMinMaxValue(2,2);
                sstr << s;
                REQUIRE( sstr.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
                s.setMinMaxValue(5,2);
                sstr2 << s;
                REQUIRE( sstr.str() == "[0,1,2,3,4,5,6,7,8,9]\n");
            }

            SECTION("cutOffToRange is not used if min and max are set, but useCutOffToRange == false") {
                s.setMinMaxValue(2,4);
                s = s + 2;
                sstr << s;
                REQUIRE( sstr.str() == "[2,3,4,5,6,7,8,9,10,11]\n");
            }
            SECTION("cutOffToRange is used if min and max are set, and useCutOffToRange == true") {
                s.setMinMaxValue(2,4);
                s.setUseCutOffToRange(true);
                s = s + 2;
                sstr << s;
                REQUIRE( sstr.str() == "[2,3,4,4,4,4,4,4,4,4]\n");
            }


        }

        SECTION("analyzation works") {
            double tempResult;
            SECTION("min & max works") {
                tempResult = s.analyzeSignalProcessor(AnalyzationType::MINIMUM);
                REQUIRE(tempResult == 0);
                tempResult = s.analyzeSignalProcessor(AnalyzationType::MAXIMUM);
                REQUIRE(tempResult == 9);
            }
            SECTION("average works") {
                tempResult = s.analyzeSignalProcessor(AnalyzationType::AVERAGE);
                REQUIRE(tempResult == 4.5);
            }
            SECTION("standard deviation works") {
                tempResult = s.analyzeSignalProcessor(AnalyzationType::STD_DEVIATION);
                REQUIRE(tempResult == Approx(2.8722813233));
                s[6] = 15;
                tempResult = s.analyzeSignalProcessor(AnalyzationType::STD_DEVIATION);
                REQUIRE(tempResult == Approx(4.2708313008));
            }


        }
        SECTION ("histogram") {
            map<int, int> tempHistogram = s.calcHistogram();
            REQUIRE(tempHistogram[0] == 1);
            REQUIRE(tempHistogram[1] == 1);
            REQUIRE(tempHistogram[2] == 1);
            REQUIRE(tempHistogram[3] == 1);
            REQUIRE(tempHistogram[4] == 1);
            REQUIRE(tempHistogram[5] == 1);
            REQUIRE(tempHistogram[6] == 1);
            REQUIRE(tempHistogram[7] == 1);
            REQUIRE(tempHistogram[8] == 1);
            REQUIRE(tempHistogram[9] == 1);
            SECTION ("add one of the excisting values") {
                s[2] = 5;
                tempHistogram = s.calcHistogram();
                REQUIRE(tempHistogram[0] == 1);
                REQUIRE(tempHistogram[1] == 1);
                REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                REQUIRE(tempHistogram[3] == 1);
                REQUIRE(tempHistogram[4] == 1);
                REQUIRE(tempHistogram[5] == 2);
                REQUIRE(tempHistogram[6] == 1);
                REQUIRE(tempHistogram[7] == 1);
                REQUIRE(tempHistogram[8] == 1);
                REQUIRE(tempHistogram[9] == 1);
                SECTION ("add another of the excisting values") {
                    s[5] = 4;
                    tempHistogram = s.calcHistogram();
                    REQUIRE(tempHistogram[0] == 1);
                    REQUIRE(tempHistogram[1] == 1);
                    REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[3] == 1);
                    REQUIRE(tempHistogram[4] == 2);
                    REQUIRE(tempHistogram[5] == 1);
                    REQUIRE(tempHistogram[6] == 1);
                    REQUIRE(tempHistogram[7] == 1);
                    REQUIRE(tempHistogram[8] == 1);
                    REQUIRE(tempHistogram[9] == 1);
                }
                SECTION ("add another value") {
                    s[6] = 200;
                    tempHistogram = s.calcHistogram();
                    REQUIRE(tempHistogram[0] == 1);
                    REQUIRE(tempHistogram[1] == 1);
                    REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[3] == 1);
                    REQUIRE(tempHistogram[4] == 1);
                    REQUIRE(tempHistogram[5] == 2);
                    REQUIRE((tempHistogram.find(6) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[7] == 1);
                    REQUIRE(tempHistogram[8] == 1);
                    REQUIRE(tempHistogram[9] == 1);
                    REQUIRE(tempHistogram[200] == 1);
                }
                SECTION ("a negative value") {
                    s[6] = -400;
                    tempHistogram = s.calcHistogram();
                    REQUIRE(tempHistogram[0] == 1);
                    REQUIRE(tempHistogram[1] == 1);
                    REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[3] == 1);
                    REQUIRE(tempHistogram[4] == 1);
                    REQUIRE(tempHistogram[5] == 2);
                    REQUIRE((tempHistogram.find(6) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[7] == 1);
                    REQUIRE(tempHistogram[8] == 1);
                    REQUIRE(tempHistogram[9] == 1);
                    REQUIRE(tempHistogram[-400] == 1);
                }
                SECTION ("min and max values") {
                    s[6] = INT_MAX;
                    s[7] = INT_MIN;
                    tempHistogram = s.calcHistogram();
                    REQUIRE(tempHistogram[0] == 1);
                    REQUIRE(tempHistogram[1] == 1);
                    REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[3] == 1);
                    REQUIRE(tempHistogram[4] == 1);
                    REQUIRE(tempHistogram[5] == 2);
                    REQUIRE((tempHistogram.find(6) == tempHistogram.end()) == true);
                    REQUIRE((tempHistogram.find(7) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[8] == 1);
                    REQUIRE(tempHistogram[9] == 1);
                    REQUIRE(tempHistogram[INT_MIN] == 1);
                    REQUIRE(tempHistogram[INT_MAX] == 1);
                }
                SECTION ("text-file") {
                    s[6] = INT_MAX;
                    s[7] = INT_MIN;
                    tempHistogram = s.calcHistogram("temp.csv",",");

                    REQUIRE(tempHistogram[0] == 1);
                    REQUIRE(tempHistogram[1] == 1);
                    REQUIRE((tempHistogram.find(2) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[3] == 1);
                    REQUIRE(tempHistogram[4] == 1);
                    REQUIRE(tempHistogram[5] == 2);
                    REQUIRE((tempHistogram.find(6) == tempHistogram.end()) == true);
                    REQUIRE((tempHistogram.find(7) == tempHistogram.end()) == true);
                    REQUIRE(tempHistogram[8] == 1);
                    REQUIRE(tempHistogram[9] == 1);
                    REQUIRE(tempHistogram[INT_MIN] == 1);
                    REQUIRE(tempHistogram[INT_MAX] == 1);

                    ifstream ifs("temp.csv");
                    string line;
                    getline(ifs, line);
                    REQUIRE(line=="-2147483648,1");
                    getline(ifs, line);
                    REQUIRE(line=="0,1");
                    getline(ifs, line);
                    REQUIRE(line=="1,1");
                    getline(ifs, line);
                    REQUIRE(line=="3,1");
                    getline(ifs, line);
                    REQUIRE(line=="4,1");
                    getline(ifs, line);
                    REQUIRE(line=="5,2");
                    getline(ifs, line);
                    REQUIRE(line=="8,1");
                    getline(ifs, line);
                    REQUIRE(line=="9,1");
                    getline(ifs, line);
                    REQUIRE(line=="2147483647,1");
                    getline(ifs, line);
                    REQUIRE(line=="");
                }
            }
        }
    }

}
