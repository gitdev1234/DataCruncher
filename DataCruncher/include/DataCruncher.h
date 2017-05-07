/**
 * DataCruncher.h
 * Purpose: defines class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

#ifndef DATACRUNCHER_H
#define DATACRUNCHER_H


#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <fstream>
#include <stdio.h>
//---
#include "VectorData.h"



class DataCruncher {
    public:
        /* --- constructors / destructors --- */
        DataCruncher() {};

        /* --- operators --- */
        double& operator[](int index_);

        /* --- load / save --- */
        int loadFromFile(const string& path_,char separator_ = ',');
        int saveToFile(const string& path_,char separator_ = ',', int decimalPlaces_ = 2) const;

        /* --- analyze --- */

        // statistic values
        double calcAverage() const;
        double calcMedian() const;
        double calcStdDeviation() const;
        double calcVariance() const;
        double calcHistogramm() const;

        // analytic values
        double calcFourierTransform() const;
        double calcTaylorSeries() const;

        /* --- modify --- */
        VectorData removeErrors();
        VectorData zTransform();
        VectorData differentiate();
        VectorData integrate();
        VectorData movingAverageFiltering();

        /* --- public members --- */
        VectorData vData;

    private:
        /* --- load / save --- */
        int loadFromCSVFile(const string& path_, char separator_ = ',');
        int saveToCSVFile(const string& path_, char separator_ = ',', int decimalPlaces_ = 2) const;
        int loadFromBinaryFile(const string& path_);
        int saveToBinaryFile(const string& path_) const;
        string getSuffixFromString(const string& val_) const;

};

#endif // DATACRUNCHER_H
