
#pragma once

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {

    private:

        QPushButton *button;

    public:

        MainWindow(QWidget *parent = nullptr);

        ~MainWindow();

};
