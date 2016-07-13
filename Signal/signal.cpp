/**
 * signal.cpp
 * Purpose: implements class Signal
 *
 * @author Wall.Of.Death
 * @version 1.0 20160713
 */

#include "signal.h"

/* --- constructors / destructors --- */

/**
 * Signal::Signal
 * @brief standard constructor of class Signal
 * @param size_             size of vector
 * @param useMultiChannel_  true if data consists of more than one channel
 * @param channelsCount_    the number of channels within the data
 * @param selectedChannel_  the index of the currently selected channel, first channel index is 0
 * @param useCutOffToRange_ true if data is cut to minimum and maximum value during a modifySignal
 * @param minValue_         minimum value, needed for cutting data during modifySignal
 * @param maxValue_         maximum value, needed for cutting data during modifySignal
 *
 * creates vector of size 'size_' and initializes attributes
 *
 */
Signal::Signal(int  size_             ,   bool useMultiChannel_  ,
               int  channelsCount_    ,   int selectedChannel_   ,
               bool useCutOffToRange_ ,   int minValue_          ,
               int  maxValue_                                    )
    : vector<int>      ( size_             ),
      useMultiChannel  ( useMultiChannel_  ),
      channelsCount    ( channelsCount_    ),
      selectedChannel  ( selectedChannel_  ),
      useCutOffToRange ( useCutOffToRange_ ),
      minValue         ( minValue_         ),
      maxValue         ( maxValue_         )
{ }

/**
 * Signal::Signal
 * @brief copy constructor of class Signal
 * @param other_ signal object to copy from
 * @param copyVectorData_ if true constructor only copies attributes, if false constructor also copies content of vector
 */
Signal::Signal(const Signal &other_, bool copyVectorData_)
    : vector<int>      ( other_.getSize()        ),
      useMultiChannel  ( other_.getUseMultiChannel()  ),
      channelsCount    ( other_.getChannelsCount()    ),
      selectedChannel  ( other_.getSelectedChannel()  ),
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
 * Signal::setSelectedChannel
 * @brief setter of selectedChannel
 * @param val_ index of channel to select
 * @return returns true if setting channel is allowed, otherwise false
 */
bool Signal::setSelectedChannel  (int  val_) {
    if ( (val_ <= getChannelsCount() - 1) && (val_ >= 0) ) {
        selectedChannel  = val_;
        return true;
    } else {
        return false;
    }
}

/**
 * Signal::setUseMultiChannel
 * @brief setter of useMultiChannel
 * @param val_ true if all functions shall interpret the vector as multi-channel-data
 * @return returns true if it is possible to interpret data as multi channel, otherwise false
 */
bool Signal::setUseMultiChannel  (bool val_) {
    if (getChannelsCount() > 1) {
        useMultiChannel = val_;
        return true;
    } else {
        useMultiChannel = false;
        return false;
    }
}

/**
 * Signal::setChannelsCount
 * @brief setter of channelsCount
 * @param val_ number of channels within the data
 * @return returns true if it is possible to interpret data as data with 'val_' channels, otherwise false
 */
bool Signal::setChannelsCount    (int  val_) {
    if (getSize() % val_ == 0) {
        channelsCount = val_;
        return true;
    } else {
        return false;
    }
}

/**
 * Signal::setUseCutOffToRange
 * @brief setter of useCutOffToRange
 * @param val_ true if data shall be cut to range of minValue and maxValue during modifySignal, otherwise false
 */
void Signal::setUseCutOffToRange(bool val_) {
    useCutOffToRange = val_;
}

/**
 * Signal::setMinMaxValue
 * @brief setter of minValue and maxValue
 * @param min_ new value for minValue
 * @param max_ new value for maxValue
 * @return returns true if it is allowed to set the range min_ -> max_
 * NOTE : min has to be smaller than max
 */
bool Signal::setMinMaxValue(int min_, int max_) {
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
 * Signal::getSize
 * @brief returns the number of fields within the vector
 * @return returns the number of fields within the vector
 * NOTE : this is needed, because vector::size() returns only unsigned int
 */
int Signal::getSize() const {
    return int( vector<int>::size() );
}

/**
 * Signal::getValueAt
 * @brief returns value at the index 'index_' within the vector-data
 * @param index_ index of the data which is requested
 * @return returns data at index 'index_'
 * NOTE : returns the data of index 0 if index is smaller than 0
 * NOTE : returns the data of index getSize() - 1 if index is bigger than getSize() - 1
 * NOTE : returns 0 if vector has no elements
 */
int Signal::getValueAt(int index_) const {
    if( getSize() < 1 )
        return 0;

    if( index_ < 0 )
        return (*this)[ 0 ];

    if( index_ > getSize()-1 )
        return (*this)[ getSize()-1 ];

    return (*this)[ index_ ];
}

/* --- operators --- */

/**
 * Signal::operator =
 * @brief assignment-operator, copies all content of other_
 * @param other_ Signal object to copy from
 * @return returns a new Signal instance which is copied from other
 * creates a new instance of Signal and copies the attributes
 * and vector-data of other_ to it
 */
Signal& Signal::operator=( const Signal& other_) {
    // proof for identical address
    if (this == &other_) {
        return (*this);
    }

    // copy attributes
    Signal( other_.getSize(),            other_.getUseMultiChannel()  ,other_.getChannelsCount(),
                   other_.getSelectedChannel(), other_.getUseCutOffToRange() ,other_.getMinValue()     ,
                   other_.getMaxValue()         );

    // copy vector-data
    int size_l = other_.getSize();
    for (int i = 0; i < size_l; i++) {
        (*this)[i] = other_[i];
    }

    return *this;

}

/**
 * Signal::operator ==
 * @brief equality-operator, checks if all content is equal
 * @param other_ Signal-object to compare with
 * @return returns true if all attributes and vector-data are equal, otherwise false
 * checks if all attributes and vector-data of *this and other_ are equal
 */
bool Signal::operator==( const Signal& other_) const {
    // check if attributes are identical
    bool isIdentical = ( getSize             () == other_.getSize             () &&
                         getUseMultiChannel  () == other_.getUseMultiChannel  () &&
                         getChannelsCount    () == other_.getChannelsCount    () &&
                         getSelectedChannel  () == other_.getSelectedChannel  () &&
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
 * Signal::operator !=
 * @brief inequality-operator, checks if anything is different
 * @param other_ Signal object to compare with
 * @return returns true if any attribute or any content of the vector is different, otherwise false
 * checks if any attribute or any vector-data of *this and other_ is not equal
 */
bool Signal::operator!=( const Signal& other_) const {
    // check if identical and return the invers
    return (!((*this == other_)));
}

/**
 * Signal::operator +
 * @brief addition-operator, adds a Signal-object and an int value
 * @param val_ value to add with
 * @return returns a new Signal-object
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator+( int val_ ) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    vector<int> temp = {val_};
    return resultSignal.modifySignal(ModificationType::ADD,temp);
}

/**
 * Signal::operator -
 * @brief substraction-operator, substracts an int value from a Signal-object
 * @param val_ value to subtract from signal object
 * @return returns a new Signal-object
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator-( int val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    vector<int> temp = {val_};
    return resultSignal.modifySignal(ModificationType::SUBTRACT,temp);
}

/**
 * Signal::operator *
 * @brief multiplication-operator, multiplies a Signal-object and an int value
 * @param val_ value to multiply with
 * @return returns a new Signal-object
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator*( int val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    vector<int> temp = {val_};
    return resultSignal.modifySignal(ModificationType::MULTIPLY,temp);
}

/**
 * Signal::operator /
 * @brief division-operator, divides a Signal-object by an int value
 * @param val_ value to divide by
 * @return returns a new Signal-object
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator/( int val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    vector<int> temp = {val_};
    return resultSignal.modifySignal(ModificationType::DIVIDE,temp);
}

/**
 * Signal::operator +
 * @brief addition-operator, adds two Signal-objects, element by element
 * @param val_ Signal-object to add with
 * @return returns a new Signal-object
 * NOTE : can only get used for two Signal-objects with same size
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator+( const Signal& val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    return resultSignal.modifySignal(ModificationType::ADD_SIGNAL,val_);
}

/**
 * Signal::operator -
 * @brief substraction-operator, substracts two Signal-objects, element by element
 * @param val_ Signal-object which is subtracted from *this
 * @return returns a new Signal-object
 * NOTE : can only get used for two Signal-objects with same size
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator-( const Signal& val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    return resultSignal.modifySignal(ModificationType::SUBTRACT_SIGNAL,val_);
}

/**
 * Signal::operator *
 * @brief multiplication-operator, multiplies two Signal-objects, element by element
 * @param val_ Signal-object to multiply with
 * @return returns a new Signal-object
 * NOTE : can only get used for two Signal-objects with same size
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator*( const Signal& val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    return resultSignal.modifySignal(ModificationType::MULTIPLY_SIGNAL,val_);
}

/**
 * Signal::operator /
 * @brief division-operator, divides two Signal-objects, element by element
 * @param val_ Signal-object by which *this is divided by
 * @return returns a new Signal-object
 * NOTE : can only get used for two Signal-objects with same size
 * NOTE : uses Signal::cutOffToRange if Signal::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if Signal::useMultiChannel == true
 * NOTE : modifies all data if Signal::useMultiChannel == false
 */
Signal Signal::operator/( const Signal& val_) const {
    // copy signal because operator is const
    Signal resultSignal(*this,true);
    return resultSignal.modifySignal(ModificationType::DIVIDE_SIGNAL,val_);
}

/**
 * operator <<
 * @brief shift-out operator for print Signal-objects to console
 * @param ostream_ stream-object before printing Signal-object to it
 * @param signal_ Signal object which shall be printed
 * @return returns stream object after printing Signal-object to it
 * prints out vector-data of Signal object to console
 * printign a signal with the elements {1,2,4,5,100} looks like this:
 * [1,2,4,5,100]
 */
ostream& operator<<(ostream& ostream_, const Signal signal_) {
    int channelsCount = 1;
    int selectedChannel = 0;
    int size = signal_.getSize();
    if (signal_.getUseMultiChannel()) {
        channelsCount   = signal_.getChannelsCount();
        selectedChannel = signal_.getSelectedChannel();
        size = signal_.getSize() / channelsCount;
    }

    ostream_ << "[";
    for (int i = 0; i < size -1; i++) {
        ostream_ << signal_.getValueAt( i * channelsCount + selectedChannel) << ",";

    }
    ostream_ << signal_.getValueAt((size-1) * channelsCount + selectedChannel) << "]" << endl;
    return ostream_;
}
