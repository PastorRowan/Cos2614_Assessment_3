
// Entry point for the Vehicle Rental Management application

#include "MainWindow.h"
#include "ApplicationContext.h"
#include "VehiclesFile/VehiclesFile.h"

#include <QApplication>
#include <QDebug>

// Application entry point
int main(int argc, char *argv[]) {

    // Qt application object required for Qt-based applications
    QApplication app(argc, argv);

    ApplicationContext context;

    MainWindow win(context);
    win.resize(500, 400);
    win.setVisible(true);

    // Terminate the application
    return app.exec();

};
