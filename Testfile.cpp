#include "FrequencyCounter.h"

int main()
{
    FrequencyCounter fc;

    map<char,int> freq = fc.countFrequency("hello");

    for(auto x : freq)
    {
        cout << x.first << " = " << x.second << endl;
    }
}
