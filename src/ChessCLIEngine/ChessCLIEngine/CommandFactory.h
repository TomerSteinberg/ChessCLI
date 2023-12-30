#ifndef COMMAND_FACTORY_H
#define COMMAND_FACTORY_H

#include <vector>
#include <unordered_map>

#include "UnkownCommandException.h"
#include "ExceededMaxArgumentsException.h"

#include "ExitCommand.h"
#include "HelpCommand.h"
#include "ClearCommand.h"
#include "QuitCommand.h"
#include "CreateCommand.h"
#include "ShowCommand.h"
#include "MoveCommand.h"
#include "FenCommand.h"
#include "HistoryCommand.h"


class ICommand;

#define CREATE_COMMAND_OBJECT(objType) args.size() <= objType::maxArg ? \
	std::unique_ptr<ICommand>(std::make_unique<objType>(args)) : throw ExceededMaxArgumentsException(args.size(), objType::maxArg)

// pointer to a function that returns an ICommand object from a vector of strings
using CommandCreatorFunction = std::unique_ptr<ICommand>(*) (std::vector<std::string>);


class CommandFactory
{
public:
	static std::unique_ptr<ICommand> createCommand(std::string cmdName, std::vector<std::string> args);
};

#endif