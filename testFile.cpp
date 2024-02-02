#include <iostream>
#include <set>
#include "util.h"

int main()
{
    std::set<int> exp1 = {};
    std::set<int> exp2 = {11};

    std::set<int> output1 = setIntersection(exp1, exp2);
    std::set<int> output2 = setUnion(exp1, exp2);

    for (std::set<int>::iterator it = output1.begin(); it != output1.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    for (std::set<int>::iterator it = output2.begin(); it != output2.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}