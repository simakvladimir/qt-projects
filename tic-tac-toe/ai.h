#ifndef AI_H
#define AI_H

#include <QObject>
#include "iplayer.h"

class AI : public IPlayer
{
    Q_OBJECT
public:
    explicit AI(int id, Board *board, Game *game,
                QObject *parent = 0);

    QString id() const { return "AI"; }
    void step();

    void setDifficulty(int level) { m_difficulty = level; }
    int difficulty() const        { return m_difficulty;  }
signals:

public slots:

private:
    int m_difficulty;

};

#endif // AI_H
