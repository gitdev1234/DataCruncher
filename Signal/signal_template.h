#ifndef SIGNAL_TEMPLATE_H
#define SIGNAL_TEMPLATE_H

#include "signal.h"

template  <typename type>
Signal Signal::modifySignal(ModificationType modificationType_, type val_ ) {
/*
    // copy all attributes except for vector data
    Signal res((*this),false);
    res.setChannelsCount    ( (*this).getChannelsCount()   );
    res.setSelectedChannel  ( (*this).getSelectedChannel() );
    res.setUseMultiChannel  ( (*this).getUseMultiChannel() );
    res.setUseCutOffToRange ( (*this).getUseCutOffToRange());
    res.setMinMaxValue      ( (*this).getMinValue(),(*this).getMaxValue());
*/

    // save attributes locally, to getting them in every loop cycle
    int  channelsCount_l    = 1;
    int  selectedChannel_l  = 0;
    int  size_l             = size();
    bool useCutOffToRange_l = getUseCutOffToRange();
    if (getUseMultiChannel()) {
        channelsCount_l    = getChannelsCount();
        selectedChannel_l  = getSelectedChannel();
        size_l             = size_l / channelsCount_l;
    }

    //TODO Bug :
    //modify : signal += 5, channel 0 :[5,0,0,6,0,0,7,0,0]
    //modify : signal += 5, channel 1 :[10,5,5,11,5,5,12,5,5]
    //modify : signal += 5, channel 2 :[15,10,10,16,10,10,17,10,10]

    // iterate through all data
    for( int i = 0; i < size_l; i++ ) {
        int index = i*channelsCount_l + selectedChannel_l;
        // modify

        switch (modificationType_) {
            case ModificationType::ADD      : (*this)[ index ] = (*this)[ index ] + val_; break;
            case ModificationType::MULTIPLY : (*this)[ index ] = (*this)[ index ] * val_; break;
            default : (*this)[index] = 0;
        }

        if (useCutOffToRange_l) {
            (*this)[ index ] = cutOffToRange((*this)[ index ]);
        }
    }

    return (*this);

}

template  <typename type>
type Signal::cutOffToRange(type val_) {
    int min = getMinValue();
    int max = getMaxValue();
    if (val_ < min) {
        val_ = min;
    } else if (val_ > max) {
        val_ = max;
    }
    return val_;
}


#endif // SIGNAL_TEMPLATE_H
