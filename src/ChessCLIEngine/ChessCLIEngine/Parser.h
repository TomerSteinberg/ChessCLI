#ifndef PARSER_H
#define PARSER_H
#pragma once

#include "ICommand.h"
#include "CommandFactory.h"
#include <sstream>
#include <iostream>
#include "UnkownCommandException.h"


class Parser
{
public:
	static std::vector<std::unique_ptr<ICommand>> parseCommand(std::string cmd);
	static std::vector<std::string> splitBySpace(std::string cmd);
	static std::vector<std::string> splitBySemicolon(std::string cmd);
private:
};

#endif
