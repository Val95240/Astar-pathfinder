#include "Square.hpp"


Square::Square(int x, int y, int width, int height, QColor col) :
    x(x), y(y), cost(100000), state(NONE), parent(0)
{
    setAcceptHoverEvents(true);
    setRect(20+30*y, 20+30*x, width, height);
    setBrush(col);
}

// Getters
int Square::getX() { return x; }
int Square::getY() { return y; }
int Square::getCost() { return cost; }
int Square::getState() { return state; }
Square* Square::getParent() { return parent; }

// Setters
void Square::setCost(int co) { cost = co; }
void Square::setParent(Square* par) { parent = par; }


void Square::setState(State st)
{
    state = st;
    setBrush(colors[state]);
}

void Square::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (state > 4)
        return;

    Qt::KeyboardModifiers keyMod = QApplication::keyboardModifiers();
    if (keyMod & Qt::ControlModifier) {
        setState(WALL);
    }
    else if (keyMod & Qt::ShiftModifier || state == NONE) {
        setState(HOVERED);
    }
}

void Square::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (state == HOVERED)
        setState(NONE);
}
