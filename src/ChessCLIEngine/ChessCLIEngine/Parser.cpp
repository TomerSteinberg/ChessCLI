#include "Parser.h"

/*
* Function for creating a Command object using a command string
* input: command input (string)
* output: pointer to a Command object
*/
std::unique_ptr<ICommand> Parser::parseCommand(std::string cmd)
{
    std::unique_ptr<ICommand> command = nullptr;

    try
    {
        std::vector<std::string> args = Parser::splitBySpace(cmd);
        if (args.size() < 1) { return nullptr; }

        std::string commandName = args[0];
        args.erase(args.begin());
        command = CommandFactory::createCommand(commandName, args);
    }
    catch (std::exception& error)
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
