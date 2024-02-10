#include "MoveSearch.h"


std::unordered_map<u64, std::pair<double,int>> transpositionTable;


/*
* Minimax algorithm with chess board
* input: board position, is maximizing or minimizing, depth of search
* output: Score of best outcome
*/
double MoveSearch::minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth, double alpha, double beta)
{
    if (position->isMate(isMaximizingPlayer))
    {
        return isMaximizingPlayer ? MIN_INFINITY - (depth * 0.01) : MAX_INFINITY + (depth * 0.01);
    }
    if (position->isStale(isMaximizingPlayer))
    {
        return EQUAL;
    }
    if (depth == 0)
    {
        return position->evaluate();
    }
    std::deque<Move> moves = position->getMoveList();
    double bestScore = isMaximizingPlayer ? MIN_INFINITY : MAX_INFINITY;

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
        double score = 0;

        u64 zobristHash = afterMove->getZobristHash();
        if (transpositionTable.find(zobristHash) != transpositionTable.end() && transpositionTable[zobristHash].second >= (depth - 1))
        {
            score = transpositionTable[zobristHash].first;
        }
        else
        {
            score = minimax(afterMove, !isMaximizingPlayer, depth - 1, alpha, beta);
            transpositionTable.insert({ zobristHash, {score, depth-1} });
        }
        if (isMaximizingPlayer)
        {
            bestScore = std::max(bestScore, score);
            alpha = std::max(alpha, bestScore);
        }
        else
        {
            bestScore = std::min(bestScore, score);
            beta = std::min(bestScore, beta);
        }
        if (beta <= alpha)
        {
            break;
        }
    }
    return bestScore;
}
