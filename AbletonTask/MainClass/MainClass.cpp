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
    PrintWelcomeMessage();
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
            PrintInputErrorMessage();
        }
    }
}

void MainClass::ModuleCommandOperations()
{
    if (CheckModuleCommandInputSize() == false)
    {
        return;
    }

    ModuleClass tempModule;
    tempModule.name = splittedInputs[1];
    tempModule.operation = GetOperation(splittedInputs[2]);

    if (tempModule.operation != ERROR_OP)
    {
        modules.push_back(tempModule);
        PrintModuleIsAddedMessage();
    }
    else
    {
        PrintModuleIsNotAddedMessage();
    }
    PrintAllModules();
}

void MainClass::ConnectCommandOperations()
{
    if (CheckConnectCommandInputSize() == false)
    {
        return;
    }

    if (IsFirstModuleFound() == false || IsSecondModuleFound() == false)
    {
        PrintModuleIsNotFoundMessage();
        PrintAllModules();
        return;
    }

    bool headIsFound = false;
    bool tailIsFound = false;

    if (FindTailModule() > 0)
    {
        tailIsFound = true;
    }
    if (FindHeadModule() > 0)
    {
        headIsFound = true;
    }

    if ((headIsFound == false) && (tailIsFound == false)) /* Empty module list, module adding operations. */
    {
        AddFirstModuleAndMakeItHead();
        AddSecondModuleAndMakeItTail();
        PrintConnectionSuccesfullMessage();
    }
    else if ((headIsFound == true) && (tailIsFound == true)) /* Not empty module list, module adding operations. */
    {
        bool firstModuleIsHead = CheckIfFirstModuleIsNewHead();
        bool secondModuleIsTail = CheckIfSecondModuleIsNewTail();

        if (firstModuleIsHead == true)
        {
            ConnectFirstModuleAsHead();
        }
        else
        {
            ConnectFirstModule();
        }
        if (secondModuleIsTail == true)
        {
            ConnectSecondModuleAsTail();
        }
        else
        {
            ConnectsecondModule();
        }
        PrintConnectionSuccesfullMessage();
    }
    else
    {
        PrintHeadAndTailError();
    }
}

void MainClass::ProcessCommandOperations()
{
    if (CheckProcessCommandInputSize() == false)
    {
        return;
    }

    int headIndex = FindHeadModule();
    FillConsoleInputToTheModule(headIndex);
    modules[headIndex].DoModuleOperation();
    currentModuleIndexes.push_back(headIndex);

    while (true)
    {
        FindNextModules();
        FillNextModulesInputs();
        DoNextModuleOperations();
        if (IsNextModuleTail() == true)
        {
            PrintTailModuleOutput();
            break;
        }
        SwitchNextModulesWithCurrentModules();
    }
    ResetModuleListAndInputs();
    PrintEndOfTheProcessMessage();
}

bool MainClass::CheckConnectCommandInputSize()
{
    if (splittedInputs.size() < 3)
    {
        PrintInputErrorMessage();
        return (false);
    }
    return (true);
}

void MainClass::FillNextModulesInputs()
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

void MainClass::FindNextModules()
{
    nextModuleIndexes.clear();
    for (int i = 0; i < currentModuleIndexes.size(); i++)
    {
        for (int k = 0; k < modules[currentModuleIndexes[i]].outputTo.size(); k++)
        {
            nextModuleIndexes.push_back(GetModuleIndex(modules[currentModuleIndexes[i]].outputTo[k]));
        }
    }
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

int MainClass::FindTailModule()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].isTail == true)
        {
            return (i);
        }
    }

    return (-1);
}

int MainClass::FindHeadModule()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].isHead == true)
        {
            return (i);
        }
    }

    return (-1);
}

void MainClass::FillConsoleInputToTheModule(int index)
{
    for (int i = 1; i < splittedInputs.size(); i++)
    {
        modules[index].input.push_back(splittedInputs[i]);
    }
}

void MainClass::DoNextModuleOperations()
{
    for (int i = 0; i < nextModuleIndexes.size(); i++)
    {
        modules[nextModuleIndexes[i]].DoModuleOperation();
    }
}

bool MainClass::IsNextModuleTail()
{
    if (nextModuleIndexes.size() == 1)
    {
        if (modules[nextModuleIndexes[0]].isTail == true)
        {
            return (true);
        }
    }
    return (false);
}

void MainClass::SwitchNextModulesWithCurrentModules()
{
    currentModuleIndexes.clear();
    for (int i = 0; i < nextModuleIndexes.size(); i++)
    {
        currentModuleIndexes.push_back(nextModuleIndexes[i]);
    }
}

bool MainClass::CheckProcessCommandInputSize()
{
    if (splittedInputs.size() < 2)
    {
        PrintInputErrorMessage();
        return false;
    }
    return true;
}

void MainClass::ResetModuleListAndInputs()
{
    currentModuleIndexes.clear();
    nextModuleIndexes.clear();
    for (int i = 0; i < modules.size(); i++)
    {
        modules[i].input.clear();
        modules[i].output.clear();
    }
}

void MainClass::PrintTailModuleOutput()
{
    for (int i = 0; i < modules[nextModuleIndexes[0]].output.size(); i++)
    {
        cout << modules[nextModuleIndexes[0]].output[i] + " ";
    }
    cout << endl;
}

void MainClass::PrintEndOfTheProcessMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "End of process. " << endl;
#endif
}

void MainClass::PrintInputErrorMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Error input." << endl;
#endif
}

void MainClass::PrintWelcomeMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Ver: " << VERSION << " Waiting for commands." << endl;
#endif
}

void MainClass::PrintAllModules()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Available modules: " << endl;
    for (int i = 0; i < modules.size(); i++)
    {
        cout << modules[i].name << endl;
    }
#endif
}

void MainClass::PrintModuleIsNotFoundMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Module is not found." << endl;
#endif
}

void MainClass::PrintModuleIsAddedMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Module is added." << endl;
#endif
}

void MainClass::PrintModuleIsNotAddedMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Module is not added." << endl;
#endif
}

bool MainClass::CheckModuleCommandInputSize()
{
    if (splittedInputs.size() < 3)
    {
        PrintInputErrorMessage();
        return false;
    }
    return true;
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

bool MainClass::IsFirstModuleFound()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[1])
        {
            return (true);
        }
    }
    return (false);
}

bool MainClass::IsSecondModuleFound()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            return (true);
        }
    }
    return (false);
}

void MainClass::AddFirstModuleAndMakeItHead()
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
}

void MainClass::AddSecondModuleAndMakeItTail()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            modules[i].isTail = true;
            modules[i].inputFrom.push_back(splittedInputs[1]);
            break;
        }
    }
}

void MainClass::PrintConnectionSuccesfullMessage()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Connection succesfull." << endl;
#endif
}

bool MainClass::CheckIfFirstModuleIsNewHead()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            if (modules[i].isHead == true)
            {
                modules[i].isHead = false;
                return (true);
            }
        }
    }
}

bool MainClass::CheckIfSecondModuleIsNewTail()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[1])
        {
            if (modules[i].isTail == true)
            {
                modules[i].isTail = false;
                return (true);
            }
        }
    }
}

void MainClass::PrintHeadAndTailError()
{
#if (CONSOLE_OUTPUT == ACTIVE)
    cout << "Head and tail error." << endl;
#endif
}

void MainClass::ConnectFirstModuleAsHead()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[1])
        {
            modules[i].isHead = true;
            modules[i].inputFrom.clear();
            modules[i].outputTo.push_back(splittedInputs[2]);
            return;
        }
    }
}

void MainClass::ConnectFirstModule()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[1])
        {
            modules[i].outputTo.push_back(splittedInputs[2]);
            return;
        }
    }
}

void MainClass::ConnectSecondModuleAsTail()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            modules[i].isTail = true;
            modules[i].outputTo.clear();
            modules[i].inputFrom.push_back(splittedInputs[1]);
            return;
        }
    }
}

void MainClass::ConnectsecondModule()
{
    for (int i = 0; i < modules.size(); i++)
    {
        if (modules[i].name == splittedInputs[2])
        {
            modules[i].inputFrom.push_back(splittedInputs[1]);
            break;
        }
    }
}