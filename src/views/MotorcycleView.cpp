
#include "views/MotorcycleView.h"
#include "vehicles/vehicles.h"

#include <QFormLayout>
#include <QLineEdit>

const vehicles::Motorcycle* views::MotorcycleView::getMotorcycle() const {
    return motorcycle;
};

void views::MotorcycleView::setMotorcycle(vehicles::Motorcycle* newMotorcycle) {
    motorcycle = newMotorcycle;
    refreshFields();
};

void views::MotorcycleView::refreshFields() {

    bool hasVehicle = (getMotorcycle() != nullptr);

    setEnabled(hasVehicle);

    if (!hasVehicle) {
        engineCapacityCCField->clear();
    } else {
        engineCapacityCCField->setText(getMotorcycle()->engineCapacityCCToQString());
    };

};

views::MotorcycleView::MotorcycleView(
    QWidget *parent,
    vehicles::Motorcycle* motorcycleP
):
    QWidget(parent),
    motorcycle(motorcycleP) {

    motorcycleFormLayout = new QFormLayout(this);

    engineCapacityCCField = new QLineEdit(this);

    motorcycleFormLayout->addRow("ENGINE_CAPACITY_CC", engineCapacityCCField);

};
