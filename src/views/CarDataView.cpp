
#include "views/CarDataView.h"
#include "models/models.h"

#include <QFormLayout>
#include <QLineEdit>

views::CarDataView::CarDataView(
    QWidget *parent
):
    QWidget(parent),
    carData(nullptr) {

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

void views::CarDataView::setCarData(
    models::CarData* carDataP
) {
    carData = carDataP;
    refreshFields();
};

bool views::CarDataView::hasCarData() const {
    return (carData != nullptr);
};

void views::CarDataView::refreshFields() {

    bool hasVehicle = hasCarData();

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        numberOfDoorsField->clear();
        numberOfSeatsField->clear();
    } else {
        numberOfDoorsField->setText(carData->getNumberOfDoorsAsQString());
        numberOfSeatsField->setText(carData->getNumberOfSeatsAsQString());
    };

};

void views::CarDataView::handleChangeNumberOfDoorsField(
    const QString& text
) {
    if (!hasCarData()) {
        return;
    };
    bool ok = false;
    const int value = text.toInt(&ok);
    if (!ok) {
        return;
    };
    carData->numberOfDoors = value;
};

void views::CarDataView::handleChangeNumberOfSeatsField(
    const QString& text
) {
    if (!hasCarData()) {
        return;
    };
    bool ok = false;
    const int value = text.toInt(&ok);
    if (!ok) {
        return;
    };
    carData->numberOfSeats = value;
};
