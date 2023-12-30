#include "Parser.h"

/*
* Function for creating a Command object using a command string
* input: command input (string)
* output: pointer to a Command object
*/
std::vector<std::unique_ptr<ICommand>>  Parser::parseCommand(std::string cmd)
{
    std::vector<std::string> unParsedCommands = splitBySemicolon(cmd);
    std::vector<std::unique_ptr<ICommand>> commands;

    for (auto it = unParsedCommands.begin(); it != unParsedCommands.end(); it++)
    {
        try
        {
            std::vector<std::string> args = Parser::splitBySpace(*it);
            if (args.size() < 1) { continue; }
            std::string commandName = args[0];
            args.erase(args.begin());
            commands.push_back(CommandFactory::createCommand(commandName, args));
        }
        catch (std::exception& error)
        {
            std::cout << error.what() << std::endl;
            return {};
        }

    }
    return commands;
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


/*
* Splits cmd by semicolons 
* input: cmd
* output: vector of split commands
*/
std::vector<std::string> Parser::splitBySemicolon(std::string cmd)
{
    int firstPos = 0, lastPos = 0;
    std::string token;
    std::vector<std::string> cmds;

    while ((lastPos = cmd.find(";", firstPos)) != std::string::npos) {
        token = cmd.substr(firstPos, lastPos - firstPos);
        firstPos = lastPos + 1;
        cmds.push_back(token);
    }

    cmds.push_back(cmd.substr(firstPos));
    return cmds;
}
