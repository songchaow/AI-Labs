// a state is represented by a matrix
#ifndef STATE_H
#define STATE_H

#include <vector>
#include <iostream>
using namespace std;

typedef struct Coord_struct
{
    int row;
    int col;
} Coord;

class State
{
private:
    vector<int> data;
protected:
    Coord bubble; // the zero value hole
    State* predecessor;
public:
    const Coord blocks[2]={{2,1},{2,3}};
    static const int height=5;
    static const int width=5;
    // The following 2 properties are assigned by searcher
    int evaluation=0;
    int path_cost=0;
    State()
    {
        data.resize(height*width,0);
        bubble.row=bubble.col=0;
    }
    State(vector<int> &datain, int bubbleIndex)
    {
        data=datain;
        bubble.row = bubbleIndex/width;
        bubble.col = bubbleIndex%width;
    }
    friend bool operator==(State& a,State& b)
    {
        vector<int>::const_iterator ita=a.getDataIterator(),itb=b.getDataIterator();
        for(int i = 0;i<a.getDataSize();i++)
        {
            if(*ita++!=*itb++)
                return false;
        }
        return true;
    }

    // test if curr_state satisfies the requirement of final state.
    bool goalTest()
    {
        int i,value,blockindex1=blocks[0].row*width+blocks[0].col;
        int blockindex2=blocks[1].row*width+blocks[1].col;
        for(i=0,value=1;i<data.size()-1;i++)
        {
            if(i==blockindex1 or i==blockindex2)
                continue;
            if(data[i]!=value++)
                return false;
        }
        // now i is data.size()-1, the last element should be zero
        if(data[i]==0) return true;
        else return false;
    }
protected:
    bool set(int row, int col, int data)
    {
        this->data.at(row*width+col)=data;
    }
private:
    bool checkEqual(int row, int col, const Coord* block)
    {
        if(row==block[0].row and col==block[0].col)
        {
            return true;
        }
        else if(row==block[1].row and col==block[1].col)
            return true;
        else return false;
    }
public:
    vector<int>::const_iterator getDataIterator() { return data.begin();}
    // get size of matrix, including two holes and zero.
    int getDataSize() {return data.size();}
    int visit(int row, int col)
    {
        return data.at(row*width+col);
    }
    // operations
    bool moveUp(State*& newstate)
    {
        if(checkEqual(bubble.row-1,bubble.col,blocks))
            return false;
        newstate = new State(*this);
        if(bubble.row>0)
        {
            newstate->set(bubble.row,bubble.col,visit(bubble.row-1,bubble.col));
            newstate->set(bubble.row-1,bubble.col,0);
            newstate->bubble.row--;
            newstate->predecessor = this;
            return true;
        }
        else
        {
            delete newstate;
            return false;
        }
    }
    bool moveDown(State*& newstate)
    {
        if(checkEqual(bubble.row+1,bubble.col,blocks))
            return false;
        newstate = new State(*this);
        if(bubble.row<height-1)
        {
            newstate->set(bubble.row,bubble.col,visit(bubble.row+1,bubble.col));
            newstate->set(bubble.row+1,bubble.col,0);
            newstate->bubble.row++;
            newstate->predecessor = this;
            return true;
        }
        else
        {
            delete newstate;
            return false;
        }
    }
    bool moveLeft(State*& newstate)
    {
        int offset = 1;
        if(bubble.col>0)
        {
            newstate = new State(*this);
            if(checkEqual(bubble.row,bubble.col-1,blocks))
                offset=2;
            newstate->set(bubble.row,bubble.col,visit(bubble.row,bubble.col-offset));
            newstate->set(bubble.row,bubble.col-offset,0);
            newstate->bubble.row--;
            newstate->predecessor = this;
            return true;
            
        }
        else return false;
    }
    bool moveRight(State*& newstate)
    {
        int offset = 1;
        if(bubble.col>0)
        {
            newstate = new State(*this);
            if(checkEqual(bubble.row,bubble.col+1,blocks))
                offset=2;
            newstate->set(bubble.row,bubble.col,visit(bubble.row,bubble.col+offset));
            newstate->set(bubble.row,bubble.col+offset,0);
            newstate->bubble.row--;
            newstate->predecessor = this;
            return true;
        }
        else return false;
    }
    
};

#endif