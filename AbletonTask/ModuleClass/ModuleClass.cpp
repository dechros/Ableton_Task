/**
 * @file ModuleClass.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Module file
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ModuleClass.h"

using namespace std;

ModuleClass::ModuleClass()
{
    name = "";
    operation = ERROR_OP;
    isHead = false;
    isTail = false;
}

ModuleClass::~ModuleClass()
{
}

operations ModuleClass::GetOperation()
{
    return operation;
}

void ModuleClass::DoModuleOperation()
{
    switch (operation)
    {
    case ERROR_OP:
#if (CONSOLE_OUTPUT == ACTIVE)
        cout << "Invalid operation." << endl;
#endif
        break;

    case ECHO:
        for (int i = 0; i < input.size(); i++)
        {
            string echoOutput = input[i] + input[i];
            output.push_back(echoOutput);
        }
        break;

    case REVERSE:
        for (int i = 0; i < input.size(); i++)
        {
            string reverseOutput(input[i]);
            reverse(reverseOutput.begin(), reverseOutput.end());
            output.push_back(reverseOutput);
        }
        break;

    case DELAY:
        output.push_back("hello");
        for (int i = 0; i < input.size(); i++)
        {
            output.push_back(input[i]);
        }
        break;

    case NOOP:
        for (int i = 0; i < input.size(); i++)
        {
            output.push_back(input[i]);
        }
        break;

    default:
#if (CONSOLE_OUTPUT == ACTIVE)
        cout << "Invalid operation." << endl;
#endif
        break;
    }
}