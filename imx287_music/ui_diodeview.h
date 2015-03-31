/********************************************************************************
** Form generated from reading UI file 'diodeview.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIODEVIEW_H
#define UI_DIODEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DiodeView
{
public:
    QVBoxLayout *verticalLayout_2;
    QGridLayout *speedLayout;
    QComboBox *speed_value;
    QLabel *label_5;
    QLabel *label_port;
    QComboBox *com_number;
    QPushButton *open_com;
    QPushButton *set_speed;
    QLabel *ind_open;
    QLabel *ind_connect;
    QFrame *line;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayoutGrad;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *color_panel;
    QComboBox *sound_devices;
    QCheckBox *capture_sound;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QVBoxLayout *eq_layot;

    void setupUi(QWidget *DiodeView)
    {
        if (DiodeView->objectName().isEmpty())
            DiodeView->setObjectName(QStringLiteral("DiodeView"));
        DiodeView->resize(480, 284);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DiodeView->sizePolicy().hasHeightForWidth());
        DiodeView->setSizePolicy(sizePolicy);
        DiodeView->setMinimumSize(QSize(480, 0));
        verticalLayout_2 = new QVBoxLayout(DiodeView);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        speedLayout = new QGridLayout();
        speedLayout->setObjectName(QStringLiteral("speedLayout"));
        speed_value = new QComboBox(DiodeView);
        speed_value->setObjectName(QStringLiteral("speed_value"));
        speed_value->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(speed_value->sizePolicy().hasHeightForWidth());
        speed_value->setSizePolicy(sizePolicy1);

        speedLayout->addWidget(speed_value, 1, 3, 1, 1);

        label_5 = new QLabel(DiodeView);
        label_5->setObjectName(QStringLiteral("label_5"));

        speedLayout->addWidget(label_5, 1, 2, 1, 1);

        label_port = new QLabel(DiodeView);
        label_port->setObjectName(QStringLiteral("label_port"));

        speedLayout->addWidget(label_port, 1, 0, 1, 1);

        com_number = new QComboBox(DiodeView);
        com_number->setObjectName(QStringLiteral("com_number"));

        speedLayout->addWidget(com_number, 1, 1, 1, 1);

        open_com = new QPushButton(DiodeView);
        open_com->setObjectName(QStringLiteral("open_com"));

        speedLayout->addWidget(open_com, 2, 4, 1, 1);

        set_speed = new QPushButton(DiodeView);
        set_speed->setObjectName(QStringLiteral("set_speed"));

        speedLayout->addWidget(set_speed, 1, 4, 1, 1);

        ind_open = new QLabel(DiodeView);
        ind_open->setObjectName(QStringLiteral("ind_open"));
        ind_open->setMaximumSize(QSize(15, 15));
        ind_open->setStyleSheet(QStringLiteral("border-radius: 7px; background-color: red;"));

        speedLayout->addWidget(ind_open, 2, 6, 1, 1);

        ind_connect = new QLabel(DiodeView);
        ind_connect->setObjectName(QStringLiteral("ind_connect"));
        ind_connect->setMaximumSize(QSize(15, 15));
        ind_connect->setStyleSheet(QStringLiteral("border-radius: 7px; background-color: red;"));
        ind_connect->setTextFormat(Qt::AutoText);

        speedLayout->addWidget(ind_connect, 1, 6, 1, 1);


        verticalLayout_2->addLayout(speedLayout);

        line = new QFrame(DiodeView);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        widget = new QWidget(DiodeView);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy1.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy1);
        widget->setMinimumSize(QSize(0, 210));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayoutGrad = new QGridLayout();
        gridLayoutGrad->setObjectName(QStringLiteral("gridLayoutGrad"));
        gridLayoutGrad->setSizeConstraint(QLayout::SetMaximumSize);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayoutGrad->addItem(horizontalSpacer, 1, 2, 1, 1);

        color_panel = new QHBoxLayout();
        color_panel->setObjectName(QStringLiteral("color_panel"));

        gridLayoutGrad->addLayout(color_panel, 2, 4, 1, 1);

        sound_devices = new QComboBox(widget);
        sound_devices->setObjectName(QStringLiteral("sound_devices"));

        gridLayoutGrad->addWidget(sound_devices, 2, 0, 1, 1);

        capture_sound = new QCheckBox(widget);
        capture_sound->setObjectName(QStringLiteral("capture_sound"));

        gridLayoutGrad->addWidget(capture_sound, 2, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 60, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayoutGrad->addItem(verticalSpacer, 2, 3, 1, 1);


        verticalLayout->addLayout(gridLayoutGrad);


        verticalLayout_2->addWidget(widget);

        line_2 = new QFrame(DiodeView);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        eq_layot = new QVBoxLayout();
        eq_layot->setObjectName(QStringLiteral("eq_layot"));

        verticalLayout_2->addLayout(eq_layot);


        retranslateUi(DiodeView);

        QMetaObject::connectSlotsByName(DiodeView);
    } // setupUi

    void retranslateUi(QWidget *DiodeView)
    {
        DiodeView->setWindowTitle(QApplication::translate("DiodeView", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \321\201\320\262\320\265\321\202\320\276\320\274\321\203\320\267\321\213\320\272\320\276\320\271", 0));
        speed_value->clear();
        speed_value->insertItems(0, QStringList()
         << QApplication::translate("DiodeView", "9600", 0)
         << QApplication::translate("DiodeView", "115200", 0)
        );
        label_5->setText(QApplication::translate("DiodeView", "\320\241\320\272\320\276\321\200\320\276\321\201\321\202\321\214", 0));
        label_port->setText(QApplication::translate("DiodeView", "\320\237\320\276\321\200\321\202", 0));
        open_com->setText(QApplication::translate("DiodeView", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214 \320\277\320\276\321\200\321\202", 0));
        set_speed->setText(QApplication::translate("DiodeView", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\272\320\276\321\200\320\276\321\201\321\202\321\214", 0));
        ind_open->setText(QString());
        ind_connect->setText(QString());
        capture_sound->setText(QApplication::translate("DiodeView", "\320\227\320\260\321\205\320\262\320\260\321\202", 0));
    } // retranslateUi

};

namespace Ui {
    class DiodeView: public Ui_DiodeView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIODEVIEW_H
