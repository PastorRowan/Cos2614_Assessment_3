
#include "views/CarDataView.h"
#include "models/models.h"

#include <QFormLayout>
#include <QLineEdit>

views::CarDataView::CarDataView(
    QWidget *parent
):
    QWidget(parent),
    optionalCarData({}) {

    carFormLayout = new QFormLayout(this);

    numberOfDoorsField = new QLineEdit(this);
    numberOfSeatsField = new QLineEdit(this);

    carFormLayout->addRow("NUMBER_OF_DOORS", numberOfDoorsField);
    carFormLayout->addRow("NUMBER_OF_SEATS", numberOfSeatsField);

    QObject::connect(
        numberOfDoorsField,
        &QLineEdit::textChanged,
        this,
        &views::CarDataView::handleChangeNumberOfDoorsField
    );

    QObject::connect(
        numberOfSeatsField,
        &QLineEdit::textChanged,
        this,
        &views::CarDataView::handleChangeNumberOfSeatsField
    );

};

models::OptionalCarData views::CarDataView::getVehicleData() {
    return optionalCarData;
};

void views::CarDataView::setCarData(
    const models::OptionalCarData optionalCarDataP
) {
    optionalCarData = optionalCarDataP;
    refreshFields();
};

void views::CarDataView::refreshFields() {

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

void views::CarDataView::handleChangeNumberOfDoorsField(
    const QString& text
) {
    if (!optionalCarData.has_value()) {
        return;
    };
    bool ok = false;
    const int value = text.toInt(&ok);
    if (!ok) {
        return;
    };
    optionalCarData->numberOfDoors = value;
};

void views::CarDataView::handleChangeNumberOfSeatsField(
    const QString& text
) {
    if (!optionalCarData.has_value()) {
        return;
    };
    bool ok = false;
    const int value = text.toInt(&ok);
    if (!ok) {
        return;
    };
    optionalCarData->numberOfSeats = value;
};
