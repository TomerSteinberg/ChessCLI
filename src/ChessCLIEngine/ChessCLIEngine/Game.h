#ifndef GAME_H
#define GAME_H

#include <list>
#include <string>
#include "BitBoard.h"
#include <regex>
#include <exception>
#include <memory>


#define FEN_REGEX "/(?<PiecePlacement>((?<RankItem>[pnbrqkPNBRQK1-8]{1,8})\\/?){8})\\s+(?<SideToMove>b|w)\\s+(?<Castling>-|K?Q?k?q)\s+(?<EnPassant>-|[a-h][3-6])\\s+(?<HalfMoveClock>\\d+)\\s+(?<FullMoveNumber>\\d+)\\s*$/x"
#define DEFAULT_STARTING_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

class BitBoard;

class Game
{
public:
	Game(std::string fen);
	Game();



private:
	std::list<std::shared_ptr<BitBoard>> m_moves;
	std::shared_ptr<BitBoard> m_currPosition;


};

#endif