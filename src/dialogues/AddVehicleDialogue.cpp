
#include "dialogues/AddVehicleDialogue.h"
#include "views/VehicleDataView.h"

#include <QObject>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QDebug>

/**
 * Constructs an AddVehicleDialogue
 *
 * Creates the dialog's user interface, including the title, vehicle type
 * selector, and embedded VehicleDataView
 * Connects the required signals and slots and initializes the dialog to create a car by default
 *
 * parent - The parent widget, defaults to nullptr
 */
dialogues::AddVehicleDialogue::AddVehicleDialogue(
    QWidget *parent
):
    QDialog(parent) {

    vBoxLayout = new QVBoxLayout(this);

    title = new QLabel(this);
    title->setText("Add Vehicle Dialogue");
    title->setAlignment(Qt::AlignCenter);

    vehicleTypeComboBox = new QComboBox(this);
    vehicleTypeComboBox->addItem("Car", static_cast<int>(models::VehicleTypeId::car));
    vehicleTypeComboBox->addItem("Motorcycle", static_cast<int>(models::VehicleTypeId::motorCycle));

    vehicleDataView = new views::VehicleDataView(this);
    vehicleDataView->setConfirmButtonText("Confirm");

    vBoxLayout->addWidget(title);
    vBoxLayout->addWidget(vehicleTypeComboBox);
    vBoxLayout->addWidget(vehicleDataView);
    vBoxLayout->addStretch();

    QObject::connect(
        vehicleTypeComboBox,
        &QComboBox::currentIndexChanged,
        this,
        &dialogues::AddVehicleDialogue::handleVehicleTypeChanged
    );

    QObject::connect(
        vehicleDataView,
        &views::VehicleDataView::confirmVehicle,
        this,
        &dialogues::AddVehicleDialogue::handleAddVehicle
    );

    handleVehicleTypeChanged(static_cast<int>(models::VehicleTypeId::car));

};

/**
 * Opens the dialog and prevent interaction with the rest of the GUI
 *
 * Displays the dialog and blocks until the user accepts or rejects it
 */
void dialogues::AddVehicleDialogue::open() {
    exec();
};

/**
 * Handles changes to the selected vehicle type
 *
 * Creates a new empty vehicle object of the selected type and assigns it to
 * the embedded VehicleDataView for editing
 *
 *  vehicleTypeId - The selected vehicle type identifier
 */
void dialogues::AddVehicleDialogue::handleVehicleTypeChanged(
    int vehicleTypeId
) {

    switch (static_cast<models::VehicleTypeId>(vehicleTypeId)) {
        case models::VehicleTypeId::car:
            vehicleDataView->setVehicleData(
                std::make_shared<models::CarData>(
                    "", "", 0.0, 0, 0, false
                )
            );
            break;
        case models::VehicleTypeId::motorCycle:
            vehicleDataView->setVehicleData(
                std::make_shared<models::MotorcycleData>(
                    "", "", 0.0, 0, false
                )
            );
            break;
        default:
            vehicleDataView->setVehicleData(
                nullptr
            );
            break;
    };

};

/**
 * Handles confirmation of a new vehicle
 *
 * Emits the addVehicle() signal with the completed vehicle data and closes
 * the dialog with an accepted result
 *
 * vehicleData - The vehicle data entered by the user
 */
void dialogues::AddVehicleDialogue::handleAddVehicle(
    std::shared_ptr<const models::VehicleData> vehicleData
) {

    qDebug() << "AddVehicleDialogue handleAddVehicle is running with vehicleData.brand: " << vehicleData->brand;

    emit addVehicle(vehicleData);

    accept();

};
