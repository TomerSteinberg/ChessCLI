#include "CommandFactory.h"


std::unordered_map<std::string, CommandCreatorFunction> CommandCreator = {
	{"help", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(HelpCommand); }},
	{"clear", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(ClearCommand); }},
	{"quit", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(QuitCommand); }},
	{"create", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(CreateCommand); }},
	{"show", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(ShowCommand); }},
	{"exit", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(ExitCommand); }},
	{"move", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(MoveCommand); }},
	{"fen", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(FenCommand); }},
	{"history", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(HistoryCommand); }},
	{"position", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(PositionCommand); }},
	{"truncate", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(TruncateCommand); }},
	{"back", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(BackCommand); }},
	{"next", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(NextCommand); }}
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
