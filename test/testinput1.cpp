#include "test.h"
#include "../src/utility.h"
#include "../src/searcher.h"
bool TestCase::testinput1()
{
    State* initState = Utility::readFromFile("input/input.txt");
    Ah1Searcher searcher= Ah1Searcher(*initState);
    searcher.search();
    if(searcher.getSolved())
        Utility::printTrace(searcher.getSolvedState(), &searcher, "output/target.txt");

}


// 输入自己的名字，然后计算出对应的序列号。名字计算一串数字，与0x1234异或，十进制就是序列号
// 序列号生成算法的分析 分析另一个CrackMe