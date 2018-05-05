#ifndef SEARCHER_H
#define SEARCHER_H

#include <set>
#include <vector>
#include <queue>
#include <chrono>
#include "state.h"
using namespace std;
class Searcher
{
  public:
  class StatePriorityCmp
  {
  public:
    bool operator()(const State* a, const State* b)
    {
        if(a->evaluation>b->evaluation)
            return true;
        else return false;
    }
  };
  class StateCmp
  {
  public:
    bool operator()(const State* a, const State* b)
    {
        vector<int>::const_iterator ita = ((State*)a)->getDataIterator();
        vector<int>::const_iterator itb = ((State*)b)->getDataIterator();
        ;
        // use dictionary order. if a>b, return true
        for(int i=0;i<((State*)a)->getDataSize();i++)
        {
            if(*ita>*itb)
                return true;
            else if(*ita<*itb)
                return false;
            else {ita++;itb++;continue;}
        }
        return false;

    }
  };
    
  protected:
    State &init_state;
    State* final_state = NULL;
    // set<State> frontier;
    priority_queue<State*,vector<State*>,StatePriorityCmp> frontier;
    set<State*,StateCmp> explored;
    bool solved=false;
    static const long max_search_count = 50000000;
    long search_count = 0;
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> start_time;
    std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> stop_time;
    

  public:
    Searcher(State &init_state) : init_state(init_state)
    {
    }
    bool getSolved() {return solved;}
    State* getSolvedState() {return final_state;}
    double tellDuration()
    {
        std::chrono::duration<double> elapsed_seconds = stop_time - start_time;
        return elapsed_seconds.count();
    }
};

class Ah1Searcher : public Searcher
{
    // get the number of misplaced tiles in state
    int misplaced_herustic(State &state);
    bool search_loop();
    void init();
public:
    Ah1Searcher(State &init_state):Searcher(init_state)
    {
        ;
    }
    void reset();
    void search();
};

#endif