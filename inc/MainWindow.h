
#pragma once

#include "models/VehicleRepository.h"
#include "views/views.h"
#include "dialogues/dialogues.h"

#include <QMainWindow>
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;

class MainWindow : public QMainWindow {

    private:

        dialogues::AddVehicleDialogue *addVehicleDialogue;

        QWidget* central;
        QWidget* content;

        QHBoxLayout* centralHLayout;
        QVBoxLayout* contentVLayout;

        QLabel* title;
        QPushButton* addVehicleButton;

        models::VehicleRepository* vehicleRepository;

        views::VehiclesRepositoryView* vehiclesRepositoryView;
        views::VehicleDataView* vehicleDataView;


    public:

        MainWindow(QWidget *parent = nullptr);

        ~MainWindow() = default;

};
