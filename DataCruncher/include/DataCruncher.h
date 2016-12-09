/**
 * DataCruncher.h
 * Purpose: defines class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.2
 */

#ifndef DATACRUNCHER_H
#define DATACRUNCHER_H

#include "VectorData.h"


class DataCruncher {
    public:
        /* --- constructors / destructors --- */
        DataCruncher() {};

        /* --- load / save --- */
        bool loadFromFile();
        bool saveToFile();
        bool loadFromDataBase();
        bool saveToDataBase();

        /* --- analyze --- */

        // statistic values
        double calcAverage();
        double calcMedian();
        double calcStdDeviation();
        double calcVariance();
        double calcHistogramm();

        // analytical values
        double calcFourierTransform();
        double calcTaylorSeries();

        /* --- modify --- */
        VectorData removeErrors();
        VectorData zTransform();
        VectorData differentiate();
        VectorData integrate();
        VectorData movingAverageFiltering();


    private:
        VectorData vData;

};

#endif // DATACRUNCHER_H
