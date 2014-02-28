#include <QGuiApplication>
#include <QQuickView>
//#include <QQmlEngine>
#include <qqml.h>
#include <QQmlContext>

//#include <QGuiApplication>
////#include "qmlapplicationviewer.h"
//#include <QDeclarativeContext>

#include "thrwrap.h"

int main(int argc, char* argv[])
{
//    qRegisterMetaType<BigUnsigned>("BigUnsigned");
//    qmlRegisterType<ThrWrap>("ModuleName", 1, 0, "TypeName");

//    ThrWrap a;

//    a.set_range( 0, 1000000 );
//    a.set_digit( 6 );
//    a.set_thread_number(1);\
//    a.calculate();


    QGuiApplication app(argc,argv);
    QQuickView view;

    ThrWrap Wrapper;
    view.rootContext()->setContextProperty("Wrapper", &Wrapper);

    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.setSource(QUrl("qrc:/qml/main.qml"));

//    const QString lowerArgument = QString::fromLatin1(argv[1]).toLower();
//    if (lowerArgument == QLatin1String("--fullscreen")) {
//        view.showFullScreen();
//    } else {
//    view.set
    view.setMinimumSize(QSize(300,400));
    view.setMaximumSize(QSize(300,400));

        view.show();
//    }
        return app.exec();
}
