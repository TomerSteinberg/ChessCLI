#include "CommandFactory.h"


// pointer to a function that returns an ICommand object from a vector of strings
using CreatorFunction = ICommand* (*) (std::vector<std::string>);

std::unordered_map<std::string, CreatorFunction> CommandCreator = {
	{"help", [](std::vector<std::string> args) {return static_cast<ICommand*>(new HelpCommand(args)); }},
	{"clear", [](std::vector<std::string> args) {return static_cast<ICommand*>(new ClearCommand(args)); }},
	{"quit", [](std::vector<std::string> args) {return static_cast<ICommand*>(new QuitCommand(args)); }}
};


/*
* Function for creating the appropriate command object based on it's name
* input: Command name (string), Command arguments (vector<string>)
* output: Pointer to Command object
*/
ICommand* CommandFactory::createCommand(std::string cmdName, std::vector<std::string> args)
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
