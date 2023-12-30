#include "HelpCommand.h"


HelpCommand::HelpCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int HelpCommand::maxArg = 0;

/*
* Help command execute for printing the Help menu
* input: application state context
* output: none
*/
void HelpCommand::execute(Context& ctx) 
{
	std::cout 
		<< "\nhelp - List of commands\n" 
		<< "clear - Clear console\n" 
		<< "quit - Close application\n" 
		<< "create [Starting position FEN string | None = Default starting position] - Create a new game\n"
		<< "evaluate [FEN string | None] - Evaluate a position\n"
		<< "analyze [FEN string | None] [-s] [--switch-turn] [-n] [-r] [--reverse-order] - Evaluate possible continuations\n"
		<< "move [Move notation] - Make a move on a loaded board\n"
		<< "show [-u] [--unicode] - Prints current position in visual format\n"
		<< "fen [-a] [--all-positions] - Show FEN string of a loaded position\n"
		<< "history - Show all moves that have been played in classic notation\n"
		<< "position [Index of position in loaded game] - Goes to a specific position in a loaded game\n"
		<< "back - Goes to the previous position\n"
		<< "next - Goes to the next position\n"
		<< "truncate - Remove all positions ahead of current position in a loaded game\n"
		<< "exit - Exit loaded game\n"
		<< "Continue [-r] [--reverse-order] - Play the move with the highest evaluation on loaded position\n\n";
}
