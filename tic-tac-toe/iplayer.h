#ifndef IPLAYER_H
#define IPLAYER_H

#include <QObject>
#include <QDebug>
class Board;
class Game;

#define PLAYER_MAX_COUNT 2

class IPlayer : public QObject
{
    Q_OBJECT
public:
    explicit IPlayer(int side, Board *board, Game *game,
                     QObject *parent = 0) :
        QObject(parent),
        m_side(side),
        m_game(game),
        m_board(board),
        m_opponent(0)
    {
    }

    int side() const { return m_side; }

    virtual QString id() const = 0;
    virtual void step() {}

    void setOpponent(IPlayer *player)  { m_opponent = player; }
    IPlayer *opponent()                { return m_opponent;   }
signals:

public slots:

protected:
    Game  *game()      { return m_game;     }
    Board *board()     { return m_board;    }

private:
    int m_side;
    Game    *m_game;
    Board   *m_board;
    IPlayer *m_opponent;
};

#endif // IPLAYER_H
