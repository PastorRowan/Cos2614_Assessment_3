
#include "views/views.h"
#include "vehicles/vehicles.h"

#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

views::VehicleView::VehicleView(
    QWidget *parent,
    vehicles::Vehicle* vehicleP
):
    QWidget(parent),
    vehicle(vehicleP) {

    vBoxLayout = new QVBoxLayout(this);

    typeIdLabel = new QLabel(this);
    vehicleIdLabel = new QLabel(this);
    brandField = new QLineEdit(this);
    modelField = new QLineEdit(this);
    pricePerDayField = new QLineEdit(this);
    isRentedLabel = new QLabel(this);

    carView = new views::CarView(this, nullptr);
    motorcycleView = new views::MotorcycleView(this, nullptr);

    vBoxLayout->addWidget(typeIdLabel);
    vBoxLayout->addWidget(vehicleIdLabel);
    vBoxLayout->addWidget(brandField);
    vBoxLayout->addWidget(modelField);
    vBoxLayout->addWidget(pricePerDayField);
    vBoxLayout->addWidget(isRentedLabel);

    setLayout(vBoxLayout);

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

    };

};

void views::VehicleView::refreshFields() {

    bool hasVehicle = (getVehicle() != nullptr);

    typeIdLabel->setVisible(hasVehicle);
    vehicleIdLabel->setVisible(hasVehicle);
    brandField->setVisible(hasVehicle);
    modelField->setVisible(hasVehicle);
    pricePerDayField->setVisible(hasVehicle);
    isRentedLabel->setVisible(hasVehicle);

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
