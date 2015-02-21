#ifndef AI_H
#define AI_H

#include <QObject>
#include <QFuture>
#include "iplayer.h"

class AI : public IPlayer
{
    Q_OBJECT
public:
    explicit AI(int id, Board *board, Game *game,
                QObject *parent = 0);

    QString id() const { return "AI"; }
    void step();
    void cancel();

    void setDifficulty(int level) { m_difficulty = level; }
    int difficulty() const        { return m_difficulty;  }
signals:

public slots:

private:
    void run();

    bool m_cancel;
    int m_difficulty;
    QFuture<void> m_future;


};

#endif // AI_H
