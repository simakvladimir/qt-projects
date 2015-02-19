#ifndef CELL_H
#define CELL_H

#include <QObject>

class Cell : public QObject
{
    Q_OBJECT
public:
    enum {
        CELL_EMPTY,

        CELL_TIC,
        CELL_TAC
    };

    explicit Cell(int x, int y, int value = CELL_EMPTY, QObject *parent = 0) :
        QObject(parent),
        m_x(x),
        m_y(y),
        m_value(value)
    {
    }

    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    void setValue(int value) { if (m_value == value) return; m_value = value; emit valueChanged(); }
    int value() const        { return m_value;  }

    bool isEmpty() const     { return m_value == CELL_EMPTY ? true : false; }

    int x() const { return m_x; }
    int y() const { return m_y; }

signals:
    void valueChanged();

public slots:

private:
    int m_x;
    int m_y;

    int m_value;
};

#endif // CELL_H
