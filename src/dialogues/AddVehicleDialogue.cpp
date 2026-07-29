
#include "dialogues/AddVehicleDialogue.h"
#include "views/VehicleDataView.h"

#include <QObject>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QWidget>
#include <QDebug>

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
            vehicleDataView->setVehicleData(
                std::make_shared<models::CarData>()
            );
            break;
        case models::VehicleTypeId::motorCycle:
            vehicleDataView->setVehicleData(
                std::make_shared<models::MotorcycleData>()
            );
            break;
        default:
            vehicleDataView->setVehicleData(
                nullptr
            );
            break;
    };

};

void dialogues::AddVehicleDialogue::handleAddVehicle(
    const std::shared_ptr<const models::VehicleData> vehicleData
) {

    qDebug() << "AddVehicleDialogue handleAddVehicle is running with vehicleData.brand: " << vehicleData->brand;

    emit addVehicle(vehicleData);

    accept();

};
