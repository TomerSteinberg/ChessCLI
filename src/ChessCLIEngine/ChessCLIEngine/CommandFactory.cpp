#include "CommandFactory.h"


std::unordered_map<std::string, CommandCreatorFunction> CommandCreator = {
	{"help", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(HelpCommand); }},
	{"clear", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(ClearCommand); }},
	{"quit", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(QuitCommand); }},
	{"create", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(CreateCommand); }},
	{"show", [](std::vector<std::string> args) {return CREATE_COMMAND_OBJECT(ShowCommand); }}
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
