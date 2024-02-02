#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <string> //ADDED for erase

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords) // string is a vector of letters
{
    set<string> tempset;
    string temp = "";
    while (!rawWords.empty())
    {
        if (rawWords[0] != ' ' && !ispunct(rawWords[0]))
        { // when the current char is valid
            temp += rawWords[0];
            rawWords.erase(rawWords.begin());
        }
        else if ((rawWords[0] == ' ' || ispunct(rawWords[0])) && temp.length() < 2)
        { // when current char is invalid and temp doesn't satisfy the requirement
            temp = "";
            rawWords.erase(rawWords.begin());
        }
        else if ((rawWords[0] == ' ' || ispunct(rawWords[0])) && temp.length() >= 2)
        { // when current char is invalid and temp satisfies requirement
            // upload temp as a keyword
            temp = convToLower(temp);
            tempset.insert(temp);
            temp = "";
        }
    }
    if(temp.length() >= 2)
    {
        temp = convToLower(temp);
        tempset.insert(temp);
        temp = "";
    }
    return tempset;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s)
{
    s.erase(s.begin(),
            std::find_if(s.begin(),
                         s.end(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s)
{
    s.erase(
        std::find_if(s.rbegin(),
                     s.rend(),
                     std::not1(std::ptr_fun<int, int>(std::isspace)))
            .base(),
        s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}
