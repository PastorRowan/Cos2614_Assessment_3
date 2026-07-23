
#include "views/carView.h"
#include "vehicles/vehicles.h"

#include <QVBoxLayout>
#include <QLineEdit>

const vehicles::Car* views::CarView::getCar() const {
    return car;
};

void views::CarView::setCar(vehicles::Car* newCar) {
    car = newCar;
    refreshFields();
};

void views::CarView::refreshFields() {

    bool hasVehicle = (getCar() != nullptr);

    numberOfDoorsField->setVisible(hasVehicle);
    numberOfSeatsField->setVisible(hasVehicle);

    if (!hasVehicle) {
        numberOfDoorsField->clear();
        numberOfSeatsField->clear();
    } else {
        numberOfDoorsField->setText(getCar()->numberOfDoorsToQString());
        numberOfSeatsField->setText(getCar()->numberOfSeatsToQString());
    };

};

views::CarView::CarView(
    QWidget *parent,
    vehicles::Car* carP
):
    QWidget(parent),
    car(carP) {

    vBoxLayout = new QVBoxLayout(this);

    numberOfDoorsField = new QLineEdit(this);
    numberOfSeatsField = new QLineEdit(this);

    vBoxLayout->addWidget(numberOfDoorsField);
    vBoxLayout->addWidget(numberOfSeatsField);

};
