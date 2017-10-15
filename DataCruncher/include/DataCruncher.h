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
        void  calcAllStatisticValues();

        // analytic values
        double calcFourierTransform() const;
        double calcTaylorSeries() const;

        /* --- modify --- */
        VectorData removeErrors(bool changeLocalVectorData_ = true);
        VectorData zTransform(bool changeLocalVectorData_ = true);
        VectorData undoZTransform(double averageBeforeZ_, double stdDeviationBeforeZ_, bool changeLocalVectorData_ = true);
        VectorData differentiate(bool changeLocalVectorData_ = true);
        VectorData integrate(bool changeLocalVectorData_ = true);
        VectorData movingAverageFiltering(bool changeLocalVectorData_ = true);

        /* --- public members --- */
        VectorData vData;

        /* --- getters / setters --- */
        bool getStatisticValuesAreUpToDate() const;
        void setStatisticValuesAreUpToDate(bool statisticValuesAreUpToDate_);

        double getAverage() const;
        void setAverage(double average_);

        double getMedian() const;
        void setMedian(double median_);

        double getStdDeviation() const;
        void setStdDeviation(double stdDeviation_);

        double getVariance() const;
        void setVariance(double variance_);

private:
        /* --- load / save --- */
        int loadFromCSVFile(const string& path_, char separator_ = ',');
        int saveToCSVFile(const string& path_, char separator_ = ',', int decimalPlaces_ = 2) const;
        int loadFromBinaryFile(const string& path_);
        int saveToBinaryFile(const string& path_) const;
        string getSuffixFromString(const string& val_) const;

        // miscellaneous
        bool statisticValuesAreUpToDate = false;

        // statistic values of vData
        double average;
        double median;
        double stdDeviation;
        double variance;
        //double calcHistogramm() const;        todo

};

#endif // DATACRUNCHER_H
