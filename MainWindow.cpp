#include "MainWindow.hpp"

MainWindow::MainWindow(int argc, char *argv[])
{
    srand(time(0));
    scene = new QGraphicsScene;
    view = new QGraphicsView(scene);

    for (int i=0; i<HEIGHT; ++i)
    {
        for (int j=0; j<WIDTH; ++j)
        {
            grid[i*WIDTH+j] = new Square(i, j, 30, 30, Qt::white);
            scene->addItem(grid[i*WIDTH+j]);
        }
    }
    reset(true);

    QPushButton *solve = new QPushButton("&Solve");
    QPushButton *reset = new QPushButton("&Reset");
    QPushButton *regen = new QPushButton("&New");
    QPushButton *quit  = new QPushButton("&Quit");

    QGraphicsProxyWidget *solve_widget = scene->addWidget(solve);
    QGraphicsProxyWidget *reset_widget = scene->addWidget(reset);
    QGraphicsProxyWidget *regen_widget = scene->addWidget(regen);
    QGraphicsProxyWidget *quit_widget  = scene->addWidget(quit);

    solve_widget->setPos(  (WIDTH*30+20) / 6, 23+30*HEIGHT);
    reset_widget->setPos(2*(WIDTH*30+20) / 6, 23+30*HEIGHT);
    regen_widget->setPos(3*(WIDTH*30+20) / 6, 23+30*HEIGHT);
    quit_widget ->setPos(4*(WIDTH*30+20) / 6, 23+30*HEIGHT);

    connect(solve, SIGNAL(clicked()), this, SLOT(solve()));
    connect(reset, SIGNAL(clicked()), this, SLOT(reset()));
    connect(regen, SIGNAL(clicked()), this, SLOT(regen()));
    connect(quit,  SIGNAL(clicked()), qApp, SLOT(quit() ));
}

MainWindow::~MainWindow()
{
    for (int k=0; k<HEIGHT*WIDTH; ++k) {
        delete grid[k];
    }
    delete view;
    delete scene;
}

void MainWindow::solve()
{
    for (int k=0; k<HEIGHT*WIDTH; ++k) {
        if (grid[k]->getState() == PATH || grid[k]->getState() == OUTSIDE_PATH)
            grid[k]->setState(NONE);
    }

    vector_pair pair = astar(WIDTH, HEIGHT, grid, startX, startY, goalX, goalY);
    std::vector<Square*> closedList = pair.first;
    std::vector<Square*> path = pair.second;
    if (path.empty()) {
        std::cout << "No path !" << std::endl;
    } else {
        for (Square* sq : closedList) {
            if (sq->getState() != START && sq->getState() != GOAL)
                sq->setState(OUTSIDE_PATH);
        }
        for (std::vector<Square*>::reverse_iterator rit = path.rbegin(); rit != path.rend(); ++rit)
        {
            if ((*rit)->getState() == NONE || (*rit)->getState() == HOVERED ||
                (*rit)->getState() == OUTSIDE_PATH)
                (*rit)->setState(PATH);
            qApp->processEvents();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
    }
}

void MainWindow::reset(bool regen)
{
    for (int k=0; k<HEIGHT*WIDTH; ++k)
        grid[k]->setState(NONE);

    if (regen) {
        startX = rand() % HEIGHT;
        startY = rand() % WIDTH;
        do {
            goalX = rand() % HEIGHT;
            goalY = rand() % WIDTH;
        } while (startX == goalX && startY == goalY || \
                abs(startX-goalX) + abs(startY-goalY) < std::min(HEIGHT, WIDTH)-5);
    }

    grid[startX * WIDTH + startY]->setState(START);
    grid[goalX * WIDTH + goalY]->setState(GOAL);
}

void MainWindow::regen()
{
    reset(true);
}


void MainWindow::show()
{
    view->show();
}
