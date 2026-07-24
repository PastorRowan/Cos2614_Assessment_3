
#include "views/views.h"
#include "vehicles/vehicles.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>

views::VehicleView::VehicleView(
    QWidget *parent,
    vehicles::Vehicle* vehicleP
):
    QWidget(parent) {

    vBoxLayout = new QVBoxLayout(this);

    vehicleFormWidget = new QWidget(this);
    vehicleFormLayout = new QFormLayout(vehicleFormWidget);

    typeIdLabel = new QLabel(this);
    vehicleIdLabel = new QLabel(this);
    brandField = new QLineEdit(this);
    modelField = new QLineEdit(this);
    pricePerDayField = new QLineEdit(this);
    isRentedLabel = new QLabel(this);

    carView = new views::CarView(this, nullptr);
    carView->hide();
    motorcycleView = new views::MotorcycleView(this, nullptr);
    motorcycleView->hide();

    vehicleFormWidget->setLayout(vehicleFormLayout);
    vehicleFormLayout->addRow("TYPE_ID: ", typeIdLabel);
    vehicleFormLayout->addRow("VEHICLE_ID: ", vehicleIdLabel);
    vehicleFormLayout->addRow("BRAND: ", brandField);
    vehicleFormLayout->addRow("MODEL: ", modelField);
    vehicleFormLayout->addRow("PRICE_PER_DAY: ", pricePerDayField);
    vehicleFormLayout->addRow("IS_RENTED: ", isRentedLabel);

    vBoxLayout->addWidget(vehicleFormWidget);
    vBoxLayout->addWidget(carView);
    vBoxLayout->addWidget(motorcycleView);

    setVehicle(vehicleP);

};

const vehicles::Vehicle* views::VehicleView::getVehicle() const {
    return vehicle;
};

void views::VehicleView::setVehicle(
    vehicles::Vehicle* vehicleP
) {

    vehicle = vehicleP;
    refreshFields();

    if (auto* car = dynamic_cast<vehicles::Car*>(vehicle)) {

        motorcycleView->hide();
        motorcycleView->setMotorcycle(nullptr);

        carView->setCar(car);
        carView->show();

    } else if (auto* motorcycle = dynamic_cast<vehicles::Motorcycle*>(vehicle)) {

        carView->hide();
        carView->setCar(nullptr);

        motorcycleView->setMotorcycle(motorcycle);
        motorcycleView->show();

    } else {
        carView->hide();
        motorcycleView->hide();
    };

};

void views::VehicleView::refreshFields() {

    bool hasVehicle = (getVehicle() != nullptr);

    vehicleFormWidget->setEnabled(hasVehicle);

    if (!hasVehicle) {
        typeIdLabel->setText("");
        vehicleIdLabel->setText("");
        brandField->clear();
        modelField->clear();
        pricePerDayField->clear();
        isRentedLabel->setText("");
    } else {
        typeIdLabel->setText(getVehicle()->typeIdToQString());
        vehicleIdLabel->setText(getVehicle()->getVehicleId());
        brandField->setText(getVehicle()->getBrand());
        modelField->setText(getVehicle()->getModel());
        pricePerDayField->setText(getVehicle()->pricePerDayToQString());
        isRentedLabel->setText(getVehicle()->isRentedToQString());
    };

};

void views::VehicleView::handleVehicleSelected(vehicles::Vehicle* vehicleP) {
    qDebug() << "handleVehicleSelected is running with vehicle id: " << vehicleP->getVehicleId();
    setVehicle(vehicleP);
};
