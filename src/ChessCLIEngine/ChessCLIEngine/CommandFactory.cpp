#include "CommandFactory.h"


std::unordered_map<std::string, CommandCreatorFunction> CommandCreator = {
	{"help",CREATE_COMMAND_OBJECT_LAMBDA(HelpCommand) },
	{"clear",CREATE_COMMAND_OBJECT_LAMBDA(ClearCommand) },
	{"quit", CREATE_COMMAND_OBJECT_LAMBDA(QuitCommand) },
	{"create", CREATE_COMMAND_OBJECT_LAMBDA(CreateCommand) },
	{"show", CREATE_COMMAND_OBJECT_LAMBDA(ShowCommand) },
	{"exit", CREATE_COMMAND_OBJECT_LAMBDA(ExitCommand) },
	{"move", CREATE_COMMAND_OBJECT_LAMBDA(MoveCommand) },
	{"fen", CREATE_COMMAND_OBJECT_LAMBDA(FenCommand) },
	{"history", CREATE_COMMAND_OBJECT_LAMBDA(HistoryCommand) },
	{"position", CREATE_COMMAND_OBJECT_LAMBDA(PositionCommand) },
	{"truncate", CREATE_COMMAND_OBJECT_LAMBDA(TruncateCommand) },
	{"back", CREATE_COMMAND_OBJECT_LAMBDA(BackCommand) },
	{"next", CREATE_COMMAND_OBJECT_LAMBDA(NextCommand) },
	{"options", CREATE_COMMAND_OBJECT_LAMBDA(OptionsCommand) },
	{"dump", CREATE_COMMAND_OBJECT_LAMBDA(DumpCommand) }
};


/*
* Function for creating the appropriate command object based on it's name
* input: Command name (string), Command arguments (vector<string>)
* output: Pointer to Command object
*/
std::unique_ptr<ICommand> CommandFactory::createCommand(std::string cmdName, std::vector<std::string> args)
{
	if (CommandCreator.find(cmdName) != CommandCreator.end())	
	{
		return CommandCreator[cmdName](args);
	}
	else
	{
		throw UnkownCommandException(cmdName);
	}
}
