
#include "views/MotorcycleView.h"
#include "vehicles/vehicles.h"

#include <QVBoxLayout>
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

    engineCapacityCCField->setVisible(hasVehicle);

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

    vBoxLayout = new QVBoxLayout(this);

    engineCapacityCCField = new QLineEdit(this);

    vBoxLayout->addWidget(engineCapacityCCField);

};
