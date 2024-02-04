#include "MoveSearch.h"


std::unordered_map<std::string, int> transpositionTable;

/*
* Minimax algorithm with chess board
* input: board position, is maximizing or minimizing, depth of search
* output: Score of best outcome
*/
int MoveSearch::minimax(std::shared_ptr<BitBoard> position, bool isMaximizingPlayer, unsigned int depth, int alpha, int beta)
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
    std::vector<Move> moves = position->getMoveList();
    int bestScore = isMaximizingPlayer ? MIN_INFINITY : MAX_INFINITY;

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
        int score = 0;
        std::string fen = afterMove->getFen(); // TODO: Improve hash map key 
        if (transpositionTable.find(fen) != transpositionTable.end()) 
        {
            score = transpositionTable[fen];
        }
        else
        {
            score = minimax(afterMove, !isMaximizingPlayer, depth - 1, alpha, beta);
            transpositionTable.insert({ fen, score });
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
