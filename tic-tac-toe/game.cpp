#include "game.h"
#include "cell.h"

#include <QDebug>
#include <QEventLoop>
#include <QTimer>


Game::Game(QObject *parent) :
    QObject(parent),
    m_gameOn(true),
    m_board(new Board(0,0)),
    m_playerOne(0),
    m_playerTwo(0)
{

}

Game::~Game()
{
    qDebug() << "~Game";
//    if (m_playerOne)
//        delete m_playerOne;
//    if (m_playerTwo)
//        delete m_playerTwo;
//    if (m_board)
//        delete m_board;
}

void Game::cleanup()
{
    if (m_playerOne)
        m_playerOne->cancel();
    if (m_playerTwo)
        m_playerTwo->cancel();
}


void Game::start(QString pl1, QString pl2, int size)
{
    setGameOn(false);

    m_board = new Board(size,size);
    connect(m_board, SIGNAL(changed()), this, SIGNAL(dataChanged()));
    emit dataChanged();

    if (pl1 == "cpu"){
        m_playerTwo = new AI(Cell::CELL_TAC, m_board, this);
    } else {
        m_playerOne = new Player(Cell::CELL_TAC, m_board, this);
    }

    if (pl2 == "cpu"){
        m_playerTwo = new AI(Cell::CELL_TIC, m_board, this);
    } else {
        m_playerOne = new Player(Cell::CELL_TIC, m_board, this);
    }

    m_playerOne->setOpponent(m_playerTwo);
    m_playerTwo->setOpponent(m_playerOne);

    while (!isFinished() && !gameOn()) {
        setActivePlayer(m_playerOne->id());
        m_playerOne->step();

        setActivePlayer(m_playerTwo->id());
        m_playerTwo->step();
    }

    cleanup();

    setGameOn(true);
}


bool Game::isFinished()
{
    return m_board->isWin(*m_playerOne) ||
           m_board->isWin(*m_playerTwo) ||
           m_board->isDraw()            ||
           m_board->availableMoves().count() == 0;
}

