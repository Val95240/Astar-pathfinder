#ifndef HEADER_SQUARE
#define HEADER_SQUARE

#include <iostream>
#include <QApplication>
#include <QtWidgets>

enum State {NONE, HOVERED, WALL, OUTSIDE_PATH, PATH, START, GOAL};

const QColor colors[7] = {Qt::white, Qt::lightGray, Qt::black,
                          Qt::darkBlue, Qt::blue, Qt::red, Qt::green};


class Square : public QGraphicsRectItem
{
    public:
        Square(int x, int y, int width, int height, QColor col);

        int getX();
        int getY();
        int getCost();
        int getState();
        Square* getParent();

        void setCost(int co);
        void setParent(Square* par);

        void setState(State st);

    private:
        int x, y;
        int cost, priority;
        Square* parent;
        State state;

        void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif //HEADER_SQUARE
