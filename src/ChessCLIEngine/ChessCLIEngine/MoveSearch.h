#pragma once
#include <memory>
#include "BitBoard.h"
#include <string>
#include <unordered_map>
#include "Game.h"

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define ALPHA_START MIN_INFINITY * 2
#define BETA_START MAX_INFINITY * 2
#define EQUAL 0


class MoveSearch
{
public:
	static int nodes;
	static std::unordered_map<u64, std::pair<int, int>> transpositionTable;
	static int minimax(const std::shared_ptr<BitBoard> position, const bool isMaximizingPlayer, const unsigned int depth, int alpha=ALPHA_START, int beta=BETA_START);
	static int perft(std::shared_ptr<BitBoard> position, const unsigned int depth);
};

