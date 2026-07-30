
/**
 * Please read README.md before trying to run the application
 * Also see https://github.com/PastorRowan/Cos2614_Assessment_3.git for the best viewing experience
 */

// Entry point for the Vehicle Rental Management application

#include "MainWindow.h"
#include "models/models.h"

#include <QApplication>
#include <QDebug>

// Application entry point
int main(int argc, char *argv[]) {

    // Qt application object required for Qt-based applications
    QApplication app(argc, argv);

    MainWindow win;
    win.resize(500, 400);
    win.setVisible(true);

    // Terminate the application
    return app.exec();

};
