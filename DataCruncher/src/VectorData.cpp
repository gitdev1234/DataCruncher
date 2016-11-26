/**
 * VectorData.cpp
 * Purpose: implements class VectorData
 *
 * @author Wall.Of.Death
 * @version 2.0 20161125
 */

#include "VectorData.h"

/* --- constructors / destructors --- */

/**
 * VectorData::VectorData
 * @brief standard constructor of class VectorData
 * @param size_             size of vector
 * @param useCutOffToRange_ true if data is cut to minimum and maximum value during a modification
 * @param minValue_         minimum value, needed for cutting data during modifation
 * @param maxValue_         maximum value, needed for cutting data during modifation
 *
 * creates vector of size 'size_' and initializes attributes
 *
 */
VectorData::VectorData(int    size_     , bool   useCutOffToRange_ ,
                           double minValue_ , double maxValue_           )
    : vector<double>   ( size_             ),
      useCutOffToRange ( useCutOffToRange_ ),
      minValue         ( minValue_         ),
      maxValue         ( maxValue_         )
{ }

/**
 * VectorData::VectorData
 * @brief copy constructor of class VectorData
 * @param other_ VectorData object to copy from
 * @param copyVectorData_ if true constructor only copies attributes, if false constructor also copies content of vector
 */
VectorData::VectorData(const VectorData &other_, bool copyVectorData_)
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
 * VectorData::setUseCutOffToRange
 * @brief setter of useCutOffToRange
 * @param val_ true if data shall be cut to range of minValue and maxValue during modification, otherwise false
 */
void VectorData::setUseCutOffToRange(bool val_) {
    useCutOffToRange = val_;
}

/**
 * VectorData::setMinMaxValue
 * @brief setter of minValue and maxValue
 * @param min_ new value for minValue
 * @param max_ new value for maxValue
 * @return returns true if it is allowed to set the range min_ -> max_
 *
 * NOTE : min has to be smaller than max
 */
bool VectorData::setMinMaxValue(double min_, double max_) {
    if (min_ < max_) {
        minValue = min_;
        maxValue = max_;
        return true;
    } else {
        return false;
    }
}

/**
 * VectorData::getSize
 * @brief returns the number of fields within the vector
 * @return returns the number of fields within the vector
 * NOTE : this is needed, because vector::size() returns only unsigned int
 */
int VectorData::getSize() const {
    return int( vector<double>::size() );
}

/**
 * VectorData::getValueAt
 * @brief returns value at the index 'index_' within the vector-data
 * @param index_ index of the data which is requested
 * @return returns data at index 'index_'
 *
 * NOTE : returns the data of index 0 if index is smaller than 0
 * NOTE : returns the data of index getSize() - 1 if index is bigger than getSize() - 1
 * NOTE : returns 0 if vector has no elements
 */
double VectorData::getValueAt(int index_) const {
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
 * VectorData::cutOffToRange
 * @brief cuts the value 'val_' into the range of minValue and maxValue
 * @param val_ value which is to cut
 * @return returns value which is cut into the range of minValue and maxValue
 */
double VectorData::cutOffToRange(double val_) const {
    if (getUseCutOffToRange()) {
        double min = getMinValue();
        double max = getMaxValue();
        if (val_ < min) {
            val_ = min;
        } else if (val_ > max) {
            val_ = max;
        }
    }
    return val_;
}

/* --- operators --- */

/**
 * VectorData::operator =
 * @brief assignment-operator, copies all content of other_
 * @param other_ VectorData object to copy from
 * @return returns a new VectorData instance which is copied from other_
 * creates a new instance of VectorData and copies the attributes
 * and vector-data of other_ to it
 */
VectorData& VectorData::operator=( const VectorData& other_) {
    // proof for identical address
    if (this == &other_) {
        return (*this);
    }

    // copy attributes
    resize(other_.getSize());
    setUseCutOffToRange ( other_.getUseCutOffToRange()              );
    setMinMaxValue      ( other_.getMinValue(),other_.getMaxValue() );

    // copy vector-data
    int size_l = other_.getSize();
    for (int i = 0; i < size_l; i++) {
        (*this)[i] = other_[i];
    }

    return *this;

}

/**
 * VectorData::operator ==
 * @brief equality-operator, checks if all content is equal
 * @param other_ VectorData-object to compare with
 * @return returns true if all attributes and vector-data are equal, otherwise false
 * checks if all attributes and vector-data of *this and other_ are equal
 */
bool VectorData::operator==( const VectorData& other_) const {
    // check if attributes are identical
    bool isIdentical = ( getSize             () == other_.getSize             () &&
                         getUseCutOffToRange () == other_.getUseCutOffToRange () &&
                         getMinValue         () == other_.getMinValue         () &&
                         getMaxValue         () == other_.getMaxValue         () );

    // check if vector-data is identical
    if (isIdentical) {
        int size_l = getSize();
        for (int i = 0; i < size_l; i++) {
            if ((*this)[i] != other_[i]) {
                isIdentical = false;
            }
        }
    }

    return isIdentical;
}

/**
 * VectorData::operator !=
 * @brief inequality-operator, checks if anything is different
 * @param other_ VectorData object to compare with
 * @return returns true if any attribute or any content of the vector is different, otherwise false
 * checks if any attribute or any vector-data of *this and other_ is not equal
 */
bool VectorData::operator!=( const VectorData& other_) const {
    // check if identical and return the invers
    return (!((*this == other_)));
}

/**
 * operator <<
 * @brief shift-out operator for print VectorData-objects to console
 * @param ostream_ stream-object before printing VectorData-object to it
 * @param VectorData_ VectorData object which shall be printed
 * @return returns stream object after printing VectorData-object to it
 * prints out vector-data of VectorData object to console
 * printign a VectorData with the elements {1,2,4,5,100} looks like this:
 * [1,2,4,5,100]
 */
ostream& operator<<(ostream& ostream_, const VectorData VectorData_) {
    int size_l = VectorData_.getSize();

    ostream_ << "[";
    for (int i = 0; i < size_l -1; i++) {
        ostream_ << VectorData_.getValueAt( i ) << ",";

    }
    ostream_ << VectorData_.getValueAt((size_l-1)) << "]" << endl;
    return ostream_;
}

/**
 * VectorData::operator +
 * @brief addition-operator, adds a VectorData-object and an int value
 * @param val_ value to add with
 * @return returns a new VectorData-object
 *
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator+(double val_ ) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    for (int i = 0; i < resultVectorData.getSize(); i++) {
        resultVectorData[i] += val_;
        resultVectorData[i] = cutOffToRange(resultVectorData[i]);
    }
    return resultVectorData;
}

/**
 * VectorData::operator -
 * @brief substraction-operator, substracts an int value from a VectorData-object
 * @param val_ value to subtract from VectorData object
 * @return returns a new VectorData-object
 *
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator-(double val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    for (int i = 0; i < resultVectorData.getSize(); i++) {
        resultVectorData[i] -= val_;
        resultVectorData[i] = cutOffToRange(resultVectorData[i]);
    }
    return resultVectorData;
}

/**
 * VectorData::operator *
 * @brief multiplication-operator, multiplies a VectorData-object and an int value
 * @param val_ value to multiply with
 * @return returns a new VectorData-object
 *
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator*(double val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    for (int i = 0; i < resultVectorData.getSize(); i++) {
        resultVectorData[i] *= val_;
        resultVectorData[i] = cutOffToRange(resultVectorData[i]);
    }
    return resultVectorData;
}

/**
 * VectorData::operator /
 * @brief division-operator, divides a VectorData-object by an int value
 * @param val_ value to divide by
 * @return returns a new VectorData-object
 *
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator/(double val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    for (int i = 0; i < resultVectorData.getSize(); i++) {
        if (val_ != 0) {
            resultVectorData[i] /= val_;
        } else {
            resultVectorData[i] = 0;
        }

        resultVectorData[i] = cutOffToRange(resultVectorData[i]);
    }
    return resultVectorData;
}

/**
 * VectorData::operator +
 * @brief addition-operator, adds two VectorData-objects, element by element
 * @param val_ VectorData-object to add with
 * @return returns a new VectorData-object
 *
 * NOTE : can only get used for two VectorData-objects with same size
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator+( const VectorData& val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    if ((*this).getSize() == val_.getSize()) {
        for (int i = 0; i < resultVectorData.getSize(); i++) {
            resultVectorData[i] += val_[i];
            resultVectorData[i] = cutOffToRange(resultVectorData[i]);
        }
    }
    return resultVectorData;
}

/**
 * VectorData::operator -
 * @brief substraction-operator, substracts two VectorData-objects, element by element
 * @param val_ VectorData-object which is subtracted from *this
 * @return returns a new VectorData-object
 *
 * NOTE : can only get used for two VectorData-objects with same size
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator-( const VectorData& val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    if ((*this).getSize() == val_.getSize()) {
        for (int i = 0; i < resultVectorData.getSize(); i++) {
            resultVectorData[i] -= val_[i];
            resultVectorData[i] = cutOffToRange(resultVectorData[i]);
        }
    }
    return resultVectorData;
}

/**
 * VectorData::operator *
 * @brief multiplication-operator, multiplies two VectorData-objects, element by element
 * @param val_ VectorData-object to multiply with
 * @return returns a new VectorData-object
 *
 * NOTE : can only get used for two VectorData-objects with same size
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator*( const VectorData& val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    if ((*this).getSize() == val_.getSize()) {
        for (int i = 0; i < resultVectorData.getSize(); i++) {
            resultVectorData[i] *= val_[i];
            resultVectorData[i] = cutOffToRange(resultVectorData[i]);
        }
    }
    return resultVectorData;
}

/**
 * VectorData::operator /
 * @brief division-operator, divides two VectorData-objects, element by element
 * @param val_ VectorData-object by which *this is divided by
 * @return returns a new VectorData-object
 *
 * NOTE : can only get used for two VectorData-objects with same size
 * NOTE : uses VectorData::cutOffToRange if VectorData::useCutOffToRange == true
 */
VectorData VectorData::operator/( const VectorData& val_) const {
    // copy VectorData because operator is const
    VectorData resultVectorData(*this,true);
    if ((*this).getSize() == val_.getSize()) {
        for (int i = 0; i < resultVectorData.getSize(); i++) {
            if (val_[i] != 0) {
                resultVectorData[i] /= val_[i];
            } else {
                resultVectorData[i] = 0;
            }
            resultVectorData[i] = cutOffToRange(resultVectorData[i]);
        }
    }
    return resultVectorData;
}
