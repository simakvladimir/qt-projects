#ifndef MOVE_H
#define MOVE_H

class Move{
public:
    Move(int x, int y) :
        m_x(x),
        m_y(y)
    {}
    int x() const { return m_x; }
    int y() const { return m_y; }
private:
    int m_x;
    int m_y;
};

#endif // MOVE_H
