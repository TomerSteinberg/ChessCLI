#include "HelpCommand.h"


HelpCommand::HelpCommand(std::vector<std::string> args) : ICommand(args)
{
}


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
		<< "load [PGN directory] - Create game representation from PGN\n"
		<< "create [Starting position FEN string | None = Default starting position] - Create a new game\n"
		<< "evaluate [FEN string | PGN directory | None] - Evaluate a position\n"
		<< "analyze [FEN string | PGN directory | None] [-s] [--switch-turn] [-n] [-r] [--reverse-order] - Evaluate possible continuations\n"
		<< "move [Move notation] - Make a move on a loaded board\n"
		<< "show [-a] [--all-positions] [-u] [--unicode] - Prints current position in visual format\n"
		<< "fen [-a] [--all-positions] - Show FEN string of a loaded position\n"
		<< "history - Show all moves that have been played in classic notation\n"
		<< "position [Index of position in loaded game] - Goes to a specific position in a loaded game\n"
		<< "truncate - Remove all positions ahead of current position in a loaded game\n"
		<< "save [Directory | None = current directory] - Save loaded game to PGN\n"
		<< "Exit [Directory | None = current directory] [-d] [--no-save] - Exit loaded game\n"
		<< "Continue [-r] [--reverse-order] - Play the move with the highest evaluation on loaded position\n\n";
}
