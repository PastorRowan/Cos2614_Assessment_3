
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

/**
 * Constructs the application's main window
 *
 * Creates and initializes the application's user interface, including the
 * vehicle repository, repository view, vehicle editor, and add-vehicle
 * dialog
 *
 * All layouts, widgets, and signal-slot connections required for
 * normal application operation are established during construction
 *
 * If the compile-time configuration option
 * `POPULATE_VEHICLES_FILE` is enabled, the repository is populated with sample vehicle data
 *
 * The following interactions are configured:
 * - Selecting a vehicle updates the vehicle editor
 * - Confirming edits updates the selected vehicle in the repository
 * - Clicking the **Add Vehicle** button opens the add-vehicle dialog
 * - Confirming the dialog adds the new vehicle to the repository
 *
 * parent - The parent widget
 */
MainWindow::MainWindow(QWidget *parent) {

    vehicleRepository = new models::VehicleRepository(this);

    // uncomment to clear and then fill vehicle repository with sample data
    // helpers::populateVehicleRepository(vehicleRepository);

    addVehicleDialogue = new dialogues::AddVehicleDialogue(this);
    deleteVehicleDialogue = new dialogues::DeleteVehicleDialogue(this);

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

    vehiclesRepositoryView = new views::VehiclesRepositoryView(content, vehicleRepository);

    buttonBarWidget = new QWidget(content);
    buttonBarHBox = new QHBoxLayout(buttonBarWidget);

    addVehicleButton = new QPushButton(this);
    addVehicleButton->setText("Add Vehicle");

    deleteVehicleButton = new QPushButton(this);
    deleteVehicleButton->setText("Delete Vehicle");

    buttonBarHBox->addWidget(addVehicleButton);
    buttonBarHBox->addWidget(deleteVehicleButton);

    vehicleDataView = new views::VehicleDataView(content);
    vehicleDataView->setConfirmButtonText("Save Changes");

    contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesRepositoryView);
    contentVLayout->addWidget(buttonBarWidget);
    contentVLayout->addWidget(vehicleDataView);
    contentVLayout->addStretch();

    setCentralWidget(central);

    QObject::connect(
        vehiclesRepositoryView,
        &views::VehiclesRepositoryView::vehicleSelected,
        this,
        &MainWindow::handleVehicleSelected
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

    QObject::connect(
        deleteVehicleButton,
        &QPushButton::clicked,
        deleteVehicleDialogue,
        &dialogues::DeleteVehicleDialogue::open
    );

    QObject::connect(
        deleteVehicleDialogue,
        &dialogues::DeleteVehicleDialogue::deleteVehicle,
        vehicleRepository,
        &models::VehicleRepository::handleDeleteVehicle
    );

};

void MainWindow::handleVehicleSelected(
    std::shared_ptr<const models::VehicleData> vehicleData
) {
    vehicleDataView->setVehicleData(vehicleData);
    deleteVehicleDialogue->setVehicleData(vehicleData);
};
