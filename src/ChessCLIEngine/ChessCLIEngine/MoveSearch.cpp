#include "MoveSearch.h"


std::unordered_map<u64, std::pair<int, int>> MoveSearch::transpositionTable;
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
        return isMaximizingPlayer ? (MIN_INFINITY - depth) : (MAX_INFINITY + depth);
    }
    if (position->isStale(isMaximizingPlayer))
    {
        return EQUAL;
    }
    if (depth == 0)
    {
        return position->evaluate();
    }
    const auto moves = position->getMoveList();
    int bestScore = isMaximizingPlayer ? ALPHA_START : BETA_START;

    for (int i = 0; i < moves.size(); i++)
    {
        for (int j = 0; j < moves[i].size(); j++)
        {
            if (moves[i][j].from == moves[i][j].to && !moves[i][j].castle)
            {
                break;
            }

            std::shared_ptr<BitBoard> afterMove;
            if (!moves[i][j].castle)
            {
                afterMove = position->move(
                    BitBoard::getLsbIndex(moves[i][j].from),
                    BitBoard::getLsbIndex(moves[i][j].to),
                    moves[i][j].promotion);
            }
            else
            {
                afterMove = position->castleMove(moves[i][j].isLong);
            }
            int score = 0;
            if ((depth - 1) != 0)
            {
                const u64 zobristHash = afterMove->getZobristHash();
                if (transpositionTable[zobristHash].second != -1 && transpositionTable[zobristHash].second >= (depth - 1))
                {
                    score = transpositionTable[zobristHash].first;
                }
                else
                {
                    score = minimax(afterMove, !isMaximizingPlayer, depth - 1, alpha, beta);
                    transpositionTable[zobristHash] = { score, depth - 1 };
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
            return position->getMoveListLength();
        }

        auto moves = position->getMoveList();
        for (int i = 0; i < moves.size(); i++)
        {
            for (int j = 0; j < moves[i].size(); j++)
            {
                if (moves[i][j].from == moves[i][j].to && !moves[i][j].castle)
                {
                    break;
                }
                if (moves[i][j].castle)
                {
                    nodes += perft(position->castleMove(moves[i][j].isLong), depth - 1);
                }
                else
                {
                    nodes += perft(position->move(BitBoard::getLsbIndex(moves[i][j].from), BitBoard::getLsbIndex(moves[i][j].to), moves[i][j].promotion), depth - 1);
                }
            }
        }
           
        return nodes;
}
