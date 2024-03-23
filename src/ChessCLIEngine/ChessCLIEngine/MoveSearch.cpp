#include "MoveSearch.h"


std::pair<int, int> MoveSearch::transpositionTable[TRANSPOTION_TABLE_SIZE] = { {0, -1} };
int MoveSearch::nodes = 0;


/*
* Minimax algorithm with chess board
* input: board position, is maximizing or minimizing, depth of search
* output: Score of best outcome
*/
int MoveSearch::minimax(const std::shared_ptr<BitBoard> position, const bool isMaximizingPlayer, const unsigned int depth, int alpha, int beta)
{
    nodes++;
    if (position->isMate(isMaximizingPlayer))
    {
        return isMaximizingPlayer ? MIN_INFINITY - depth : MAX_INFINITY + depth;
    }
    if (position->isStale(isMaximizingPlayer))
    {
        return EQUAL;
    }
    if (depth == 0)
    {
        return position->evaluate();
    }
    const std::deque<Move> moves = position->getMoveList();
    int bestScore = isMaximizingPlayer ? MIN_INFINITY : MAX_INFINITY;

    for (auto moveIterator = moves.begin(); moveIterator != moves.end(); moveIterator++)
    {
        std::shared_ptr<BitBoard> afterMove;
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
        int score = 0;

        if ((depth - 1) != 0)
        {
            const u64 zobristHash = afterMove->getZobristHash();
            if (transpositionTable[zobristHash % TRANSPOTION_TABLE_SIZE].second != -1 && transpositionTable[zobristHash % TRANSPOTION_TABLE_SIZE].second >= (depth - 1))
            {
                score = transpositionTable[zobristHash % TRANSPOTION_TABLE_SIZE].first;
            }
            else
            {
                score = minimax(afterMove, !isMaximizingPlayer, depth-1, alpha, beta);
                transpositionTable[zobristHash % TRANSPOTION_TABLE_SIZE] = { score, depth -1 };
            }
        }
        else
        {
            score = minimax(afterMove, !isMaximizingPlayer, depth - 1, alpha, beta);
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


/*
* Runs a perft nps test 
* input: position and depth of test
* output: number of nodes gone over in the test
*/
int MoveSearch::perft(std::shared_ptr<BitBoard> position, const unsigned int depth)
{
        int32_t nodes = 0;
        if (depth == 0)
        {
            return position->getMoveList().size();
        }

        std::deque<Move> moves = position->getMoveList();
        for (auto move = moves.begin(); move != moves.end(); move++)
        {
            if (move->castle)
            {
                //int nodes_test = perft(position->castleMove(move->isLong), depth - 1);
                nodes +=  perft(position->castleMove(move->isLong), depth - 1);
                //if (depth == 1)
                //{
                //    std::cout << Game::notationFromMove(*move) << ": " << nodes_test << std::endl;
                //}
            }
            else
            {
                //int nodes_test = perft(position->move(BitBoard::getLsbIndex(move->from), BitBoard::getLsbIndex(move->to), move->promotion), depth - 1);
                nodes += perft(position->move(BitBoard::getLsbIndex(move->from), BitBoard::getLsbIndex(move->to), move->promotion), depth - 1);
                //if (depth == 1)
                //{
                //    std::cout << Game::notationFromMove(*move) << ": " << nodes_test << std::endl;
                //}
            }
        }
        return nodes;
}
