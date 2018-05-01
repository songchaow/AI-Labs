#include "test.h"
#include "../src/utility.h"
#include "../src/searcher.h"
bool TestCase::testinput1()
{
    State* initState = Utility::readFromFile("input/input1.txt");
    Ah1Searcher searcher= Ah1Searcher(*initState);
    searcher.search();

}