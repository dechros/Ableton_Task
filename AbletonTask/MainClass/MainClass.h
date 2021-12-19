/**
 * @file MainClass.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Main class header file
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MAIN_TASK_H
#define MAIN_TASK_H

#include "../Globals/Definitions.h"
#include "../Globals/Structs.h"
#include "../Globals/Enums.h"
#include "../Globals/GlobalFunctions.h"
#include "../Globals/GlobalVariables.h"

#include "../ModuleClass/ModuleClass.h"

/**
 * @brief Main Class is responsible for main program operations.
 * 
 * @details This class reads user inputs as commands and does what user is commanded.
 * Command List: 
 * 
 * 1. "Module" definition, adds a new module to the network
 * Ex: module <name> <operation>
 * 2. "Connection" command, connects the output of one module to the input of another
 * Ex: connect <name1> <name2>
 * 3. "Process" command, feeds input into the first module in the network
 * Ex: process <...list of strings to be processed>
 * 
 */
class MainClass
{
private:
    /**
     * @brief The raw user input to be proccessed.
     * 
     */
    std::string userInput;

    /**
     * @brief Added sound module list. Detailed module description is in the 
     * Module Class description.
     * 
     */
    std::vector<ModuleClass> modules;

    /**
     * @brief User inputs are splitted and placed in this list.
     * 
     * @details Splitting operation is made via " " (space) character.
     * 
     */
    std::vector<std::string> splittedInputs;

    /**
     * @brief Currently "in use" module list.
     * 
     */
    std::vector<int> currentModuleIndexes;

    /**
     * @brief Next "to be activated" module list.
     * 
     */
    std::vector<int> nextModuleIndexes;

    /**
     * @brief Connects second module.
     * 
     */
    void ConnectsecondModule();

    /**
     * @brief Connects second module as tail module.
     * 
     */
    void ConnectSecondModuleAsTail();

    /**
     * @brief Connects first module.
     * 
     */
    void ConnectFirstModule();

    /**
     * @brief Connects first module as head module.
     * 
     */
    void ConnectFirstModuleAsHead();

    /**
     * @brief Prints head and tail error to the console.
     * 
     */
    void PrintHeadAndTailError();

    /**
     * @brief Checks if newly added first module is the new head.
     * 
     * @return true Yes, first module is the new head
     * @return false No, first module is not the new head
     */
    bool CheckIfFirstModuleIsNewHead();

    /**
     * @brief Checks if newly added first module is the new head.
     * 
     * @return true Yes, first module is the new head
     * @return false No, first module is not the new head
     */
    bool CheckIfSecondModuleIsNewTail();

    /**
     * @brief Prints connection succesfull message.
     * 
     */
    void PrintConnectionSuccesfullMessage();

    /**
     * @brief Adds first module and makes it head.
     * 
     */
    void AddFirstModuleAndMakeItHead();

    /**
     * @brief Adds second module and makes it tail.
     * 
     */
    void AddSecondModuleAndMakeItTail();

    /**
     * @brief Checks if second module is found.
     * 
     * @return true Second module is found
     * @return false Second module is not found
     */
    bool IsSecondModuleFound();

    /**
     * @brief Checks if first module is found.
     * 
     * @return true First module is found
     * @return false First module is not found
     */
    bool IsFirstModuleFound();

    /**
     * @brief Prints module is added message to the console.
     * 
     */
    void PrintModuleIsAddedMessage();

    /**
     * @brief Prints module is not added error to the console.
     * 
     */
    void PrintModuleIsNotAddedMessage();

    /**
     * @brief Prints input error to the console.
     * 
     */
    void PrintInputErrorMessage();

    /**
     * @brief Prints welcome message to the console.
     * 
     */
    void PrintWelcomeMessage();

    /**
     * @brief Prints end of the process message.
     * 
     */
    void PrintEndOfTheProcessMessage();

    /**
     * @brief Resets current module list, next module list and
     * all module inputs/outputs.
     * 
     */
    void ResetModuleListAndInputs();

    /**
     * @brief Checks if user connect command length is valid or not.
     * 
     * @return true Input is valid
     * @return false Input is not valid
     */
    bool CheckConnectCommandInputSize();

    /**
     * @brief Checks if user module command length is valid or not.
     * 
     * @return true Input is valid
     * @return false Input is not valid
     */
    bool CheckModuleCommandInputSize();

    /**
     * @brief Checks if user process command length is valid or not.
     * 
     * @return true Input is valid
     * @return false Input is not valid
     */
    bool CheckProcessCommandInputSize();

    /**
     * @brief When next module operations are finished, this function
     * switches the next sound modules list with current list.
     * 
     */
    void SwitchNextModulesWithCurrentModules();

    /**
     * @brief Fills input of the selected module.
     * 
     * @param index Selected module index
     */
    void FillConsoleInputToTheModule(int index);

    /**
     * @brief Prints tail sound module output to the console.
     * 
     */
    void PrintTailModuleOutput();

    /**
     * @brief Checks if next sound module is tail.
     * 
     * @details If a module is tail, this means its output should be printed
     * to the console and this is the end of the "process" command.
     * 
     * @return true Next sound module is tail
     * @return false Next sound module is not tail
     */
    bool IsNextModuleTail();

    /**
     * @brief Finds head sound module index.
     * 
     * @return int head module index
     */
    int FindHeadModule();

    /**
     * @brief Finds tail sound module index.
     * 
     * @return int tail module index
     */
    int FindTailModule();

    /**
     * @brief Shows module is not found message in the console.
     * 
     */
    void PrintModuleIsNotFoundMessage();

    /**
     * @brief Transfers current string data to the next modules.
     * 
     * @details This function detects currently activated modules and reads
     * their output content, reads where to write their output content as
     * input and Writes output content to next sound modules. 
     */
    void FillNextModulesInputs();

    /**
     * @brief Finds next "to be activated" sound modules.
     * 
     * @details This function detects currently activated modules and reads
     * their output content. By doing this, it detects which sound modules
     * needs to be activated soon.
     */
    void FindNextModules();

    /**
     * @brief According to the nextModuleIndexes list, does next module
     * operations.
     * 
     * @details Each module is a class which is implemented in Module Class.
     * Each module has its operation functions inside.
     * 
     */
    void DoNextModuleOperations();

    /**
     * @brief Reads user inputs from console and splits it via " " character.
     * 
     * @return string Splitted user input
     */
    std::vector<std::string> ReadAndSplitUserInput();

    /**
     * @brief Does "module" user command operations.
     * 
     * @details  Module definition, adds a new module to the network.
     * Ex: module <name> <operation>
     * 
     */
    void ModuleCommandOperations();

    /**
     * @brief Does "connect" user command operations.
     * 
     * @details Connection command, connects the output of one module to the
     * input of another.
     * Ex: connect <name1> <name2>
     * 
     */
    void ConnectCommandOperations();

    /**
     * @brief Does "process" command operations.
     * 
     * @details Process command, feeds input into the first module in the network
     * Ex: process <...list of strings to be processed>
     * 
     */
    void ProcessCommandOperations();

    /**
     * @brief Converts string operation to enum type.
     * 
     * @param operationstr String type operation
     * @return operations Enum type operation
     */
    operations GetOperation(std::string operationstr);

    /**
     * @brief Prints all added modules to the console.
     * 
     */
    void PrintAllModules();

    /**
     * @brief Concats a list of string and makes one long string.
     * 
     * @param splittedList List op small strings to be added together
     * @return std::string Concated string
     */
    std::string AddSplittedInputsTogether(std::vector<std::string> splittedList);

    /**
     * @brief Splits a string with a specified character.
     * 
     * @param s String to be splittes
     * @param delim Split character
     * @return vector<std::string> Splitted string list
     */
    std::vector<std::string> Split(const std::string &s, char delim);

    /**
     * @brief Searches module name and finds its index in the modules list.
     * 
     * @param moduleName Module name to be searched
     * @return int Module index
     */
    int GetModuleIndex(std::string moduleName);

public:
    /**
     * @brief Construct a new Main Class object
     * 
     */
    MainClass();

    /**
     * @brief Destroy the Main Class object
     * 
     */
    ~MainClass();

    /**
     * @brief Main Class infinite task loop.
     * 
     */
    void Run();
};

#endif