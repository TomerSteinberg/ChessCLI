#pragma once
#include <memory>
#include "BitBoard.h"
#include <string>
#include <unordered_map>

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define EQUAL 0

class MoveSearch
{
public:
	static double minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth, double alpha=MIN_INFINITY, double beta=MAX_INFINITY);
};

