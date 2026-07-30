
#include "views/CarDataView.h"
#include "models/models.h"

#include <QObject>
#include <memory>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>

/**
 * Constructs a CarDataView widget
 *
 * Initializes the form layout, creates the input fields for car-specific
 * properties, assigns validators, and connects the input fields to their
 * corresponding slots
 *
 * parent - The parent widget
 */
views::CarDataView::CarDataView(
    QWidget *parent
):
    QWidget(parent),
    carData(nullptr) {

    carFormLayout = new QFormLayout(this);

    numberOfDoorsField = new QLineEdit(this);
    numberOfDoorsField->setValidator(
        new QIntValidator(1, 1000)
    );

    numberOfSeatsField = new QLineEdit(this);
    numberOfSeatsField->setValidator(
        new QIntValidator(1, 1000)
    );

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

/**
 * Sets the car data displayed by the widget
 *
 * Stores the supplied car data object and refreshes the displayed values
 *
 * carDataP - Shared pointer to the car data object
 */
void views::CarDataView::setCarData(
    std::shared_ptr<models::CarData> carDataP
) {
    carData = carDataP;
    refreshFields();
};

/**
 * Determines whether the widget currently has car data
 *
 * Returns true if a car data object has been assigned, otherwise false
 */
bool views::CarDataView::hasCarData() const {
    return (carData != nullptr);
};

/**
 * Refreshes the widget's input fields
 *
 * Updates the enabled state of the widget and synchronizes the displayed
 * values with the current car data
 * If no car data is assigned, the input fields are cleared and the widget is disabled
 */
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

/**
 * Handles changes to the number of doors field
 *
 * Converts the entered text to an integer and updates the underlying
 * car data if the conversion succeeds
 *
 * text - The new text entered by the user
 */
void views::CarDataView::handleChangeNumberOfDoorsField(
    const QString text
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

/**
 * Handles changes to the number of seats field
 *
 * Converts the entered text to an integer and updates the underlying
 * car data if the conversion succeeds
 *
 * text - The new text entered by the user
 */
void views::CarDataView::handleChangeNumberOfSeatsField(
    const QString text
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
