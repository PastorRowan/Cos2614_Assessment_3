
#include "MainWindow.h"

#include <QPushButton>

MainWindow::MainWindow() {
    button = new QPushButton("Store Content", this);
    setCentralWidget(button);
};

MainWindow::~MainWindow() {};
