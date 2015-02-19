#include "player.h"
#include "game.h"

#include <QApplication>
#include <QEvent>
#include <QDebug>

Player::Player(int id, Board *board, Game *game,
               QObject *parent) :
    IPlayer(id, board, game, parent)
{
    connect(game, SIGNAL(entered(int)), this, SLOT(receiveIndex(int)));
}

Player::~Player()
{
    m_loop.quit();
}

void Player::step()
{
    m_loop.exec();
}


void Player::receiveIndex(int index)
{
    qDebug() << "receiveIndex";
    m_loop.quit();
    board()->setByIndex(index, *this);
}

bool Player::event(QEvent *event)
{
qDebug() << event->type();
}

//bool Player::event(QEvent *event)
//{
//    qDebug() << event->type();
//}
