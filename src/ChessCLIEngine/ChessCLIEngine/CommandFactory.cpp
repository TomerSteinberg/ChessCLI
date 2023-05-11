#include "CommandFactory.h"


// pointer to a function that returns an ICommand object from a vector of strings
using CommandCreatorFunction = std::unique_ptr<ICommand> (*) (std::vector<std::string>);

std::unordered_map<std::string, CommandCreatorFunction> CommandCreator = {
	{"help", [](std::vector<std::string> args) {return std::unique_ptr<ICommand>(std::make_unique<HelpCommand>(args)); }},
	{"clear", [](std::vector<std::string> args) {return std::unique_ptr<ICommand>(std::make_unique<ClearCommand>(args)); }},
	{"quit", [](std::vector<std::string> args) {return std::unique_ptr<ICommand>(std::make_unique<QuitCommand>(args)); }}
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
