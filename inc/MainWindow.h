
#pragma once

#include "ApplicationContext.h" 

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {

    private:

        ApplicationContext& context;
        QPushButton *button;

    public:

        MainWindow(
            ApplicationContext& contextP
        );

        ~MainWindow();

};
