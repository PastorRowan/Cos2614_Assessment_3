
#pragma once

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {

    public:
        MainWindow();
        ~MainWindow();

    private:
        QPushButton *button;

};
