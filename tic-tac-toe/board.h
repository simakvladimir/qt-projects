#ifndef BOARD_H
#define BOARD_H

#include <QObject>

#include "iplayer.h"
#include "move.h"
#include "cell.h"

class Board : public QObject
{
    Q_OBJECT
public:

    explicit Board(int rows, int columns, QObject *parent = 0);
    Board(Board *board);
    ~Board();

    int columns() const { return m_columns; }
    int rows() const    { return m_rows;    }

    void doMove(Move move, const IPlayer &player);
    QList<Move> availableMoves() const;

    void setByIndex(int index, const IPlayer &player);
    int valueByIndex(int index);

    bool isWin(const IPlayer &player);
    bool isDraw();

signals:
    void changed();

public slots:

protected:
    Cell *cell(int x, int y);

private:
    int m_rows;
    int m_columns;

    QList<Cell*> m_board;
};

#endif // BOARD_H
