
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

    handleVehicleTypeChanged(static_cast<int>(models::VehicleTypeId::car));

};

void dialogues::AddVehicleDialogue::open() {
    exec();
};

void dialogues::AddVehicleDialogue::handleVehicleTypeChanged(
    int vehicleTypeId
) {

    qDebug() 
        << "dialogues::AddVehicleDialogue::handleVehicleTypeChanged was called with vehicleTypeId: " << vehicleTypeId
    ;

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

void dialogues::AddVehicleDialogue::handleAddVehicle(
    std::shared_ptr<const models::VehicleData> vehicleData
) {

    qDebug() << "AddVehicleDialogue handleAddVehicle is running with vehicleData.brand: " << vehicleData->brand;

    emit addVehicle(vehicleData);

    accept();

};
