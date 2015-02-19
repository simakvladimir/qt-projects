#include "ai.h"
#include "board.h"
#include "solver.h"
#include "game.h"

AI::AI(int id, Board *board,  Game *game, QObject *parent) :
    IPlayer(id, board, game, parent),
    m_difficulty(1)
{
}

void AI::step()
{
    Solver solver;

    Move bestMove(0,0);
    int  minScore = INT_MAX;

    solver.setDepth(difficulty());

    foreach (Move move, board()->availableMoves()) {

        int score = solver.minmax(board(), *this, *opponent(), 0);
        if (score < minScore){
            move     = bestMove;
            minScore = score;
        }

    }

    board()->doMove(bestMove, *this);
}


