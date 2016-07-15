/**
 * SignalProcessor.cpp
 * Purpose: implements class SignalProcessor
 *
 * @author Wall.Of.Death
 * @version 1.0 20160713
 */

#include "../include/SignalProcessor.h"
#include "../include/SignalProcessor_template.h"

/* --- constructors / destructors --- */

/**
 * SignalProcessor::SignalProcessor
 * @brief standard constructor of class SignalProcessor
 * @param size_             size of vector
 * @param useMultiChannel_  true if data consists of more than one channel
 * @param channelsCount_    the number of channels within the data
 * @param selectedChannel_  the index of the currently selected channel, first channel index is 0
 * @param useCutOffToRange_ true if data is cut to minimum and maximum value during a modifySignalProcessor
 * @param minValue_         minimum value, needed for cutting data during modifySignalProcessor
 * @param maxValue_         maximum value, needed for cutting data during modifySignalProcessor
 *
 * creates vector of size 'size_' and initializes attributes
 *
 */
SignalProcessor::SignalProcessor(int  size_             ,   bool useMultiChannel_  ,
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
 * SignalProcessor::SignalProcessor
 * @brief copy constructor of class SignalProcessor
 * @param other_ SignalProcessor object to copy from
 * @param copyVectorData_ if true constructor only copies attributes, if false constructor also copies content of vector
 */
SignalProcessor::SignalProcessor(const SignalProcessor &other_, bool copyVectorData_)
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
 * SignalProcessor::setSelectedChannel
 * @brief setter of selectedChannel
 * @param val_ index of channel to select
 * @return returns true if setting channel is allowed, otherwise false
 */
bool SignalProcessor::setSelectedChannel  (int  val_) {
    if ( (val_ <= getChannelsCount() - 1) && (val_ >= 0) ) {
        selectedChannel  = val_;
        return true;
    } else {
        return false;
    }
}

/**
 * SignalProcessor::setUseMultiChannel
 * @brief setter of useMultiChannel
 * @param val_ true if all functions shall interpret the vector as multi-channel-data
 * @return returns true if it is possible to interpret data as multi channel, otherwise false
 */
bool SignalProcessor::setUseMultiChannel  (bool val_) {
    if (getChannelsCount() > 1) {
        useMultiChannel = val_;
        return true;
    } else {
        useMultiChannel = false;
        return false;
    }
}

/**
 * SignalProcessor::setChannelsCount
 * @brief setter of channelsCount
 * @param val_ number of channels within the data
 * @return returns true if it is possible to interpret data as data with 'val_' channels, otherwise false
 */
bool SignalProcessor::setChannelsCount    (int  val_) {
    if (val_ == 0)  {
        setUseMultiChannel(false);
        setSelectedChannel(0);
        channelsCount = val_;

    } else if (getSize() % val_ == 0) {
        channelsCount = val_;
        return true;
    } else {
        return false;
    }
}

/**
 * SignalProcessor::setUseCutOffToRange
 * @brief setter of useCutOffToRange
 * @param val_ true if data shall be cut to range of minValue and maxValue during modifySignalProcessor, otherwise false
 */
void SignalProcessor::setUseCutOffToRange(bool val_) {
    useCutOffToRange = val_;
}

/**
 * SignalProcessor::setMinMaxValue
 * @brief setter of minValue and maxValue
 * @param min_ new value for minValue
 * @param max_ new value for maxValue
 * @return returns true if it is allowed to set the range min_ -> max_
 * NOTE : min has to be smaller than max
 */
bool SignalProcessor::setMinMaxValue(int min_, int max_) {
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
 * SignalProcessor::getSize
 * @brief returns the number of fields within the vector
 * @return returns the number of fields within the vector
 * NOTE : this is needed, because vector::size() returns only unsigned int
 */
int SignalProcessor::getSize() const {
    return int( vector<int>::size() );
}

/**
 * SignalProcessor::getValueAt
 * @brief returns value at the index 'index_' within the vector-data
 * @param index_ index of the data which is requested
 * @return returns data at index 'index_'
 * NOTE : returns the data of index 0 if index is smaller than 0
 * NOTE : returns the data of index getSize() - 1 if index is bigger than getSize() - 1
 * NOTE : returns 0 if vector has no elements
 */
int SignalProcessor::getValueAt(int index_) const {
    if( getSize() < 1 ) {
        return 0;
    }

    if (getUseMultiChannel()) {
        int size_l = getSize()/getChannelsCount();
        if( index_ < 0 ) {
            return (*this)[ 0  + getSelectedChannel()];
        }
        if( index_ > size_l-1 ) {
            return (*this)[ size_l * getChannelsCount() + getSelectedChannel() ];
        }
        return (*this)[ index_ * getChannelsCount() + getSelectedChannel() ];
    } else {
        if( index_ < 0 ) {
            return (*this)[ 0 ];
        }
        if( index_ > getSize()-1 ) {
            return (*this)[ getSize()-1 ];
        }
        return (*this)[ index_ ];
    }
}

int SignalProcessor::movingAverage(int index_, int neighbourhoodCount_, int channelsCount_, int selectedChannel_) {
    if (neighbourhoodCount_ == 0) {
        index_ = index_ * channelsCount_ + selectedChannel_;
        return getValueAt( index_ );
    } else {
        int sum = 0;
        for( int j = 0; j < neighbourhoodCount_; j++ ) {
            sum += getValueAt( index_ - neighbourhoodCount_ / 2 + j );
        }
        double temp = double(sum) / double(neighbourhoodCount_);
        return round(temp);
    }
}

vector<double> SignalProcessor::analyzeSignalProcessor(AnalyzationType analyzationType_) {
    // save attributes locally, to getting them in every loop cycle
    int  channelsCount_l    = 1;
    int  selectedChannel_l  = 0;
    int  size_l             = size();

    vector<double> result_l(1);
    vector<double> average_l;

    switch (analyzationType_) {
        case AnalyzationType::MINIMUM       : result_l[0] = INT_MAX; break;
        case AnalyzationType::MAXIMUM       : result_l[0] = INT_MIN; break;
        case AnalyzationType::AVERAGE       : result_l[0] =       0; break;
        case AnalyzationType::STD_DEVIATION : {   average_l = analyzeSignalProcessor(AnalyzationType::AVERAGE);
                                                result_l[0] = 0;};   break;
        default : ; // TODO
    }

    if (getUseMultiChannel()) {
        channelsCount_l    = getChannelsCount();
        selectedChannel_l  = getSelectedChannel();
        size_l             = size_l / channelsCount_l;
        for (int i = 0; i < channelsCount_l; i++) {
            result_l.push_back(result_l[0]);
        }

    }

    // iterate through all data
    for( int i = 0; i < size_l; i++ ) {
        for (int channelIndex = 0; channelIndex < channelsCount_l; channelIndex++) {
            int index = i*channelsCount_l + channelIndex;
            switch (analyzationType_) {
                case AnalyzationType::MINIMUM       : if ( (*this)[ index ] < result_l[channelIndex] ) {
                                                        result_l[channelIndex] = (*this)[ index ];
                                                      }; break;
                case AnalyzationType::MAXIMUM       : if ( (*this)[ index ] > result_l[channelIndex] ) {
                                                        result_l[channelIndex] = (*this)[ index ];
                                                      }; break;
                case AnalyzationType::AVERAGE       : result_l[channelIndex] += (*this)[ index ]; break;
                case AnalyzationType::STD_DEVIATION : result_l[channelIndex] += pow((double((*this)[ index ]) - double(average_l[channelIndex])),2); break;
                default : ; // TODO
            }
        }


    }



    for (int channelIndex = 0; channelIndex < channelsCount_l; channelIndex++) {
        switch (analyzationType_) {
            case AnalyzationType::AVERAGE       : result_l[channelIndex] /= size_l; break;
            case AnalyzationType::STD_DEVIATION : sqrt(result_l[channelIndex] / size_l); break;
            default : ; // TODO
        }
    }



    return result_l;
}


/* --- operators --- */

/**
 * SignalProcessor::operator =
 * @brief assignment-operator, copies all content of other_
 * @param other_ SignalProcessor object to copy from
 * @return returns a new SignalProcessor instance which is copied from other
 * creates a new instance of SignalProcessor and copies the attributes
 * and vector-data of other_ to it
 */
SignalProcessor& SignalProcessor::operator=( const SignalProcessor& other_) {
    // proof for identical address
    if (this == &other_) {
        return (*this);
    }

    // copy attributes
    resize(other_.getSize());
    setChannelsCount    ( other_.getChannelsCount()                 );
    setUseMultiChannel  ( other_.getUseMultiChannel()               );
    setSelectedChannel  ( other_.getSelectedChannel()               );
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
 * SignalProcessor::operator ==
 * @brief equality-operator, checks if all content is equal
 * @param other_ SignalProcessor-object to compare with
 * @return returns true if all attributes and vector-data are equal, otherwise false
 * checks if all attributes and vector-data of *this and other_ are equal
 */
bool SignalProcessor::operator==( const SignalProcessor& other_) const {
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
 * SignalProcessor::operator !=
 * @brief inequality-operator, checks if anything is different
 * @param other_ SignalProcessor object to compare with
 * @return returns true if any attribute or any content of the vector is different, otherwise false
 * checks if any attribute or any vector-data of *this and other_ is not equal
 */
bool SignalProcessor::operator!=( const SignalProcessor& other_) const {
    // check if identical and return the invers
    return (!((*this == other_)));
}

/**
 * SignalProcessor::operator +
 * @brief addition-operator, adds a SignalProcessor-object and an int value
 * @param val_ value to add with
 * @return returns a new SignalProcessor-object
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator+( int val_ ) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    vector<int> temp = {val_};
    return resultSignalProcessor.modifySignalProcessor(ModificationType::ADD,temp);
}

/**
 * SignalProcessor::operator -
 * @brief substraction-operator, substracts an int value from a SignalProcessor-object
 * @param val_ value to subtract from SignalProcessor object
 * @return returns a new SignalProcessor-object
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator-( int val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    vector<int> temp = {val_};
    return resultSignalProcessor.modifySignalProcessor(ModificationType::SUBTRACT,temp);
}

/**
 * SignalProcessor::operator *
 * @brief multiplication-operator, multiplies a SignalProcessor-object and an int value
 * @param val_ value to multiply with
 * @return returns a new SignalProcessor-object
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator*( int val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    vector<int> temp = {val_};
    return resultSignalProcessor.modifySignalProcessor(ModificationType::MULTIPLY,temp);
}

/**
 * SignalProcessor::operator /
 * @brief division-operator, divides a SignalProcessor-object by an int value
 * @param val_ value to divide by
 * @return returns a new SignalProcessor-object
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator/( int val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    vector<int> temp = {val_};
    return resultSignalProcessor.modifySignalProcessor(ModificationType::DIVIDE,temp);
}

/**
 * SignalProcessor::operator +
 * @brief addition-operator, adds two SignalProcessor-objects, element by element
 * @param val_ SignalProcessor-object to add with
 * @return returns a new SignalProcessor-object
 * NOTE : can only get used for two SignalProcessor-objects with same size
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator+( const SignalProcessor& val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    return resultSignalProcessor.modifySignalProcessor(ModificationType::ADD_SIGNALPROCESSOR,val_);
}

/**
 * SignalProcessor::operator -
 * @brief substraction-operator, substracts two SignalProcessor-objects, element by element
 * @param val_ SignalProcessor-object which is subtracted from *this
 * @return returns a new SignalProcessor-object
 * NOTE : can only get used for two SignalProcessor-objects with same size
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator-( const SignalProcessor& val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    return resultSignalProcessor.modifySignalProcessor(ModificationType::SUBTRACT_SIGNALPROCESSOR,val_);
}

/**
 * SignalProcessor::operator *
 * @brief multiplication-operator, multiplies two SignalProcessor-objects, element by element
 * @param val_ SignalProcessor-object to multiply with
 * @return returns a new SignalProcessor-object
 * NOTE : can only get used for two SignalProcessor-objects with same size
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator*( const SignalProcessor& val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    return resultSignalProcessor.modifySignalProcessor(ModificationType::MULTIPLY_SIGNALPROCESSOR,val_);
}

/**
 * SignalProcessor::operator /
 * @brief division-operator, divides two SignalProcessor-objects, element by element
 * @param val_ SignalProcessor-object by which *this is divided by
 * @return returns a new SignalProcessor-object
 * NOTE : can only get used for two SignalProcessor-objects with same size
 * NOTE : uses SignalProcessor::cutOffToRange if SignalProcessor::useCutOffToRange == true
 * NOTE : only modifies data of a specific channel if SignalProcessor::useMultiChannel == true
 * NOTE : modifies all data if SignalProcessor::useMultiChannel == false
 */
SignalProcessor SignalProcessor::operator/( const SignalProcessor& val_) const {
    // copy SignalProcessor because operator is const
    SignalProcessor resultSignalProcessor(*this,true);
    return resultSignalProcessor.modifySignalProcessor(ModificationType::DIVIDE_SIGNALPROCESSOR,val_);
}

/**
 * operator <<
 * @brief shift-out operator for print SignalProcessor-objects to console
 * @param ostream_ stream-object before printing SignalProcessor-object to it
 * @param SignalProcessor_ SignalProcessor object which shall be printed
 * @return returns stream object after printing SignalProcessor-object to it
 * prints out vector-data of SignalProcessor object to console
 * printign a SignalProcessor with the elements {1,2,4,5,100} looks like this:
 * [1,2,4,5,100]
 */
ostream& operator<<(ostream& ostream_, const SignalProcessor signalProcessor_) {
    /*int channelsCount = 1;
    int selectedChannel = 0;
    int size = signalProcessor_.getSize();
    if (signalProcessor_.getUseMultiChannel()) {
        channelsCount   = signalProcessor_.getChannelsCount();
        selectedChannel = signalProcessor_.getSelectedChannel();
        size = signalProcessor_.getSize() / channelsCount;
    }

    ostream_ << "[";
    for (int i = 0; i < size -1; i++) {
        ostream_ << signalProcessor_.getValueAt( i * channelsCount + selectedChannel) << ",";

    }
    ostream_ << signalProcessor_.getValueAt((size-1) * channelsCount + selectedChannel) << "]" << endl;
    return ostream_;*/
    int channelsCount = 1;
    int selectedChannel = 0;
    int size = signalProcessor_.getSize();
    if (signalProcessor_.getUseMultiChannel()) {
        channelsCount   = signalProcessor_.getChannelsCount();
        selectedChannel = signalProcessor_.getSelectedChannel();
        size = signalProcessor_.getSize() / channelsCount;
    }

    ostream_ << "[";
    for (int i = 0; i < size -1; i++) {
        ostream_ << signalProcessor_.getValueAt( i ) << ",";

    }
    ostream_ << signalProcessor_.getValueAt((size-1)) << "]" << endl;
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
