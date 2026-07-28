
#include "dialogues/AddVehicleDialogue.h"
#include "views/VehicleDataView.h"

#include <QObject>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QWidget>

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

    vehicleTypeComboBox->setCurrentIndex(0);

};

void dialogues::AddVehicleDialogue::open() {
    exec();
};

void dialogues::AddVehicleDialogue::handleVehicleTypeChanged(
    int vehicleTypeId
) {

    switch (static_cast<models::VehicleTypeId>(vehicleTypeId)) {
        case models::VehicleTypeId::car:
            vehicleData = std::make_unique<models::CarData>();
            break;
        case models::VehicleTypeId::motorCycle:
            vehicleData = std::make_unique<models::MotorcycleData>();
            break;
        default:
            vehicleData.reset();
            break;
    };

    if (vehicleData) {
        vehicleDataView->setVehicleData(*vehicleData);
    };

};

void dialogues::AddVehicleDialogue::handleAddVehicle(
    const models::VehicleData& vehicleData
) {

    emit addVehicle(vehicleData);

    accept();

};
