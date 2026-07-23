
#include "VehiclesFile/VehiclesFile.h"

#include <QDebug>

/**
  * Removes a vehicle in the collection
  */
void VehiclesFile::removeVehicle(
    const QString& vehicleId
) {

    for (unsigned int i = 0; i < vehiclesQVector.size(); ++i) {
        auto vehicle = vehiclesQVector.at(i);
        if (vehicle->getVehicleId() == vehicleId) {
            vehiclesQVector.remove(i);
            delete vehicle;
            return;
        };
    };

    qDebug() << "Vehicle not found in list";

};
