#include "controller.h"

Controller::Controller(QObject *parent, MainWindow *window) :
    QObject(parent),
    view(window),
    model(new Model),
    thread(new QThread(this))
{
    createConnections();
    tuneThread();

    initModel();
}

Controller::~Controller()
{
   thread->quit();
   thread->wait();

   delete model;
   delete thread;

   qDebug() << "ctrl dest";
}

void Controller::tuneThread()
{
    model->moveToThread(thread);
    thread->start();
}

void Controller::createConnections()
{
    connect(view, SIGNAL(signalFileName(QString)),model, SLOT(slotReadFile(QString)));
    connect(view, SIGNAL(signalStart(int,int)), model, SLOT(slotProcess(int,int)));
    connect(view, SIGNAL(signalDeviceChanged(int)), model, SLOT(slotInit(int)));

    connect(model, SIGNAL(signalReadFileFinished(int,QString)), this, SLOT(slotReadFileFinished(int,QString)));
    connect(model, SIGNAL(signalProcessFinished(int,QString)), this, SLOT(slotProcessFinished(int,QString)));
    connect(model, SIGNAL(signalInitFinished(int,QString)), this, SLOT(slotInitFinished(int,QString)));

    connect(model, SIGNAL(signalDataUpdated(int,int)), this, SLOT(slotModelDataUpdated(int,int)));

    connect(model, SIGNAL(signalReadProgress(int)), view, SLOT(setProgressBar(int)));
    connect(model, SIGNAL(signalProcessProgress(int)), view, SLOT(setProgressBar(int)));

    connect(this, SIGNAL(signalInitModel(int)), model, SLOT(slotInit(int)));
}

void Controller::initModel()
{
    emit signalInitModel(view->getCurrentDev());
}



void Controller::slotReadFileFinished(int code, QString str)
{
    view->setStatusDescription(str);
    view->unblockWidgets();
}

void Controller::slotProcessFinished(int code, QString str)
{
    view->setStatusDescription(str);
    view->setTimeDuration(model->getTimeDuration());
}

void Controller::slotInitFinished(int code, QString str)
{
    view->setStatusDescription(str);
    view->setDevDesc(model->getDeviceInfo());
}

void Controller::slotModelDataUpdated(int Nd, int Md)
{
    double *x,*y,*z;
    model->getModelData(&x,&y,&z);
    view->drawPlot(x,y,z,Nd,Md,model->getFetchFreq(),model->getSamples());

}
