#ifndef SOLVER_H
#define SOLVER_H

#include <QPair>
#include <QList>
#include "board.h"

class Solver
{
public:
    Solver();

    void setDepth(int value) { m_depth = value; }
    int depth() const        { return m_depth;  }

    int minmax(Board   *board,
               const IPlayer &hero, const IPlayer &opponent,
               int depth);

private:

    int heuristic(Board *board, const IPlayer &hero, const IPlayer &opponent, int depth);
    QList<Board *> childrens(Board *board, const IPlayer &player);

    bool isTerminal(Board *board, const IPlayer &hero,
                    const IPlayer &opponent, int curDepth) const;

    int m_depth;
};

#endif // SOLVER_H
