#include "signal.h"

/* --- constructors / destructors --- */

Signal::Signal(  int length_ , bool useMultiChannel_ , int channelsCount_ )
        : vector<int>( length_ ),
          useMultiChannel(useMultiChannel_),
          channelsCount(channelsCount_) {}

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
    if (size() % val_ == 0) {
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
int Signal::size() const {
    return int( vector<int>::size() );
}

int Signal::value(int val_ ) const {
    if( size() < 1 )
        return 0.0;

    if( val_ < 0 )
        return (*this)[ 0 ];

    if( val_ > size()-1 )
        return (*this)[ size()-1 ];

    return (*this)[ val_ ];
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
    Signal res( size() );

    for( int i = 0; i < size(); i++ ) {
        res[ i ] = (*this)[ i ] + val_;
    }

    return res;
}


Signal Signal::operator-( int val_) const {
    Signal res( size() );

    for( int i = 0; i < size(); i++ ) {
        res[ i ] = (*this)[ i ] - val_;
    }

    return res;
}

Signal Signal::operator*( int val_) const {
    Signal res( size() );

    for( int i = 0; i < size(); i++ ) {
        res[ i ] = (*this)[ i ] * val_;
    }

    return res;
}

Signal Signal::operator+( const Signal& val_) const {
    if( size() != val_.size() ) {
        return *this;
    }

    Signal res( size() );

    for( int i = 0; i < size(); i++ ) {
        res[ i ] = (*this)[ i ] + val_.value(i);
    }

    return res;
}

Signal Signal::operator-( const Signal& val_) const {
    if( size() != val_.size() ) {
        return *this;
    }
    Signal res( size() );

    for( int i = 0; i < size(); i++ ) {
        res[ i ] = (*this)[ i ] - val_.value(i);
    }
    return res;
}

ostream& operator<<(ostream& ostream_, const Signal signal_) {
    int channelsCount = 1;
    int selectedChannel = 0;
    int size = signal_.size();
    if (signal_.getUseMultiChannel()) {
        channelsCount   = signal_.getChannelsCount();
        selectedChannel = signal_.getSelectedChannel();
        size = signal_.size() / channelsCount;
    }

    ostream_ << "[";
    for (int i = 0; i < size -1; i++) {
        ostream_ << signal_.value( i * channelsCount + selectedChannel) << ",";

    }
    ostream_ << signal_.value((size-1) * channelsCount + selectedChannel) << "]" << endl;
    return ostream_;
}
