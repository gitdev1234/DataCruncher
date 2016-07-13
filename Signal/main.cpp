#include <iostream>
#include "signal.h"
#include "signal_template.h"

using namespace std;

int main() {
    cout << "Hello World" << endl;
    Signal s;
    for (int i = 0; i< 10; i++) {
        s.push_back(i);
    }
    cout << "--> OUTPUT s : " << endl;
    cout << s;


    // should work
    s.setChannelsCount(2);
    s.setUseMultiChannel(true);
    s.setSelectedChannel(0);
    cout << "--> OUTPUT s, channel 0/2: " << endl;
    cout << s;
    s.setSelectedChannel(1);
    cout << "--> OUTPUT s, channel 1/2: " << endl;
    cout << s;
    s.setUseMultiChannel(false);
    cout << "--> OUTPUT s " << endl;
    cout << s;

    // should fail
    s.setChannelsCount(3);
    s.setUseMultiChannel(true);
    s.setSelectedChannel(0);
    cout << "--> try to OUTPUT s, channel 0/3, will fail: " << endl;
    cout << s;
    s.setSelectedChannel(1);
    cout << "--> try to OUTPUT s, channel 1/3, will fail: " << endl;
    cout << s;
    s.setSelectedChannel(2);
    cout << "--> try to OUTPUT s, channel 2/3, will fail: " << endl;
    cout << s;

    // should work
    s.pop_back();
    s.setChannelsCount(3);
    s.setUseMultiChannel(true);
    s.setSelectedChannel(0);
    cout << "--> removed one element for size % 3 == 0" << endl;
    cout << "--> OUTPUT s, channel 0/3 : " << endl;
    cout << s ;
    s.setSelectedChannel(1);
    cout << "--> OUTPUT s, channel 1/3 : " << endl;
    cout << s;
    s.setSelectedChannel(2);
    cout << "--> OUTPUT s, channel 2/3 : " << endl;
    cout << s;
    s.setUseMultiChannel(false);
    cout << "--> OUTPUT s : " << endl;
    cout << s;

    // modifying without multi-channel
    s = s.modifySignal(ModificationType::ADD ,5);
    cout << "--> modify without multi-channel  : signal += 5 :" << s << endl;
    s = s.modifySignal(ModificationType::ADD ,-5);
    cout << "--> modify without multi-channel  : signal -= 5 :" << s << endl;
    s = s.modifySignal(ModificationType::MULTIPLY ,2);
    cout << "--> modify without multi-channel  : signal *= 2 :" << s << endl;
    s = s.modifySignal(ModificationType::MULTIPLY ,1.0/2.0);
    cout << "--> modify without multi-channel  : signal /= 2 :" << s << endl;

    // modifying with multi-channel
    s.setChannelsCount(3);
    s.setUseMultiChannel(true);
    s.setSelectedChannel(0);
    s = s.modifySignal(ModificationType::ADD ,5);
    cout << "--> modify with multi-channel : signal += 5, channel 0 :" << s << endl;
    s.setSelectedChannel(1);
    s = s.modifySignal(ModificationType::ADD ,5);
    cout << "--> modify with multi-channel : signal += 5, channel 1 :" << s << endl;
    s.setSelectedChannel(2);
    s = s.modifySignal(ModificationType::ADD ,5);
    cout << "--> modify with multi-channel : signal += 5, channel 2 :" << s << endl;

    // modify without multi-channel and min-max-range
    s.setUseCutOffToRange(true);
    s.setMinMaxValue(3, 7);
    s.setUseMultiChannel(false);
    s = s.modifySignal(ModificationType::ADD ,-5);
    cout << "--> modify without multi-channel, with min 3 and max 7 : signal -= 5 : " << s << endl;

    // test operators
    s.setUseCutOffToRange(false);
    s = s + 3;
    cout << "test operators : s = s + 3 = " << s;
}
