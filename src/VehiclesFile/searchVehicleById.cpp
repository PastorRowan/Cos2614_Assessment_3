
// Implementation of vehicle search functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>

/**
 * Searches for a vehicle by its unique ID
 *
 * Iterates through the internal vehicle collection and returns a pointer
 * to the first vehicle matching the provided ID
 *
 * This function does not modify the vehicle collection
 */
const vehicles::Vehicle* VehiclesFile::searchVehicleById(
    const QString& vehicleId
) const {

    for (unsigned int i = 0; i < vehiclesQVector.size(); i++) {
        if (vehiclesQVector[i]->getVehicleId() == vehicleId) {
            return vehiclesQVector[i];
        };
    };

    return nullptr;

};
