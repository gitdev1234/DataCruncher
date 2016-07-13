#include "signal.h"

/* --- constructors / destructors --- */

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
bool Signal::setSelectedChannel  (int  val_) {
    if ( (val_ <= getChannelsCount() - 1) && (val_ >= 0) ) {
        selectedChannel  = val_;
        return true;
    } else {
        return false;
    }
}

bool Signal::setUseMultiChannel  (bool val_) {
    if (getChannelsCount() > 1) {
        useMultiChannel = val_;
        return true;
    } else {
        useMultiChannel = false;
        return false;
    }
}

bool Signal::setChannelsCount    (int  val_) {
    if (getSize() % val_ == 0) {
        channelsCount = val_;
        return true;
    } else {
        return false;
    }
}

void Signal::setUseCutOffToRange(bool val_) {
    useCutOffToRange = val_;
}

bool Signal::setMinMaxValue(int min_, int max_) {
    if (min_ <= max_) {
        minValue = min_;
        maxValue = max_;
        return true;
    } else {
        return false;
    }
}

/* --- miscellaneous --- */
int Signal::getSize() const {
    return int( vector<int>::size() );
}

int Signal::getValueAt(int index_) const {
    if( getSize() < 1 )
        return 0.0;

    if( index_ < 0 )
        return (*this)[ 0 ];

    if( index_ > getSize()-1 )
        return (*this)[ getSize()-1 ];

    return (*this)[ index_ ];
}

/*
template  <typename type>
type Signal::modifySignal(ModificationType modificationType_, type val_ ) {
    int i = 10;
    switch (modificationType_) {
        ADD : i += val_; break;
        MULTIPLY : i *= val_; break;
    }
    type T;
    return T;
} */

/* --- operators --- */

Signal Signal::operator+( int val_ ) const {
    Signal res( getSize() );

    for( int i = 0; i < getSize(); i++ ) {
        res[ i ] = (*this)[ i ] + val_;
    }

    return res;
}


Signal Signal::operator-( int val_) const {
    Signal res( getSize() );

    for( int i = 0; i < getSize(); i++ ) {
        res[ i ] = (*this)[ i ] - val_;
    }

    return res;
}

Signal Signal::operator*( int val_) const {
    Signal res( getSize() );

    for( int i = 0; i < getSize(); i++ ) {
        res[ i ] = (*this)[ i ] * val_;
    }

    return res;
}

Signal Signal::operator+( const Signal& val_) const {
    if( getSize() != val_.getSize() ) {
        return *this;
    }

    Signal res( getSize() );

    for( int i = 0; i < getSize(); i++ ) {
        res[ i ] = (*this)[ i ] + val_.getValueAt(i);
    }

    return res;
}

Signal Signal::operator-( const Signal& val_) const {
    if( getSize() != val_.getSize() ) {
        return *this;
    }
    Signal res( getSize() );

    for( int i = 0; i < getSize(); i++ ) {
        res[ i ] = (*this)[ i ] - val_.getValueAt(i);
    }
    return res;
}

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
