#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H

#include <iostream>
#include <map>
using namespace std;

class FrequencyCounter
{
public:
    map<char, int> countFrequency(string text);
};

#endif
