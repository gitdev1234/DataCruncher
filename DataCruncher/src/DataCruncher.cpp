/**
 * DataCruncher.cpp
 * Purpose: implements class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 2.0 20161125
 */

#include "DataCruncher.h"

/* --- constructors / destructors --- */

/**
 * DataCruncher::DataCruncher
 * @brief standard constructor of class DataCruncher
 * @param size_             size of vector
 * @param useCutOffToRange_ true if data is cut to minimum and maximum value during a modification
 * @param minValue_         minimum value, needed for cutting data during modifation
 * @param maxValue_         maximum value, needed for cutting data during modifation
 *
 * creates vector of size 'size_' and initializes attributes
 *
 */
DataCruncher::DataCruncher(int    size_     , bool   useCutOffToRange_ ,
                           double minValue_ , double maxValue_           )
    : vector<double>   ( size_             ),
      useCutOffToRange ( useCutOffToRange_ ),
      minValue         ( minValue_         ),
      maxValue         ( maxValue_         )
{ }

/**
 * DataCruncher::DataCruncher
 * @brief copy constructor of class DataCruncher
 * @param other_ DataCruncher object to copy from
 * @param copyVectorData_ if true constructor only copies attributes, if false constructor also copies content of vector
 */
DataCruncher::DataCruncher(const DataCruncher &other_, bool copyVectorData_)
    : vector<double>   ( other_.getSize()             ),
      useCutOffToRange ( other_.getUseCutOffToRange() ),
      minValue         ( other_.getMinValue()         ),
      maxValue         ( other_.getMaxValue()         )
{
    if (copyVectorData_) {
        int size_l = other_.getSize();
        for (int i = 0; i < size_l; i++) {
            (*this)[i] = other_[i];
        }
    }
}

/* --- getters and setters --- */

/**
 * DataCruncher::setUseCutOffToRange
 * @brief setter of useCutOffToRange
 * @param val_ true if data shall be cut to range of minValue and maxValue during modification, otherwise false
 */
void DataCruncher::setUseCutOffToRange(bool val_) {
    useCutOffToRange = val_;
}

/**
 * DataCruncher::setMinMaxValue
 * @brief setter of minValue and maxValue
 * @param min_ new value for minValue
 * @param max_ new value for maxValue
 * @return returns true if it is allowed to set the range min_ -> max_
 *
 * NOTE : min has to be smaller than max
 */
bool DataCruncher::setMinMaxValue(double min_, double max_) {
    if (min_ < max_) {
        minValue = min_;
        maxValue = max_;
        return true;
    } else {
        return false;
    }
}

/**
 * DataCruncher::getSize
 * @brief returns the number of fields within the vector
 * @return returns the number of fields within the vector
 * NOTE : this is needed, because vector::size() returns only unsigned int
 */
int DataCruncher::getSize() const {
    return int( vector<double>::size() );
}

/**
 * DataCruncher::getValueAt
 * @brief returns value at the index 'index_' within the vector-data
 * @param index_ index of the data which is requested
 * @return returns data at index 'index_'
 *
 * NOTE : returns the data of index 0 if index is smaller than 0
 * NOTE : returns the data of index getSize() - 1 if index is bigger than getSize() - 1
 * NOTE : returns 0 if vector has no elements
 */
double DataCruncher::getValueAt(int index_) const {
    int size_l = getSize();
    if( size_l  < 1 ) {
        return 0;
    }

    if( index_ < 0 ) {
        return (*this)[ 0 ];
    }
    if( index_ > size_l-1 ) {
        return (*this)[ size_l - 1 ];
    }
    return (*this)[ index_ ];

}

/* --- miscellaneous --- */


/**
 * DataCruncher::cutOffToRange
 * @brief cuts the value 'val_' into the range of minValue and maxValue
 * @param val_ value which is to cut
 * @return returns value which is cut into the range of minValue and maxValue
 */
double DataCruncher::cutOffToRange(double val_) {
    double min = getMinValue();
    double max = getMaxValue();
    if (val_ < min) {
        val_ = min;
    } else if (val_ > max) {
        val_ = max;
    }
    return val_;
}

