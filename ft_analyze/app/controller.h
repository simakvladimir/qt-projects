#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "mainwindow.h"
#include "model.h"

#include <QObject>
#
#include <QDebug>

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0, MainWindow *window = 0);
    ~Controller();

    void setModel();
    void tuneThread();
    void createConnections();
signals:

public slots:
    void slotReadFileFinished(int code, QString str);
    void slotProcessFinished(int code, QString str);

    void slotModelDataUpdated(int Nd, int Md);

private:
    MainWindow *view;
    Model      *model;
    QThread    *thread;
};

#endif // CONTROLLER_H
