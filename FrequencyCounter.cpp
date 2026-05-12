#include "FrequencyCounter.h"

map<char, int> FrequencyCounter::countFrequency(string text)
{
    map<char, int> freq;

    for(char ch : text)
    {
        freq[ch]++;
    }

    return freq;
}
