/**
 * @file GlobalFunctions.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Global functions file
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "GlobalFunctions.h"

using namespace std;

std::string addSplittedInputsTogether(std::vector<std::string> splittedList)
{
    string output = "";

    for (int i = 1; i < splittedList.size(); i++)
    {
        output += splittedList[i];
    }

    return output;
}



vector<std::string> split(const std::string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}