
#include "Config.h"

#include "MainWindow.h"
#include "models/VehicleRepository.h"
#include "helpers/populateVehicleRepository.h"
#include "views/views.h"
#include "dialogues/dialogues.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) {

    addVehicleDialogue = new dialogues::AddVehicleDialogue(this);

    central = new QWidget(this);
    central->setContentsMargins(10, 10, 10, 10);

    content = new QWidget(central);
    content->setMaximumWidth(800);

    centralHLayout = new QHBoxLayout(central);
    centralHLayout->addStretch();
    centralHLayout->addWidget(content);
    centralHLayout->addStretch();

    title = new QLabel(content);
    title->setText("Vehicle Rental System");
    title->setAlignment(Qt::AlignCenter);

    vehicleRepository = new models::VehicleRepository(this);

    #if POPULATE_VEHICLES_FILE
        helpers::populateVehicleRepository(vehicleRepository);
    #endif

    vehiclesRepositoryView = new views::VehiclesRepositoryView(content, vehicleRepository);

    addVehicleButton = new QPushButton(this);
    addVehicleButton->setText("Add Vehicle");

    vehicleDataView = new views::VehicleDataView(content);
    vehicleDataView->setConfirmButtonText("Save changes");

    contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesRepositoryView);
    contentVLayout->addWidget(addVehicleButton);
    contentVLayout->addWidget(vehicleDataView);
    contentVLayout->addStretch();

    setCentralWidget(central);

    QObject::connect(
        vehiclesRepositoryView,
        &views::VehiclesRepositoryView::vehicleSelected,
        vehicleDataView,
        &views::VehicleDataView::handleVehicleSelected
    );

    QObject::connect(
        vehicleDataView,
        &views::VehicleDataView::confirmVehicle,
        vehicleRepository,
        &models::VehicleRepository::handleUpdateVehicle
    );

    QObject::connect(
        addVehicleButton,
        &QPushButton::clicked,
        addVehicleDialogue,
        &dialogues::AddVehicleDialogue::open
    );

    QObject::connect(
        addVehicleDialogue,
        &dialogues::AddVehicleDialogue::addVehicle,
        vehicleRepository,
        &models::VehicleRepository::handleAddVehicle
    );

};
