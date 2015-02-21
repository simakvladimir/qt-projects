#include "ai.h"
#include "board.h"
#include "solver.h"
#include "game.h"

#include <QApplication>
#include <QtConcurrent/QtConcurrent>

AI::AI(int id, Board *board,  Game *game, QObject *parent) :
    IPlayer(id, board, game, parent),
    m_difficulty(3),
    m_cancel(false)
{
}

void AI::step()
{


//    connect(&watcher, SIGNAL(finished()), &m_loop, SLOT(quit()));

    m_future = QtConcurrent::run(this, &AI::run);
    while (m_future.isRunning()) {
        QThread::msleep(500);
        QApplication::processEvents();
    }

}

void AI::cancel()
{
    qDebug() << "[AI::cancel]";
    m_future.cancel();
//    m_future.waitForFinished();
//    m_cancel = false;
}

void AI::run()
{


    Move bestMove(0,0);

    int  minScore = -INT_MAX;


    qDebug() << "Difficult" << difficulty();

    QList<Move> moves = board()->availableMoves();
    if(moves.isEmpty())
        return;

    // Из наихудших исходов выбираем более предпочтительный

    int i;

    #pragma omp parallel for default(none) private(i) shared(moves, minScore, bestMove)
    for (i = 0; i < moves.count(); i++){


        Solver solver;
        Move move = moves[i];
        solver.setDepth(difficulty());

        Board *copy = new Board(board());
        copy->doMove(move, *this);
        int score = solver.minmax(copy, *this, *opponent(), 0);
        if (score > minScore){
            bestMove = move;
            minScore = score;
        }
        delete copy;
//        qDebug() << "AI score:" << score << " x: " << move.x() << " y:" << move.y();

    }




    int index = board()->columns() * bestMove.y() + bestMove.x();
    board()->setByIndex(index, *this);

    qDebug() << "Best Index" << index;
}


