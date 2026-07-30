
#include "views/MotorcycleDataView.h"
#include "models/models.h"

#include <QObject>
#include <memory>
#include <QFormLayout>
#include <QLineEdit>

/**
 * Constructs a MotorcycleDataView widget
 *
 * Initializes the form layout, creates the input field for the engine
 * capacity, and connects the field to its corresponding slot
 *
 * parent The parent widget
 */
views::MotorcycleDataView::MotorcycleDataView(
    QWidget *parent
):
    QWidget(parent),
    motorcycleData(nullptr) {

    motorcycleFormLayout = new QFormLayout(this);

    engineCapacityCCField = new QLineEdit(this);

    motorcycleFormLayout->addRow("ENGINE_CAPACITY_CC", engineCapacityCCField);

    QObject::connect(
        engineCapacityCCField,
        &QLineEdit::textChanged,
        this,
        &views::MotorcycleDataView::handleChangeEngineCapacityCCField
    );

};


/**
 * Sets the motorcycle data displayed by the widget
 *
 * Stores the supplied motorcycle data object and refreshes the displayed
 * values
 *
 * motorcycleDataP - Shared pointer to the motorcycle data object
 */
void views::MotorcycleDataView::setMotorcycleData(
    std::shared_ptr<models::MotorcycleData> motorcycleDataP
) {
    motorcycleData = motorcycleDataP;
    refreshFields();
};

/**
 * Determines whether the widget currently has motorcycle data
 *
 * True if a motorcycle data object has been assigned, otherwise false
 */
bool views::MotorcycleDataView::hasMotorcycleData() const {
    return (motorcycleData != nullptr);
};

/**
 * Refreshes the widget's input field
 *
 * Updates the enabled state of the widget and synchronizes the displayed
 * engine capacity with the current motorcycle data
 * If no motorcycle data is assigned, the input field is cleared and the widget is disabled
 */
void views::MotorcycleDataView::refreshFields() {

    bool hasVehicle = hasMotorcycleData();

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        engineCapacityCCField->clear();
    } else {
        engineCapacityCCField->setText(motorcycleData->getEngineCapacityCCAsQString());
    };

};

/**
 * Handles changes to the engine capacity field
 *
 * Converts the entered text to an integer and updates the underlying
 * motorcycle data if the conversion succeeds
 *
 * text - The new text entered by the user
 */
void views::MotorcycleDataView::handleChangeEngineCapacityCCField(
    const QString text
) {
    if (!hasMotorcycleData()) {
        return;
    };
    bool ok = false;
    const int engineCapacityCC = text.toInt(&ok);
    if (!ok) {
        return;
    };
    motorcycleData->engineCapacityCC = engineCapacityCC;

};
