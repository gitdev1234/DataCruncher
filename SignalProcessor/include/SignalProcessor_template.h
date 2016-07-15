/**
 * SignalProcessor_template.h
 * Purpose: implements template functions of class SignalProcessor
 *
 * @author Wall.Of.Death
 * @version 1.0 20160713
 */

#ifndef SIGNALPROCESSOR_TEMPLATE_H
#define SIGNALPROCESSOR_TEMPLATE_H

#include "SignalProcessor.h"

/**
 * SignalProcessor::modifySignalProcessor
 * @brief modifySignalProcessor iterates through all vector-data and modifies it depending on modificationType_
 * @param modificationType_ defines how SignalProcessor shall be modified
 * @param val_ value which shall be added, subtacted, multiplied ... with *this, if val_ is scalar use a vector with one element
 * @return returns the new SignalProcessor-object after modification
 * NOTE : This function encapsulates all logic for multiple channels within the data
 *        and for cutting data to the range of minValue and maxValue
 */
template  <typename type>
SignalProcessor SignalProcessor::modifySignalProcessor(ModificationType modificationType_, vector<type> val_ ) {
    // check dimensions of val_
    if ( (modificationType_ == ModificationType::ADD_SIGNALPROCESSOR     ) ||
         (modificationType_ == ModificationType::SUBTRACT_SIGNALPROCESSOR) ||
         (modificationType_ == ModificationType::MULTIPLY_SIGNALPROCESSOR) ||
         (modificationType_ == ModificationType::DIVIDE_SIGNALPROCESSOR  ) ){
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
            case ModificationType::DIVIDE          : if (val_[0] == 0) {
                                                        (*this)[ index ] = 0;
                                                     } else {
                                                        (*this)[ index ] = (*this)[ index ] / val_[0]; break;
                                                     }; break;
            case ModificationType::ADD_SIGNALPROCESSOR      : (*this)[ index ] = (*this)[ index ] + val_[index]; break;
            case ModificationType::SUBTRACT_SIGNALPROCESSOR : (*this)[ index ] = (*this)[ index ] - val_[index]; break;
            case ModificationType::MULTIPLY_SIGNALPROCESSOR : (*this)[ index ] = (*this)[ index ] * val_[index]; break;
            case ModificationType::DIVIDE_SIGNALPROCESSOR   :  if (val_[index] == 0) {
                                                                  (*this)[ index ] = 0;
                                                               } else {
                                                                  (*this)[ index ] = (*this)[ index ] / val_[index]; break;
                                                               }; break;

            default : (*this)[index] = 0;
        }

        if (useCutOffToRange_l) {
            (*this)[ index ] = cutOffToRange((*this)[ index ]);
        }
    }

    return (*this);

}

template  <typename type>
type SignalProcessor::cutOffToRange(type val_) {
    int min = getMinValue();
    int max = getMaxValue();
    if (val_ < min) {
        val_ = min;
    } else if (val_ > max) {
        val_ = max;
    }
    return val_;
}




#endif // SIGNALPROCESSOR_TEMPLATE_H
