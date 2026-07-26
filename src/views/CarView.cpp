
#include "views/carView.h"
#include "models/models.h"

#include <QFormLayout>
#include <QLineEdit>

views::CarView::CarView(
    QWidget *parent
):
    QWidget(parent),
    optionalCarData({}) {

    carFormLayout = new QFormLayout(this);

    numberOfDoorsField = new QLineEdit(this);
    numberOfSeatsField = new QLineEdit(this);

    carFormLayout->addRow("NUMBER_OF_DOORS", numberOfDoorsField);
    carFormLayout->addRow("NUMBER_OF_SEATS", numberOfSeatsField);

};

void views::CarView::setCarData(
    const models::OptionalCarData optionalCarDataP
) {
    optionalCarData = optionalCarDataP;
    refreshFields();
};

void views::CarView::refreshFields() {

    bool hasVehicle = optionalCarData.has_value();

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        numberOfDoorsField->clear();
        numberOfSeatsField->clear();
    } else {
        // I am sorry
        const models::CarData& carData = optionalCarData.value();
        numberOfDoorsField->setText(QString::number(carData.numberOfDoors));
        numberOfSeatsField->setText(QString::number(carData.numberOfSeats));
    };

};
