
#include "views/MotorcycleView.h"
#include "models/models.h"

#include <QFormLayout>
#include <QLineEdit>

views::MotorcycleView::MotorcycleView(
    QWidget *parent
):
    QWidget(parent),
    optionalMotorcycleData({}) {

    motorcycleFormLayout = new QFormLayout(this);

    engineCapacityCCField = new QLineEdit(this);

    motorcycleFormLayout->addRow("ENGINE_CAPACITY_CC", engineCapacityCCField);

};

void views::MotorcycleView::setMotorcycleData(
    const models::OptionalMotorcycleData optionalMotorcycleDataP
) {
    optionalMotorcycleData = optionalMotorcycleDataP;
    refreshFields();
};

void views::MotorcycleView::refreshFields() {

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
