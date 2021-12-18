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

#include "../Globals/GlobalFunctions.h"
#include "../ModuleClass/ModuleClass.h"

/**
 * @brief Main Class is responsible for main program operations.
 * 
 */
class MainClass
{
private:
    std::string userInput;
    std::vector<ModuleClass> modules;
    std::vector<std::string> splittedInputs;

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
     * @brief Main Class task loop.
     * 
     */
    void Run();

    /**
     * @brief Shows module is not found message.
     * 
     */
    void ModuleIsNotFoundMessage();

    /**
     * @brief 
     * 
     * @param currentModuleIndexes 
     */
    void FillNextModulesInputs(std::vector<int> currentModuleIndexes);

    /**
     * @brief 
     * 
     * @param currentModuleIndexes 
     * @return std::vector<int> 
     */
    std::vector<int> FindNextModules(std::vector<int> currentModuleIndexes);

    /**
     * @brief Reads user inputs from console and splits it via " " character.
     * 
     * @return string 
     */
    std::vector<std::string> ReadAndSplitUserInput();

    /**
     * @brief Does module command operations.
     * 
     */
    void ModuleCommandOperations();

    /**
     * @brief Does connect command operations.
     * 
     */
    void ConnectCommandOperations();

    /**
     * @brief Does process command operations.
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
     * @brief 
     * 
     * @param splittedList 
     * @return std::string 
     */
    std::string AddSplittedInputsTogether(std::vector<std::string> splittedList);

    /**
     * @brief 
     * 
     * @param s 
     * @param delim 
     * @return vector<std::string> 
     */
    std::vector<std::string> Split(const std::string &s, char delim);

    /**
     * @brief Get the Module Index
     * 
     * @param moduleName 
     * @return int 
     */
    int GetModuleIndex(std::string moduleName);
};

#endif