
#include "views/views.h"
#include "models/Vehicle.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

views::VehicleView::VehicleView(
    QWidget *parent
):
    QWidget(parent),
    optionalVehicleData({}) {

    vBoxLayout = new QVBoxLayout(this);

    vehicleFormWidget = new QWidget(this);
    vehicleFormLayout = new QFormLayout(vehicleFormWidget);

    VehicleTypeIdLabel = new QLabel(this);
    vehicleIdLabel = new QLabel(this);
    brandField = new QLineEdit(this);
    modelField = new QLineEdit(this);
    pricePerDayField = new QLineEdit(this);
    isRentedLabel = new QLabel(this);

    carView = new views::CarView(this);
    carView->hide();
    motorcycleView = new views::MotorcycleView(this);
    motorcycleView->hide();

    saveChangesButton = new QPushButton(this);
    saveChangesButton->setText("Save Changes");

    vehicleFormWidget->setLayout(vehicleFormLayout);
    vehicleFormLayout->addRow("TYPE_ID: ", VehicleTypeIdLabel);
    vehicleFormLayout->addRow("VEHICLE_ID: ", vehicleIdLabel);
    vehicleFormLayout->addRow("BRAND: ", brandField);
    vehicleFormLayout->addRow("MODEL: ", modelField);
    vehicleFormLayout->addRow("PRICE_PER_DAY: ", pricePerDayField);
    vehicleFormLayout->addRow("IS_RENTED: ", isRentedLabel);

    vBoxLayout->addWidget(vehicleFormWidget);
    vBoxLayout->addWidget(carView);
    vBoxLayout->addWidget(motorcycleView);

};

void views::VehicleView::setVehicleData(
    const models::Vehicle* vehicle
) {

    if (vehicle == nullptr) {
        optionalVehicleData.reset();
        carView->hide();
        motorcycleView->hide();
        return;
    } else {
        models::Vehicle* clonedVehicle = vehicle->clone();

        optionalVehicleData = clonedVehicle->getVehicleData();

        if (auto* car = dynamic_cast<models::Car*>(clonedVehicle)) {

            motorcycleView->hide();
            motorcycleView->setMotorcycleData({});

            carView->setCarData(car->getCarData());
            carView->show();

        } else if (auto* motorcycle = dynamic_cast<models::Motorcycle*>(clonedVehicle)) {

            carView->hide();
            carView->setCarData({});

            motorcycleView->setMotorcycleData(motorcycle->getMotorcycleData());
            motorcycleView->show();

        };

        delete clonedVehicle;

    };

    refreshFields();

};

void views::VehicleView::refreshFields() {

    bool hasVehicle = optionalVehicleData.has_value();

    vehicleFormWidget->setEnabled(hasVehicle);

    if (!hasVehicle) {
        VehicleTypeIdLabel->setText("");
        vehicleIdLabel->setText("");
        brandField->clear();
        modelField->clear();
        pricePerDayField->clear();
        isRentedLabel->setText("");
    } else {
        // I am sorry
        const models::VehicleData& vehicleData = optionalVehicleData.value();
        VehicleTypeIdLabel->setText(QString::number(static_cast<int>(vehicleData.vehicleTypeId)));
        vehicleIdLabel->setText(QString::number(vehicleData.vehicleId));
        brandField->setText(vehicleData.brand);
        modelField->setText(vehicleData.model);
        pricePerDayField->setText(QString::number(vehicleData.pricePerDay));
        isRentedLabel->setText(vehicleData.isRented ? "Yes" : "No");
    };

};

void views::VehicleView::handleVehicleSelected(models::Vehicle* vehicle) {
    qDebug() << "handleVehicleSelected is running with vehicle id: " << vehicle->getVehicleIdAsQString();
    setVehicleData(vehicle);
};
