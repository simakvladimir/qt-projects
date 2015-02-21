#ifndef PLAYER_H
#define PLAYER_H

#include <QEventLoop>
#include "iplayer.h"

class Player : public IPlayer
{
    Q_OBJECT
public:
    explicit Player(int id, Board *board, Game *game,
                    QObject *parent = 0);
    ~Player();
signals:

public slots:
    QString id() const { return "Man"; }
    void step();
    void cancel();

    void receiveIndex(int index);

protected:
    bool event(QEvent *event);

private:
    QEventLoop m_loop;
};

#endif // PLAYER_H
