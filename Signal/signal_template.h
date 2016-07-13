/**
 * signal_template.h
 * Purpose: implements template functions of class Signal
 *
 * @author Wall.Of.Death
 * @version 1.0 20160713
 */

#ifndef SIGNAL_TEMPLATE_H
#define SIGNAL_TEMPLATE_H

#include "signal.h"

template  <typename type>
Signal Signal::modifySignal(ModificationType modificationType_, vector<type> val_ ) {
    // check dimensions of val_
    if ( (modificationType_ == ModificationType::ADD_SIGNAL     ) ||
         (modificationType_ == ModificationType::SUBTRACT_SIGNAL) ||
         (modificationType_ == ModificationType::MULTIPLY_SIGNAL) ||
         (modificationType_ == ModificationType::DIVIDE_SIGNAL  ) ){
        if (int(val_.size()) != getSize()) {
            return (*this);
        }
    } else {
        if (int(val_.size()) > 1) {
            return (*this);
        }
    }


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

    // iterate through all data
    for( int i = 0; i < size_l; i++ ) {
        int index = i*channelsCount_l + selectedChannel_l;
        // modify

        switch (modificationType_) {
            case ModificationType::ADD             : (*this)[ index ] = (*this)[ index ] + val_[0]; break;
            case ModificationType::SUBTRACT        : (*this)[ index ] = (*this)[ index ] - val_[0]; break;
            case ModificationType::MULTIPLY        : (*this)[ index ] = (*this)[ index ] * val_[0]; break;
            case ModificationType::DIVIDE          : (*this)[ index ] = (*this)[ index ] / val_[0]; break;
            case ModificationType::ADD_SIGNAL      : (*this)[ index ] = (*this)[ index ] + val_[index]; break;
            case ModificationType::SUBTRACT_SIGNAL : (*this)[ index ] = (*this)[ index ] - val_[index]; break;
            case ModificationType::MULTIPLY_SIGNAL : (*this)[ index ] = (*this)[ index ] * val_[index]; break;
            case ModificationType::DIVIDE_SIGNAL   : (*this)[ index ] = (*this)[ index ] / val_[index]; break;
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
