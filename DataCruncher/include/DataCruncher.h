/**
 * DataCruncher.h
 * Purpose: defines class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.0 20160713
 */

#ifndef DataCruncher_H
#define DataCruncher_H

#include <iostream>
#include <vector>
#include <float.h>

using namespace std;

/**
 * class
 */
class DataCruncher : public vector<double> {
    public:
        /* --- constructors / destructors --- */

        // standard - constructor
        DataCruncher(int     size_     =       0, bool   useCutOffToRange_ =   false,
                     double  minValue_ = DBL_MIN, double maxValue_         = DBL_MAX);

        // copy - constructor
        DataCruncher(const DataCruncher& other_, bool copyVectorData_ = true);

        /* --- miscellaneous --- */
        int    getSize       ()           const;
        double getValueAt    (int index_) const;
        double cutOffToRange (double val_);

        /* --- getter / setter --- */
        bool    getUseCutOffToRange () const    {return useCutOffToRange;};
        double  getMinValue         () const    {return minValue;        };
        double  getMaxValue         () const    {return maxValue;        };
        void    setUseCutOffToRange (bool val_) ;
        bool    setMinMaxValue      (double  min_, double max_);

        /* --- operators --- */
        DataCruncher& operator= (const DataCruncher& other_);
        bool          operator==(const DataCruncher& other_) const;
        bool          operator!=(const DataCruncher& other_) const;
        DataCruncher  operator+ (double val_) const;
        DataCruncher  operator- (double val_) const;
        DataCruncher  operator* (double val_) const;
        DataCruncher  operator/ (double val_) const;
        DataCruncher  operator+ (const DataCruncher& val_) const;
        DataCruncher  operator- (const DataCruncher& val_) const;
        DataCruncher  operator* (const DataCruncher& val_) const;
        DataCruncher  operator/ (const DataCruncher& val_) const;
        friend ostream& operator<<(ostream& ostream_, const DataCruncher DataCruncher_);
        friend ostream& operator<<(ostream& ostream_, vector<double> val_);

    private:
        bool   useCutOffToRange = false;
        double minValue         = DBL_MIN;
        double maxValue         = DBL_MAX;
};

#endif // DataCruncher_H
