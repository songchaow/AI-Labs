// #ifndef UTILITY_H
// #define UTILITY_H
// file utilities

#include <fstream>
#include <string>
#include "state.h"
#include "searcher.h"
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
    static bool printTrace(State* final_state, Searcher* searcher, string filename)
    {
        if(final_state==NULL)
            return false;
        vector<int>::const_iterator it;
        int len = final_state->getDataSize();
        int width = final_state->width;
        ofstream foutput = ofstream(filename);
        if(!foutput.is_open()) return false;
        foutput << searcher->tellDuration() <<endl;
        foutput << final_state->getTrace() << endl;
        foutput << final_state->path_cost;
        // do
        // {
        //     it = final_state->getDataIterator();
        //     int i = 0;
        //     while(i<len)
        //     {
        //         foutput << *it;
        //         foutput << ' ';
        //         if((i+1)%width==0)
        //             foutput << endl;
        //         i++;
        //         it++;
        //     }
        //     foutput << endl;
            
        // }while((final_state=final_state->getPredecessor()));
        return true;
    }
};

// #endif