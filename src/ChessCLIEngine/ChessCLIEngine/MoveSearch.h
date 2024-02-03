#pragma once
#include <memory>
#include "BitBoard.h"

#define MAX_INFINITY 1000000
#define MIN_INFINITY -1000000
#define EQUAL 0

class MoveSearch
{
public:
	static int minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth);
};

