#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPointer>

#include "board.h"
#include "iplayer.h"
#include "ai.h"
#include "player.h"

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = 0);
    ~Game();

    Q_PROPERTY(bool gameOn READ gameOn WRITE setGameOn NOTIFY gameOnChanged)
    bool gameOn() const {return m_gameOn;}
    void setGameOn(bool on) {if(on==m_gameOn) return; m_gameOn = on; emit gameOnChanged();}

    Q_PROPERTY(int enteredIndex READ enteredIndex WRITE setEnteredIndex NOTIFY entered)
    int enteredIndex() const        { return m_index; }
    void setEnteredIndex(int index) { if(m_index==index) return; m_index = index; emit entered(index);}

    Q_PROPERTY(QString activePlayer READ activePlayer WRITE setActivePlayer NOTIFY activePlayerChanged )
    QString activePlayer() const         {return m_activePlayer;}
    void setActivePlayer(QString player) { if (m_activePlayer == player) return; m_activePlayer = player; emit activePlayerChanged(); }

    void cleanup();

signals:
    void activePlayerChanged();
    void entered(int index);
    void gameOnChanged();
    void dataChanged();

public slots:
    void start(QString pl1, QString pl2, int size);
    int cellValueByIndex(int index){ return  m_board ? m_board->valueByIndex(index) : 0; }

private:
    bool isFinished();

    int  m_index;
    bool m_gameOn;

    QString m_activePlayer;

    QPointer<Board> m_board;
    QPointer<IPlayer> m_playerOne;
    QPointer<IPlayer> m_playerTwo;

};

#endif // GAME_H
