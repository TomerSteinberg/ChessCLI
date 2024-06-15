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
#include "PositionCommand.h"
#include "TruncateCommand.h"
#include "BackCommand.h"
#include "NextCommand.h"
#include "OptionsCommand.h"
#include "DumpCommand.h"
#include "EvaluateCommand.h"
#include "ContinueCommand.h"
#include "AnalyzeCommand.h"
#include "PerftCommand.h"
#include "ServeCommand.h"

class ICommand;

#define CREATE_COMMAND_OBJECT(objType) (int)args.size() <= objType::maxArg ? \
	std::unique_ptr<ICommand>(std::make_unique<objType>(args)) : throw ExceededMaxArgumentsException(args.size(), objType::maxArg)

#define CREATE_COMMAND_OBJECT_LAMBDA(objType) [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(objType); }
// pointer to a function that returns an ICommand object from a vector of strings
using CommandCreatorFunction = std::unique_ptr<ICommand>(*) (std::vector<std::string>);


class CommandFactory
{
public:
	static std::unique_ptr<ICommand> createCommand(std::string cmdName, std::vector<std::string> args);
};

#endif