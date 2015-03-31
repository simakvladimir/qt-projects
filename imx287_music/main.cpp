#include <QApplication>
#include <QTextCodec>
#include "diodeview.h"
#include "diodepresenter.h"
#include "gradient.h"
#include "ui_diodeview.h"
#include "buffer/common.h"
/*!
    Устанавливает текстовые кодеки для кодировки \a codecName.
*/

#include "fftwcompute.h"

#include <QAxObject>
#include <QThread>
#include <QDebug>
void initTextCodecs(const char *codecName)
{
    QTextCodec *codec = QTextCodec::codecForName(codecName);
//    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
//    QTextCodec::setCodecForTr(codec);
}
int main(int argc, char *argv[])
{
// QAxObject *word;
    QApplication app(argc, argv);
    qRegisterMetaType<MyArray>("MyArray");

//    QAxObject *word;
//    QAxObject *doc;
//    word = new QAxObject("Word.Application");
//    word->setProperty("DisplayAlerts", false);
//    word->setProperty("Visible", true);
//    doc = word->querySubObject("Documents");
//    doc->dynamicCall("Open(QVariant)", "d:/test.doc");

//    FFTWCompute fftw;
//    fftw.calculate();

    initTextCodecs("UTF-8");


    DiodeView      *view      = new DiodeView();
    DiodePresenter *presenter = new DiodePresenter(view);

    Q_UNUSED(presenter);
    view->show();
qDebug() << view->thread();
    return app.exec();
}

