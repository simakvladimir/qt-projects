#include "solver.h"

Solver::Solver() :
    m_depth(1)
{
}

int Solver::minmax(Board *board,
                   const IPlayer &hero,
                   const IPlayer &opponent,
                   int depth)
{
    if (isTerminal(board, depth)){
        int rating = heuristic(board, hero, opponent);
        return depth % PLAYER_MAX_COUNT ? rating : -rating;
    }
    int score = INT_MAX;
    foreach (Board *child, childrens(board, hero)) {
        int s = minmax(child, opponent, hero, depth + 1);
        if (s < score){
            score = s;
        }
        delete child;
    }
    return score;
}

int Solver::heuristic(Board *board, const IPlayer &hero, const IPlayer &opponent)
{
    if (board->isWin(hero))
        return 5;

    if (board->isWin(opponent))
        return -5;

    if (board->isDraw())
        return 2;

    return 0;
}

QList<Board*> Solver::childrens(Board *board, const IPlayer &player)
{
    QList<Board*> childList;
    foreach (Move move, board->availableMoves()) {
        Board *child = new Board(board);
        child->doMove(move, player);
        childList.append(child);
    }
    return childList;
}

bool Solver::isTerminal(Board *board, int curDepth) const
{
    if (curDepth > depth())
        return true;

    return false;
}
