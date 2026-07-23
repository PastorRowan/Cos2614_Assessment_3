
#include "VehiclesFile/VehiclesFile.h"

#include <QtAlgorithms>
#include <QDebug>

/**
  * Removes all vehicles in the collection by:
  * Emptying the vehicles list
  * Saving the empty vehicles list
  */
void VehiclesFile::clear() {

    // Clear vehiclesQVector
    qDeleteAll(vehiclesQVector);
    vehiclesQVector.clear();

    bool ok = false;

    saveVehiclesQVector(ok);

    if (!ok) {
        qDebug() << "Failed to save vehicles list";
        return;
    };

    setCurrentVehicleId(1);
    saveCurrentVehicleId(ok);

    if (!ok) {
        qDebug() << "Failed to save vehicles current vehicle id";
    };

};
