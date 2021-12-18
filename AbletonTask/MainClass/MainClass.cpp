/**
 * @file MainClass.cpp
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Main class file
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "MainClass.h"

using namespace std;

MainClass::MainClass()
{
    userInput = "";
}

MainClass::~MainClass()
{
}

void MainClass::Run()
{
    cout << "Waiting for commands." << endl;

    while (true)
    {
        splittedInputs = ReadAndSplitUserInput();

        if (splittedInputs[0] == "module")
        {
            ModuleCommandOperations();
        }
        else if (splittedInputs[0] == "connect")
        {
            ConnectCommandOperations();
        }
        else if (splittedInputs[0] == "process")
        {
            ProcessCommandOperations();
        }
        else
        {
            cout << "Error input." << endl;
        }
    }
}

void MainClass::ProcessCommandOperations()
{
    if (splittedInputs.size() < 2)
    {
        cout << "Input length error." << endl;
        return;
    }

    int headIndex = -1;
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].isHead == true)
        {
            headIndex = i;
            break;
        }
    }

    for (int i = 1; i < splittedInputs.size(); i++)
    {
        modules[headIndex].input.push_back(splittedInputs[i]);
    }

    modules[headIndex].DoModuleOperation();

    vector<int> currentModuleIndexes;
    vector<int> nextModuleIndexes;
    currentModuleIndexes.push_back(headIndex);
    while (true)
    {
        nextModuleIndexes = FindNextModules(currentModuleIndexes);
        FillNextModulesInputs(currentModuleIndexes);

        for (int i = 0; i < nextModuleIndexes.size(); i++)
        {
            modules[nextModuleIndexes[i]].DoModuleOperation();
        }

        if(nextModuleIndexes.size() == 1)
        {
            if(modules[nextModuleIndexes[0]].isTail == true)
            {
                for (int i = 0; i < modules[nextModuleIndexes[0]].output.size(); i++)
                {
                    cout << modules[nextModuleIndexes[0]].output[i] + " ";
                }
                cout << endl;
                break;
            }
        }

        currentModuleIndexes.clear();
        for (int i = 0; i < nextModuleIndexes.size(); i++)
        {
            currentModuleIndexes.push_back(nextModuleIndexes[i]);
        }
    }

    for (int i = 0; i < modules.size(); i++)
    {
        modules[i].input.clear();
        modules[i].output.clear();
    }

    cout << "End of process. " << endl;
    return;
}

void MainClass::ModuleCommandOperations()
{
    if (splittedInputs.size() < 3)
    {
        cout << "Input length error." << endl;
        return;
    }

    ModuleClass tempModule;
    tempModule.name = splittedInputs[1];
    tempModule.operation = GetOperation(splittedInputs[2]);

    if (tempModule.operation != ERROR_OP)
    {
        modules.push_back(tempModule);

        cout << "Module is added." << endl;
        cout << tempModule.name << endl;
        cout << tempModule.operation << endl;
    }
    else
    {
        cout << "Module is not added." << endl;
    }

    PrintAllModules();
}

void MainClass::PrintAllModules()
{
    cout << "Available modules: " << endl;
    for (int i = 0; i < modules.size(); i++)
    {
        cout << modules[i].name << endl;
    }
}

operations MainClass::GetOperation(std::string operationstr)
{
    if (operationstr == "echo")
    {
        return (ECHO);
    }
    else if (operationstr == "reverse")
    {
        return (REVERSE);
    }
    else if (operationstr == "delay")
    {
        return (DELAY);
    }
    else if (operationstr == "noop")
    {
        return (NOOP);
    }
    else
    {
        return (ERROR_OP);
    }
}

void MainClass::ModuleIsNotFoundMessage()
{
    cout << "Module is not found." << endl;
    PrintAllModules();
}

void MainClass::FillNextModulesInputs(std::vector<int> currentModuleIndexes) /* 0 */
{
    for (int i = 0; i < currentModuleIndexes.size(); i++)
    {
        for (int j = 0; j < modules[currentModuleIndexes[i]].outputTo.size(); j++)
        {
            int tempModuleIndex = GetModuleIndex(modules[currentModuleIndexes[i]].outputTo[j]);

            for (int k = 0; k < modules[currentModuleIndexes[i]].output.size(); k++)
            {
                modules[tempModuleIndex].input.push_back(modules[currentModuleIndexes[i]].output[k]);
            }
        }
    }
}

vector<int> MainClass::FindNextModules(std::vector<int> currentModuleIndexes)
{
    vector<int> nextModuleIndexes;

    for (int i = 0; i < currentModuleIndexes.size(); i++)
    {
        for (int k = 0; k < modules[currentModuleIndexes[i]].outputTo.size(); k++)
        {
            nextModuleIndexes.push_back(GetModuleIndex(modules[currentModuleIndexes[i]].outputTo[k]));
        }
    }

    return nextModuleIndexes;
}

int MainClass::GetModuleIndex(std::string moduleName)
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == moduleName)
        {
            return i;
        }
    }

    return -1;
}

vector<string> MainClass::ReadAndSplitUserInput()
{
    userInput = "";
    getline(cin, userInput);
    return Split(userInput, ' ');
}

std::string MainClass::AddSplittedInputsTogether(std::vector<std::string> splittedList)
{
    string output = "";

    for (int i = 1; i < splittedList.size(); i++)
    {
        output += splittedList[i];
    }

    return output;
}

vector<std::string> MainClass::Split(const std::string &s, char delim)
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

void MainClass::ConnectCommandOperations()
{
    if (splittedInputs.size() < 3)
    {
        cout << "Input length error." << endl;
        return;
    }

    bool moduleIsFound = false;

    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[1])
        {
            moduleIsFound = true;
            break;
        }
    }

    if (moduleIsFound == false)
    {
        ModuleIsNotFoundMessage();
        return;
    }

    moduleIsFound = false;
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            moduleIsFound = true;
            break;
        }
    }

    if (moduleIsFound == false)
    {
        ModuleIsNotFoundMessage();
        return;
    }

    /* Everything is fine. Connect the module. */

    bool headIsFound = false;
    bool tailIsFound = false;

    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].isHead == true)
        {
            headIsFound = true;
            break;
        }
    }

    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].isTail == true)
        {
            tailIsFound = true;
            break;
        }
    }

    if ((headIsFound == false) && (tailIsFound == false))
    {
        for (int i = 0; i < modules.size(); i++)
        {
            if (modules[i].name == splittedInputs[1])
            {
                modules[i].isHead = true;
                modules[i].outputTo.push_back(splittedInputs[2]);
                break;
            }
        }

        for (int i = 0; i < modules.size(); i++)
        {
            if (modules[i].name == splittedInputs[2])
            {
                modules[i].isTail = true;
                modules[i].inputFrom.push_back(splittedInputs[1]);
                break;
            }
        }

        cout << "Connection succesfull." << endl;
    }
    else if ((headIsFound == true) && (tailIsFound == true))
    {
        bool firstModuleIsHead = false;
        bool secondModuleIsTail = false;

        for (int i = 0; i < modules.size(); i++)
        {
            if (modules[i].name == splittedInputs[2])
            {
                if (modules[i].isHead == true)
                {
                    modules[i].isHead = false;
                    firstModuleIsHead = true;
                }
                break;
            }
        }

        if (firstModuleIsHead == true)
        {
            cout << "firstModuleIsHead == true" << endl;

            for (int i = 0; i < modules.size(); i++)
            {
                if (modules[i].name == splittedInputs[1])
                {
                    modules[i].isHead = true;
                    modules[i].inputFrom.clear();
                    modules[i].outputTo.push_back(splittedInputs[2]);
                    break;
                }
            }
        }
        else
        {
            cout << "firstModuleIsHead == false" << endl;

            for (int i = 0; i < modules.size(); i++)
            {
                if (modules[i].name == splittedInputs[1])
                {
                    modules[i].outputTo.push_back(splittedInputs[2]);
                    break;
                }
            }
        }

        for (int i = 0; i < modules.size(); i++)
        {
            if (modules[i].name == splittedInputs[1])
            {
                if (modules[i].isTail == true)
                {
                    modules[i].isTail = false;
                    secondModuleIsTail = true;
                }
                break;
            }
        }

        if (secondModuleIsTail == true)
        {
            cout << "secondModuleIsTail == true" << endl;

            for (int i = 0; i < modules.size(); i++)
            {
                if (modules[i].name == splittedInputs[2])
                {
                    modules[i].isTail = true;
                    modules[i].outputTo.clear();
                    modules[i].inputFrom.push_back(splittedInputs[1]);
                    break;
                }
            }
        }
        else
        {
            cout << "secondModuleIsTail == false" << endl;

            for (int i = 0; i < modules.size(); i++)
            {
                if (modules[i].name == splittedInputs[2])
                {
                    modules[i].inputFrom.push_back(splittedInputs[1]);
                    break;
                }
            }
        }
        cout << "Connection succesfull." << endl;
    }
    else
    {
        cout << "Head and tail error." << endl;
        return;
    }
}