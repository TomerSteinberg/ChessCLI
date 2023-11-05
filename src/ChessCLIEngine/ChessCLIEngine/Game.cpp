#include "Game.h"

Game::Game(std::string fen)
{
	std::cmatch res;
	if (!std::regex_match(fen, std::regex(FEN_REGEX)))
	{
		throw std::exception("Argument Error: Invalid FEN string"); // turn to it's own exception type
	}
	// create BitBoard instance
}

Game::Game()
{
}
