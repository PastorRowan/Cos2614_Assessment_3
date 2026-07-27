
#include "views/MotorcycleDataView.h"
#include "models/models.h"

#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

views::MotorcycleDataView::MotorcycleDataView(
    QWidget *parent
):
    QWidget(parent),
    optionalMotorcycleData({}) {

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

models::OptionalMotorcycleData views::MotorcycleDataView::getVehicleData() {
    return optionalMotorcycleData;
};

void views::MotorcycleDataView::setMotorcycleData(
    const models::OptionalMotorcycleData optionalMotorcycleDataP
) {
    optionalMotorcycleData = optionalMotorcycleDataP;
    refreshFields();
};

void views::MotorcycleDataView::refreshFields() {

    bool hasVehicle = optionalMotorcycleData.has_value();

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        engineCapacityCCField->clear();
    } else {
        // I am sorry
        const models::MotorcycleData& motorcycleData = optionalMotorcycleData.value();
        engineCapacityCCField->setText(QString::number(motorcycleData.engineCapacityCC));
    };

};

void views::MotorcycleDataView::handleChangeEngineCapacityCCField(
    const QString& text
) {
    if (!optionalMotorcycleData.has_value()) {
        return;
    };
    bool ok = false;
    const int engineCapacityCC = text.toInt(&ok);
    if (!ok) {
        return;
    };
    optionalMotorcycleData->engineCapacityCC = engineCapacityCC;

};
