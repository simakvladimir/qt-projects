#include "packettable.h"
#include "ui_packettable.h"

#include <QDebug>

PacketTable::PacketTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PacketTable)
{
    ui->setupUi(this);
//    insert_row_in_table( QByteArray("111"));
//    insert_row_in_table( QByteArray("222"));
}

PacketTable::~PacketTable()
{
    delete ui;
}

void PacketTable::insert_row_in_table(QByteArray data)
{
    bool isOk;
    int i, length;
    QString mac_dst, mac_src, stream;

    qDebug() << "[data]" << data.toHex();

    if (data.size() <= 14)
        return;

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    mac_dst = QString::number(data.mid(0,6).toHex().toLongLong(&isOk,16), 16).toUpper();
    qDebug() << mac_dst;
    mac_src = QString::number(data.mid(6,6).toHex().toLongLong(&isOk,16), 16).toUpper();
    qDebug() << mac_src;
    length = data.mid(12,2).toHex().toInt(&isOk,16);
    qDebug() << length;
    for(i = 14; (i < 14 + length) && (i<data.size()); i++ )
      stream.append(QString::number((uchar)data[i], 16));

    qDebug() << stream;
    QTableWidgetItem *newItem = new QTableWidgetItem(mac_dst);
    ui->tableWidget->setItem(row, 0, newItem);

    newItem = new QTableWidgetItem(mac_src);
    ui->tableWidget->setItem(row, 1, newItem);

    newItem = new QTableWidgetItem(QString::number(length));
    ui->tableWidget->setItem(row, 2, newItem);

    newItem = new QTableWidgetItem(stream);
    ui->tableWidget->setItem(row, 3, newItem);
}
