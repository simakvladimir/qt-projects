#include "solver.h"

Solver::Solver() :
    m_depth(3)
{
}

int Solver::minmax(Board *board,
                   const IPlayer &hero,
                   const IPlayer &opponent,
                   int depth)
{
    if (isTerminal(board, hero, opponent, depth)){
        int rating = heuristic(board, hero, opponent, depth);
        return rating;
    }
    int score = INT_MAX;
    foreach (Board *child, childrens(board, opponent)) {
        int s = minmax(child, opponent, hero, depth + 1);
        if (s < score){
            score = s;
        }
        delete child;
    }
    return score;
}

int Solver::heuristic(Board *board, const IPlayer &hero, const IPlayer &opponent, int depth)
{
    int winCoef = m_depth - depth;

    if (board->isWin(hero))
        return (depth % PLAYER_MAX_COUNT == 0) ? 5 * depth : -5 * winCoef;

    if (board->isWin(opponent))
        return (depth % PLAYER_MAX_COUNT == 0) ? -5 * winCoef : 5 * depth;

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

bool Solver::isTerminal(Board *board, const IPlayer &hero, const IPlayer &opponent, int curDepth) const
{
    if (curDepth > depth())
        return true;

    if (board->isWin(hero))
        return true;

    if (board->isWin(opponent))
        return true;

    if (board->isDraw())
        return true;

    return false;
}
