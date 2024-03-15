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
		<< "help\t\t\tList of commands\n" 
		<< "clear\t\t\tClear console\n" 
		<< "create  [FEN|None]\tCreate game instance\n"
		<< "move  [Notation]\tMake move\n"
		<< "show  [-u|--unicode]\tShows position\n"
		<< "dump  [-l] [-b] [-h]\tDump bitboard\n"
		<< "fen  [-a]\t\tShow FEN\n"
		<< "options\t\t\tPossible moves\n"
		<< "position  [Index]\tGo to position\n"
		<< "back\t\t\tGo to previous position\n"
		<< "next\t\t\tGo to next position\n"
		<< "truncate\t\tCut moves ahead of position\n"
		<< "history\t\t\tGame move history\n"
		<< "exit\t\t\tExit game\n"
		<< "evaluate  [FEN|None]\tEvaluate current position\n"
		<< "analyze  [FEN|None]\tEvaluate Options\n"
		<< "continue  [-r]\t\tPlay computer move\n"
		<< "perft  [depth] [-r]\tRun Perft test\n"
		<< "quit\t\t\tClose application\n\n";
}
