#include "searcher.h"
#include "state.h"

int Ah1Searcher::misplaced_herustic(State &state)
{
    vector<int>::const_iterator it = state.getDataIterator();
    vector<int>::const_iterator begin = it;
    int len = state.getDataSize(), value = 1;
    int misp_count = 0;
    while (len-- > 1)
    {
        if(it-begin == state.blocks[0].row*state.width+state.blocks[0].col)
            {it++;continue;}
        if(it-begin == state.blocks[1].row*state.width+state.blocks[1].col)
            {it++;continue;}
        if (*it++ != value++)
            misp_count++;
    }//47 75
    // check for the last zero element
    if(*it!=0) misp_count++;
    return misp_count;
}
bool Ah1Searcher::search_loop()
{
    search_count++;
    if (frontier.empty())
        return false;
    State *node = frontier.top();
    explored.insert(node);
    frontier.pop();
    if (node->goalTest())
    {
        solved = true;
        return true;
    }
    // expand this node
    State *newnode = NULL;
    if (node->moveUp(newnode))
    {
        newnode->path_cost = node->path_cost + 1;
        newnode->evaluation = newnode->path_cost + misplaced_herustic(*newnode);
        frontier.push(newnode);
    }
    if (node->moveDown(newnode))
    {
        newnode->path_cost = node->path_cost + 1;
        newnode->evaluation = newnode->path_cost + misplaced_herustic(*newnode);
        frontier.push(newnode);
    }
    if (node->moveLeft(newnode))
    {
        newnode->path_cost = node->path_cost + 1;
        newnode->evaluation = newnode->path_cost + misplaced_herustic(*newnode);
        frontier.push(newnode);
    }
    if (node->moveRight(newnode))
    {
        newnode->path_cost = node->path_cost + 1;
        newnode->evaluation = newnode->path_cost + misplaced_herustic(*newnode);
        frontier.push(newnode);
    }
}

void Ah1Searcher::init()
{
    init_state.path_cost = 0;
    init_state.evaluation = init_state.path_cost + misplaced_herustic(init_state);
    frontier.push(&init_state);
}

// free resources
void Ah1Searcher::reset()
{
    ;
}
void Ah1Searcher::search()
{
    init();
    while (search_count <= max_search_count)
        search_loop();
}