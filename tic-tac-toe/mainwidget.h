#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include "game.h"

const QString contentPath = "qml/";

class MainWidget : public QDeclarativeView
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent=0);
    ~MainWidget();

public slots:
    void minimizeWindow();
    void exitApplication();

protected:
    void closeEvent(QCloseEvent *ev);

private:
    QDeclarativeContext *m_context;
    Game m_game;
};

#endif // MAINWIDGET_H
