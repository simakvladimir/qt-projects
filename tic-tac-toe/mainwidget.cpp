#include <QDeclarativeItem>
#include <QGLWidget>
#include <QGLFormat>
#include <QUrl>
#include <QTimer>
#include <QApplication>
#include <QDeclarativeEngine>

#include "mainwidget.h"

QString filename(contentPath + "MainView.qml");

MainWidget::MainWidget(QWidget *parent)
    : QDeclarativeView(parent)
{
    setResizeMode(QDeclarativeView::SizeRootObjectToView);

    // Register Tile to be available in QML
//    qmlRegisterType<Cell>("gameCore", 1, 0, "Cell");

    // Setup context
    m_context = rootContext();
    m_context->setContextProperty("mainWidget", this);
    m_context->setContextProperty("game", &m_game);

    // Set view optimizations not already done for QDeclarativeView
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);

    // Make QDeclarativeView use OpenGL backend
    QGLWidget *glWidget = new QGLWidget(this);
    setViewport(glWidget);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    // Open root QML file
    setSource(QUrl(filename));
}

MainWidget::~MainWidget()
{
    qDebug() << "~MainWidget";
}



void MainWidget::minimizeWindow()
{
    setWindowState(Qt::WindowMinimized);

}

void MainWidget::exitApplication()
{
    QApplication::quit();
}

void MainWidget::closeEvent(QCloseEvent *ev)
{
    qDebug() << "closeEvent";
    m_game.setGameOn(true);
    m_game.cleanup();
}

