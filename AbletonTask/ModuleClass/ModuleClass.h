/**
 * @file ModuleClass.h
 * @author Halit Cetin (halitcetin@live.com)
 * @brief Module header file
 * @version 0.1
 * @date 2021-12-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MODULE_CLASS_H
#define MODULE_CLASS_H

#include "../Globals/Definitions.h"
#include "../Globals/Enums.h"
#include "../Globals/Structs.h"
#include "../Globals/GlobalVariables.h"
#include "../Globals/GlobalFunctions.h"

/**
 * @brief Module class represents a sound module. This module is 
 * used for connecting each other and alters its inputs.
 * 
 */
class ModuleClass
{
private:
public:
	bool isHead;
	bool isTail;
	std::string name;
	operations operation;
	std::vector<std::string> inputFrom;
	std::vector<std::string> outputTo;
	std::vector<std::string> input;
	std::vector<std::string> output;

	/**
	 * @brief Construct a new Module Class object
	 * 
	 */
	ModuleClass();

	/**
	 * @brief Destroy the Module Class object
	 * 
	 */
	~ModuleClass();

	/**
	 * @brief Get the Operation type.
	 * 
	 * @return operations 
	 */
	operations GetOperation();

	/**
	 * @brief Does module operations.
	 * 
	 * @details Reads inputs, alters it and writes to output vector.
	 * 
	 */
	void DoModuleOperation();
};
#endif