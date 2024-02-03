#include "MoveSearch.h"


/*
* Minimax algorithm with chess board
* input: board position, is maximizing or minimizing, depth of search
* output: Score of best outcome
*/
int MoveSearch::minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth)
{
    if (position->isMate(isMaximizingPlayer))
    {
        return isMaximizingPlayer ? MAX_INFINITY : MIN_INFINITY;
    }
    if (position->isStale(isMaximizingPlayer))
    {
        return EQUAL;
    }
    if (depth == 0)
    {
        return position->evaluate();
    }
    std::vector<Move> moves = position->getMoveList();
    int bestScore = 0;

    for (auto moveIterator = moves.begin(); moveIterator != moves.end(); moveIterator++)
    {
        std::shared_ptr<BitBoard> afterMove;
        try 
        {
            if (!moveIterator->castle)
            {
                    afterMove = position->move(
                    BitBoard::getLsbIndex(moveIterator->from),
                    BitBoard::getLsbIndex(moveIterator->to),
                    moveIterator->promotion);
            }
            else
            {
                afterMove = position->castleMove(moveIterator->isLong);
            }
        }
        catch (...)
        {
            continue;
        }

        int score = minimax(afterMove, !isMaximizingPlayer, depth - 1);
        if (isMaximizingPlayer)
        {
            if (score > bestScore)
            {
                bestScore = score;
            }
        }
        else
        {
            if (score < bestScore)
            {
                bestScore = score;
            }
        }
    }
    return bestScore;
}
