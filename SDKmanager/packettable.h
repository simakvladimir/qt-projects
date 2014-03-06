#ifndef PACKETTABLE_H
#define PACKETTABLE_H

#include <QWidget>

namespace Ui {
class PacketTable;
}

class PacketTable : public QWidget
{
    Q_OBJECT

public:
    explicit PacketTable(QWidget *parent = 0);
    ~PacketTable();

    void insert_row_in_table( QByteArray data );

private:
    Ui::PacketTable *ui;
};

#endif // PACKETTABLE_H
