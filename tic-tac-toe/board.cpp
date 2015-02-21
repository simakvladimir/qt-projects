#include "board.h"

#include <QDebug>

Board::Board(int row, int column, QObject *parent) :
    QObject(parent),
    m_rows(row),
    m_columns(column)
{
    Cell *cell;
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++){
            cell =  new Cell(j, i);
            connect(cell, SIGNAL(valueChanged()), this, SIGNAL(changed()));
            m_board << cell;

        }
}

Board::Board(Board *board)
{
    Cell *cell;

    m_rows = board->rows();
    m_columns = board->columns();

    for (int i = 0; i < board->rows(); i++)
        for (int j = 0; j < board->columns(); j++){
            int value = board->cell(i,j)->value();
            cell = new Cell(i, j, value);
            connect(cell, SIGNAL(valueChanged()), this, SIGNAL(changed()));
            m_board << cell;
        }
}

Board::~Board()
{
//    qDebug() << "~Board";
    qDeleteAll(m_board);
}

void Board::doMove(Move move, const IPlayer &player)
{
    int x = move.x();
    int y = move.y();
    Cell *to_cell = cell(x,y);
    if (to_cell)
        to_cell->setValue(player.side());
}

QList<Move> Board::availableMoves() const
{
    QList<Move> moves;
    foreach (Cell *cell, m_board) {
        if (cell->isEmpty())
            moves << Move(cell->x(), cell->y());
    }
    return moves;
}

void Board::setByIndex(int index, const IPlayer &player)
{
    int x, y;
    x = index % columns();
    y = index / rows();

    qDebug() << "[Board::setByIndex]" << x << y;

    cell(x,y)->setValue(player.side());
}

int Board::valueByIndex(int index)
{
    int x, y;
    x = index % columns();
    y = index / rows();

//    qDebug() << "[Board::valueByIndex]" << x << y << index;

    Cell *_cell = cell(x,y);
    return _cell ? _cell->value() : 0;
}

bool Board::isWin(const IPlayer &player)
{
    int count;

    // column
    for (int i = 0; i < columns(); i++){
        count = 0;
        for (int j = 0; j < rows(); j++){
            count = (cell(i,j)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }
    }

    // rows
    for (int i = 0; i < rows(); i++){
        count = 0;
        for (int j = 0; j < columns(); j++){
            count = (cell(j,i)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }
    }

    // diag  \ (1,1; 2,2; 3,3)
    for (int i = -rows(); i < columns(); i++){
        count = 0;
        int x, y;
        for (x = i, y = 0; y < rows() && x < columns(); x++, y++){
            if (x < 0)
                continue;
            count = (cell(x,y)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }

    }

    // diag / (3,1; 2,2; 1,3)
    for (int i = columns() + rows() - 1; i >= 0;  i--){
        count = 0;
        int x, y;
        for (x = i, y = 0; y < rows() && x >= 0; x--, y++){
            if (x >= columns())
                continue;
            count = (cell(x,y)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }

    }

    return false;
}

bool Board::isDraw()
{
    // TODO
    return availableMoves().isEmpty();
}

Cell *Board::cell(int x, int y)
{
    foreach (Cell *cell, m_board) {
        if (cell->x() == x && cell->y() == y)
            return cell;
    }
    return 0;
}

