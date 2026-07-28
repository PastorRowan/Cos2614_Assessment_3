
#include "views/MotorcycleDataView.h"
#include "models/models.h"

#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

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

void views::MotorcycleDataView::setMotorcycleData(
    models::MotorcycleData* motorcycleDataP
) {
    motorcycleData = motorcycleDataP;
    refreshFields();
};

bool views::MotorcycleDataView::hasMotorcycleData() const {
    return (motorcycleData != nullptr);
};

void views::MotorcycleDataView::refreshFields() {

    bool hasVehicle = hasMotorcycleData();

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        engineCapacityCCField->clear();
    } else {
        engineCapacityCCField->setText(motorcycleData->getEngineCapacityCCAsQString());
    };

};

void views::MotorcycleDataView::handleChangeEngineCapacityCCField(
    const QString& text
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
