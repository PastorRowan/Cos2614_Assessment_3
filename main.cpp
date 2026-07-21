
// Entry point for the Vehicle Rental Management application

#include <QApplication>

#include "MainWindow.h"

// Application entry point
int main(int argc, char *argv[]) {

    // Qt core application object required for Qt-based applications
    QApplication app(argc, argv);

    MainWindow win;
    win.resize(320, 240);
    win.setVisible(true);

    // Terminate the application
    return app.exec();

};
