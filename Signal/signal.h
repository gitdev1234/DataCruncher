#ifndef SIGNAL_H
#define SIGNAL_H

#include <vector>
#include <iostream>
#include <climits>

using namespace std;


enum ModificationType {ADD, MULTIPLY};


class Signal : public vector<int>{
    public:
        /* --- constructors / destructors --- */
        Signal( int length_ = 0, bool multiChannelData_ = false, int channelsCount_ = 1 );

        /* --- miscellaneous --- */
        int size() const;
        int value( int val_ ) const;
        template  <typename type>
        Signal modifySignal(ModificationType modificationType_, type val_ ) ;
        template  <typename type>
        type cutOffToRange(type val_);

        /* --- getter / setter --- */
        bool getUseMultiChannel  () const    { return useMultiChannel; };
        int  getChannelsCount    () const    { return channelsCount;   };
        int  getSelectedChannel  () const    { return selectedChannel; };
        bool getUseCutOffToRange () const    { return useCutOffToRange;};
        int  getMinValue         () const    { return minValue;        };
        int  getMaxValue         () const    { return maxValue;        };
        bool setSelectedChannel  (int  val_) ;
        bool setUseMultiChannel  (bool val_) ;
        bool setChannelsCount    (int  val_) ;
        void setUseCutOffToRange (bool val_) ;
        bool setMinMaxValue      (int  min_, int max_);

        /* --- operators --- */
        Signal operator+( int val_) const;
        Signal operator-( int val_) const;
        Signal operator*( int val_) const;
        Signal operator+( const Signal& val_) const;
        Signal operator-( const Signal& val_) const;
        friend ostream& operator<<(ostream& ostream_, const Signal signal_);
    private:
        bool useMultiChannel  = false;
        int  channelsCount    = 1;
        int  selectedChannel  = 0;
        bool useCutOffToRange = false;
        int  minValue         = INT_MIN;
        int  maxValue         = INT_MAX;


};

#endif // SIGNAL_H
