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

    m_rows = board->columns();
    m_columns = board->rows();

    for (int i = 0; i < board->columns(); i++)
        for (int j = 0; j < board->rows(); j++){
            cell = new Cell(j, i, board->cell(i,j)->value());
            connect(cell, SIGNAL(valueChanged()), this, SIGNAL(changed()));
            m_board << cell;
        }
}

Board::~Board()
{
    qDebug() << "~Board";
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
    m_board.at(index)->setValue(player.side());
}

int Board::valueByIndex(int index)
{
    if (index < 0 || index >= m_board.count())
        return Cell::CELL_EMPTY;

    return m_board.at(index)->value();
}

bool Board::isWin(const IPlayer &player)
{
    int count;

    // row
    for (int i = 0; i < rows(); i++){
        count = 0;
        for (int j = 0; j < columns(); j++){
            count = (cell(i,j)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }
    }

    // columns
    for (int i = 0; i < columns(); i++){
        count = 0;
        for (int j = 0; j < rows(); j++){
            count = (cell(i,j)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }
    }

    // diag
    for (int i = 0; i < columns(); i++){
        count = 0;
        for (int x = i, y = 0; x  < columns() && y < rows(); x++, y++){
            count = (cell(x,y)->value() == player.side()) ? count + 1 : 0;
            if (count == 3)
                return true;
        }
    }
    for (int j = 0; j < rows(); j++){
        count = 0;
        for (int x = 0, y = j; x < columns() && y < rows(); x++, y++){
            count = (cell(x,y)->value() == player.side()) ? count + 1: 0;
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

