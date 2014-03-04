/********************************************************************************
** Form generated from reading UI file 'settings.ui'
**
** Created by: Qt User Interface Compiler version 5.2.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGS_H
#define UI_SETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_Settings
{
public:
    QGridLayout *gridLayout;
    QLabel *label_4;
    QDialogButtonBox *btnBox;
    QComboBox *cbDevices;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLineEdit *leSrcMac;
    QLabel *label;
    QLineEdit *leDstMac;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *Settings)
    {
        if (Settings->objectName().isEmpty())
            Settings->setObjectName(QStringLiteral("Settings"));
        Settings->resize(419, 240);
        gridLayout = new QGridLayout(Settings);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_4 = new QLabel(Settings);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        btnBox = new QDialogButtonBox(Settings);
        btnBox->setObjectName(QStringLiteral("btnBox"));
        btnBox->setOrientation(Qt::Horizontal);
        btnBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(btnBox, 5, 1, 1, 1);

        cbDevices = new QComboBox(Settings);
        cbDevices->setObjectName(QStringLiteral("cbDevices"));

        gridLayout->addWidget(cbDevices, 3, 1, 1, 1);

        label_2 = new QLabel(Settings);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_3 = new QLabel(Settings);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        leSrcMac = new QLineEdit(Settings);
        leSrcMac->setObjectName(QStringLiteral("leSrcMac"));
        leSrcMac->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(leSrcMac, 2, 1, 1, 1);

        label = new QLabel(Settings);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 1, 1, 1);

        leDstMac = new QLineEdit(Settings);
        leDstMac->setObjectName(QStringLiteral("leDstMac"));
        leDstMac->setMinimumSize(QSize(120, 0));

        gridLayout->addWidget(leDstMac, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);


        retranslateUi(Settings);
        QObject::connect(btnBox, SIGNAL(accepted()), Settings, SLOT(accept()));
        QObject::connect(btnBox, SIGNAL(rejected()), Settings, SLOT(reject()));

        QMetaObject::connectSlotsByName(Settings);
    } // setupUi

    void retranslateUi(QDialog *Settings)
    {
        Settings->setWindowTitle(QApplication::translate("Settings", "Dialog", 0));
        label_4->setText(QApplication::translate("Settings", "\320\220\320\264\320\260\320\277\321\202\320\265\321\200:", 0));
        label_2->setText(QApplication::translate("Settings", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\320\265\320\273\321\214:", 0));
        label_3->setText(QApplication::translate("Settings", "\320\237\320\276\320\273\321\203\321\207\320\260\321\202\320\265\320\273\321\214:", 0));
        leSrcMac->setInputMask(QApplication::translate("Settings", ">HH HH HH HH HH HH", 0));
        leSrcMac->setText(QApplication::translate("Settings", "00 00 00 00 00 00", 0));
        label->setText(QApplication::translate("Settings", "\320\220\320\264\321\200\320\265\321\201", 0));
        leDstMac->setInputMask(QApplication::translate("Settings", ">HH HH HH HH HH HH", 0));
        leDstMac->setText(QApplication::translate("Settings", "00 00 00 00 00 00", 0));
    } // retranslateUi

};

namespace Ui {
    class Settings: public Ui_Settings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGS_H
