#include "Parser.h"

/*
* Function for creating a Command object using a command string
* input: command input (string)
* output: pointer to a Command object
*/
ICommand* Parser::parseCommand(std::string cmd)
{
    ICommand* command = nullptr;
    std::vector<std::string> args = Parser::splitBySpace(cmd);
    std::string commandName = args[0];
    args.erase(args.begin());
    try
    {
        command = CommandFactory::createCommand(commandName, args);
    }
    catch (CommandNotFoundException& error)
    {
        std::cout << error.what();
    }
    return command;
}


/*
* Function for splitting a command by spaces
* input: command input (string)
* output: vector of strings holding the parts of the command
*/
std::vector<std::string> Parser::splitBySpace(std::string cmd)
{
    std::istringstream iss(cmd);
    return std::vector<std::string>(std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>{});
}
