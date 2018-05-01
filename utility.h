// #ifndef UTILITY_H
// #define UTILITY_H
// file utilities

#include <fstream>
#include <string>
#include "state.h"
using namespace std;
class Utility
{
    static State* readFromFile(string filename)
    {
        ifstream finput = ifstream(filename);
        if(!finput.is_open())
            return NULL;
        vector<int> matrix;
        int value;
        State* initstate = new State();
        while(finput >> value)
        {
            matrix.push_back(value);
        }
        if(matrix.size()!=State::height)
            cout << "warning: wrong input element number.";
        State* initState = new State(matrix);
        return initState;
    }
};

// #endif