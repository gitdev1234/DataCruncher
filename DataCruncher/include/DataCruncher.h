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
//---
#include "VectorData.h"



class DataCruncher {
    public:
        /* --- constructors / destructors --- */
        DataCruncher() {};

        /* --- operators --- */
        double& operator[](int index_);

        /* --- load / save --- */
        bool loadFromFile(const string& path_,char separator_ = ',');
        bool saveToFile(const string& path_,char separator_ = ',', int decimalPlaces_ = 2) const;
        bool loadFromDataBase();
        bool saveToDataBase() const;

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


        VectorData vData;

    private:
        /* --- load / save --- */
        bool loadFromCSVFile(const string& path_, char separator_ = ',');
        bool saveToCSVFile(const string& path_, char separator_ = ',', int decimalPlaces_ = 2) const;
        bool loadFromBinaryFile(const string& path_);
        bool saveToBinaryFile(const string& path_) const;
        string getSuffixFromString(const string& val_) const;

};

#endif // DATACRUNCHER_H
