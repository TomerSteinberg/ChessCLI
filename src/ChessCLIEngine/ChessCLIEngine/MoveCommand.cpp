#include "MoveCommand.h"

MoveCommand::MoveCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int MoveCommand::maxArg = 1;

void MoveCommand::execute(Context& ctx)
{
	if(!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
	if(this->m_args.size() != 1)
	{	throw InvalidArgumentException("Missing Argument"); }
	if (this->m_args[0] == "0-0" || this->m_args[0] == "0-0-0")
	{
		// castling
		ctx.getCurrGame()->move(this->m_args[0] == "0-0-0", this->m_args[0]);
		std::cout << "Played " + this->m_args[0] << std::endl;
		return;
	}
	if (!std::regex_match(this->m_args[0], std::regex(MOVE_REGEX)))
	{
		throw InvalidArgumentException("Incorrect Format. <usage> move <move notation>. Example: 'move e2e4'");
	}

	int promotionPiece = NO_PROMOTION;
	// converting notation string to square integers
	int startSquare = (this->m_args[0][0] - 97) + (8 - (this->m_args[0][1] - '0')) * 8;
	int endSquare = (this->m_args[0][2] - 97) + (8 - (this->m_args[0][3] - '0')) * 8;
	const std::unordered_map<char, int> promotionMap = { {'q', queen},
		{'b', bishop}, {'r', rook}, {'n', knight}};

	if (this->m_args[0].size() == PROMOTION_LENGTH)
	{
		promotionPiece = promotionMap.at(this->m_args[0][4]);
	}

	ctx.getCurrGame()->move(startSquare, endSquare, promotionPiece, this->m_args[0]);
}	
