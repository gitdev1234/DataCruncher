/**
 * DataCruncher.cpp
 * Purpose: implements class DataCruncher
 *
 * @author Wall.Of.Death
 * @version 1.0 20160713
 */

#include "../include/DataCruncher.h"



/* --- constructors / destructors --- */

/**
 * DataCruncher::DataCruncher
 * @brief standard constructor of class DataCruncher
 * @param size_             size of vector
 * @param useCutOffToRange_ true if data is cut to minimum and maximum value during a modifyDataCruncher
 * @param minValue_         minimum value, needed for cutting data during modifyDataCruncher
 * @param maxValue_         maximum value, needed for cutting data during modifyDataCruncher
 *
 * creates vector of size 'size_' and initializes attributes
 *
 */
DataCruncher::DataCruncher(int size_     , bool useCutOffToRange_ ,
                                 int minValue_ , int maxValue_           )
    : vector<int>      ( size_             ),
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
    : vector<int>      ( other_.getSize()        ),
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
 * @param val_ true if data shall be cut to range of minValue and maxValue during modifyDataCruncher, otherwise false
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
 * NOTE : min has to be smaller than max
 */
bool DataCruncher::setMinMaxValue(int min_, int max_) {
    if (min_ < max_) {
        minValue = min_;
        maxValue = max_;
        return true;
    } else {
        return false;
    }
}

/* --- miscellaneous --- */
/**
 * DataCruncher::getSize
 * @brief returns the number of fields within the vector
 * @return returns the number of fields within the vector
 * NOTE : this is needed, because vector::size() returns only unsigned int
 */
int DataCruncher::getSize() const {
    return int( vector<int>::size() );
}

/**
 * DataCruncher::getValueAt
 * @brief returns value at the index 'index_' within the vector-data
 * @param index_ index of the data which is requested
 * @return returns data at index 'index_'
 * NOTE : returns the data of index 0 if index is smaller than 0
 * NOTE : returns the data of index getSize() - 1 if index is bigger than getSize() - 1
 * NOTE : returns 0 if vector has no elements
 */
int DataCruncher::getValueAt(int index_) const {
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


int DataCruncher::cutOffToRange(int val_) {
    int min = getMinValue();
    int max = getMaxValue();
    if (val_ < min) {
        val_ = min;
    } else if (val_ > max) {
        val_ = max;
    }
    return val_;
}

/* --- operators --- */

/**
 * DataCruncher::operator =
 * @brief assignment-operator, copies all content of other_
 * @param other_ DataCruncher object to copy from
 * @return returns a new DataCruncher instance which is copied from other
 * creates a new instance of DataCruncher and copies the attributes
 * and vector-data of other_ to it
 */
DataCruncher& DataCruncher::operator=( const DataCruncher& other_) {
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
 * DataCruncher::operator ==
 * @brief equality-operator, checks if all content is equal
 * @param other_ DataCruncher-object to compare with
 * @return returns true if all attributes and vector-data are equal, otherwise false
 * checks if all attributes and vector-data of *this and other_ are equal
 */
bool DataCruncher::operator==( const DataCruncher& other_) const {
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
 * DataCruncher::operator !=
 * @brief inequality-operator, checks if anything is different
 * @param other_ DataCruncher object to compare with
 * @return returns true if any attribute or any content of the vector is different, otherwise false
 * checks if any attribute or any vector-data of *this and other_ is not equal
 */
bool DataCruncher::operator!=( const DataCruncher& other_) const {
    // check if identical and return the invers
    return (!((*this == other_)));
}

/**
 * DataCruncher::operator +
 * @brief addition-operator, adds a DataCruncher-object and an int value
 * @param val_ value to add with
 * @return returns a new DataCruncher-object
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator+( int val_ ) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::ADD,temp);
}

/**
 * DataCruncher::operator -
 * @brief substraction-operator, substracts an int value from a DataCruncher-object
 * @param val_ value to subtract from DataCruncher object
 * @return returns a new DataCruncher-object
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator-( int val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::SUBTRACT,temp);
}

/**
 * DataCruncher::operator *
 * @brief multiplication-operator, multiplies a DataCruncher-object and an int value
 * @param val_ value to multiply with
 * @return returns a new DataCruncher-object
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator*( int val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::MULTIPLY,temp);
}

/**
 * DataCruncher::operator /
 * @brief division-operator, divides a DataCruncher-object by an int value
 * @param val_ value to divide by
 * @return returns a new DataCruncher-object
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator/( int val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::DIVIDE,temp);
}

/**
 * DataCruncher::operator +
 * @brief addition-operator, adds two DataCruncher-objects, element by element
 * @param val_ DataCruncher-object to add with
 * @return returns a new DataCruncher-object
 * NOTE : can only get used for two DataCruncher-objects with same size
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator+( const DataCruncher& val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::ADD_DataCruncher,temp);
}

/**
 * DataCruncher::operator -
 * @brief substraction-operator, substracts two DataCruncher-objects, element by element
 * @param val_ DataCruncher-object which is subtracted from *this
 * @return returns a new DataCruncher-object
 * NOTE : can only get used for two DataCruncher-objects with same size
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator-( const DataCruncher& val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::SUBTRACT_DataCruncher,temp);
}

/**
 * DataCruncher::operator *
 * @brief multiplication-operator, multiplies two DataCruncher-objects, element by element
 * @param val_ DataCruncher-object to multiply with
 * @return returns a new DataCruncher-object
 * NOTE : can only get used for two DataCruncher-objects with same size
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator*( const DataCruncher& val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    vector<int> temp = {val_};
    return resultDataCruncher.modifyDataCruncher(ModificationType::MULTIPLY_DataCruncher,temp);
}

/**
 * DataCruncher::operator /
 * @brief division-operator, divides two DataCruncher-objects, element by element
 * @param val_ DataCruncher-object by which *this is divided by
 * @return returns a new DataCruncher-object
 * NOTE : can only get used for two DataCruncher-objects with same size
 * NOTE : uses DataCruncher::cutOffToRange if DataCruncher::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if DataCruncher::useMultiChannel == true
 * NOTE : modifies all data if DataCruncher::useMultiChannel == false
 */
DataCruncher DataCruncher::operator/( const DataCruncher& val_) const {
    // copy DataCruncher because operator is const
    DataCruncher resultDataCruncher(*this,true);
    return resultDataCruncher.modifyDataCruncher(ModificationType::DIVIDE_DataCruncher,val_);
}

/**
 * operator <<
 * @brief shift-out operator for print DataCruncher-objects to console
 * @param ostream_ stream-object before printing DataCruncher-object to it
 * @param DataCruncher_ DataCruncher object which shall be printed
 * @return returns stream object after printing DataCruncher-object to it
 * prints out vector-data of DataCruncher object to console
 * printign a DataCruncher with the elements {1,2,4,5,100} looks like this:
 * [1,2,4,5,100]
 */
ostream& operator<<(ostream& ostream_, const DataCruncher DataCruncher_) {
    int size_l = DataCruncher_.getSize();

    ostream_ << "[";
    for (int i = 0; i < size_l -1; i++) {
        ostream_ << DataCruncher_.getValueAt( i ) << ",";

    }
    ostream_ << DataCruncher_.getValueAt((size_l-1)) << "]" << endl;
    return ostream_;
}

ostream& operator<<(ostream& ostream_, vector<double> val_) {
    ostream_ << "[";
    for (unsigned int i = 0; i < val_.size() -1; i++) {
        ostream_ << val_[i] << ",";
    }
    ostream_ << val_[val_.size()-1] << "]" << endl;
    return ostream_;
}

