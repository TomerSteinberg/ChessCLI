#include "ICommand.h"
#include <vector>
#include <unordered_map>

#include "UnkownCommandException.h"
#include "ExceededMaxArgumentsException.h"

#include "HelpCommand.h"
#include "ClearCommand.h"
#include "QuitCommand.h"

#pragma once
#define CREATE_COMMAND_OBJECT(x) args.size() <= x::maxArg ? std::unique_ptr<ICommand>(std::make_unique<x>(args)) : throw ExceededMaxArgumentsException(args.size(), x::maxArg)

// pointer to a function that returns an ICommand object from a vector of strings
using CommandCreatorFunction = std::unique_ptr<ICommand>(*) (std::vector<std::string>);


class CommandFactory
{
public:
	static std::unique_ptr<ICommand> createCommand(std::string cmdName, std::vector<std::string> args);
};

