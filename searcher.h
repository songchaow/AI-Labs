#ifndef SEARCHER_H
#define SEARCHER_H
#endif
#include <set>
#include <vector>
#include <queue>
#include "state.h"
using namespace std;
class Searcher
{
  public:
  class StateCmp
  {
  public:
    bool operator()(const State* a, const State* b)
    {
        if(a->evaluation>b->evaluation)
            return true;
        else return false;
    }
  };
    
  protected:
    State &init_state;
    // set<State> frontier;
    priority_queue<State*,vector<State*>,StateCmp> frontier;
    set<State*> explored;
    bool solved=false;
    static const long max_search_count = 50000000;
    long search_count = 0;
    

  public:
    Searcher(State &init_state) : init_state(init_state)
    {
    }
    bool getSolved() {return solved;}
};