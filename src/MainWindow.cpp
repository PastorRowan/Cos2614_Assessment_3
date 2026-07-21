
#include "MainWindow.h"
#include "ApplicationContext.h"

#include <QPushButton>

MainWindow::MainWindow(
    ApplicationContext& contextP
): context(contextP) {
    button = new QPushButton("Store Content", this);
    setCentralWidget(button);
};

MainWindow::~MainWindow() {};
