#ifndef HEADER_MAINWINDOW
#define HEADER_MAINWINDOW

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <chrono>

#include <QApplication>
#include <QtWidgets>

#include "Square.hpp"
#include "Astar.hpp"


const int HEIGHT = 30;
const int WIDTH = 45;

class MainWindow : public QWidget
{
    Q_OBJECT

    public:
        MainWindow(int argc, char *argv[]);
        ~MainWindow();

        void show();

    public slots:
        void solve();
        void reset(bool regen=false);
        void regen();

    private:
        QGraphicsScene* scene;
        QGraphicsView* view;
        Square* grid[HEIGHT*WIDTH];

        int startX, startY;
        int goalX, goalY;
};

#endif //HEADER_MAINWINDOW
