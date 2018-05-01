// #ifndef UTILITY_H
// #define UTILITY_H
// file utilities

#include <fstream>
#include <string>
#include "state.h"
using namespace std;
class Utility
{
public:
    static State* readFromFile(string filename)
    {
        ifstream finput = ifstream(filename);
        if(!finput.is_open())
            return NULL;
        vector<int> matrix;
        int value;
        int bubbleIndex,bubbleCount=0;
        State* initstate = new State();
        while(finput >> value)
        {
            matrix.push_back(value);
            if(value==0) {bubbleIndex=matrix.size()-1;bubbleCount++;}
        }
        if(matrix.size()!=State::height)
            cout << "warning: wrong input element number.";
        if(bubbleCount>=2)
            cout << "warning: more than one bubble is found.";
        State* initState = new State(matrix,bubbleIndex);
        return initState;
    }
};

// #endif