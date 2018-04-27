#include "searcher.h"
#include "state.h"

class Ah1Searcher : public Searcher
{
    // get the number of misplaced tiles in state
    int misplaced_herustic(State &state)
    {
        vector<int>::const_iterator it = state.getDataIterator();
        int len = state.getDataSize(), value = 1;
        int misp_count = 0;
        while (len-- > 0)
        {
            if (*it++ != value++)
                misp_count++;
        }
        return misp_count;
    }
    bool search_loop()
    {
        search_count++;
        if (frontier.empty())
            return false;
        State *node = frontier.top();
        explored.insert(node);
        frontier.pop();
        if(node->goalTest())
        {
            solved = true;
            return true;
        }
        // expand this node
        State *newnode=NULL;
        if(node->moveUp(newnode))
        {
            newnode->path_cost = node->path_cost+1;
            newnode->evaluation = newnode->path_cost+misplaced_herustic(*newnode);
            frontier.push(newnode);
        }
        if(node->moveDown(newnode))
        {
            newnode->path_cost = node->path_cost+1;
            newnode->evaluation = newnode->path_cost+misplaced_herustic(*newnode);
            frontier.push(newnode);
        }
        if(node->moveLeft(newnode))
        {
            newnode->path_cost = node->path_cost+1;
            newnode->evaluation = newnode->path_cost+misplaced_herustic(*newnode);
            frontier.push(newnode);
        }
        if(node->moveRight(newnode))
        {
            newnode->path_cost = node->path_cost+1;
            newnode->evaluation = newnode->path_cost+misplaced_herustic(*newnode);
            frontier.push(newnode);
        }
    }

    void init()
    {
        init_state.path_cost = 0;
        init_state.evaluation = init_state.path_cost + misplaced_herustic(init_state);
        frontier.push(&init_state);
    }

  public:

    // free resources
    void reset()
    {
        ;
    }
    void search()
    {
        init();
        while(search_count<=max_search_count)
            search_loop();
    }
}