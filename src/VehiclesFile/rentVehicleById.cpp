
// Implementation of vehicle rental functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>

/**
 * Rents a vehicle by its ID
 *
 * This function searches for a vehicle with the specified ID and:
 * - Checks if it exists
 * - Ensures it is not already rented
 * - Marks it as rented
 * - Saves the updated state to persistent storage
 *
 * If saving fails, the rental change is reverted
 */
void VehiclesFile::rentVehicleById(
    const QString& vehicleId,
    QString& message
) {

    for (unsigned int i = 0; i < vehiclesQVector.size(); i++) {

        if (vehiclesQVector[i]->getVehicleId() != vehicleId) {
            continue;
        };

        if (vehiclesQVector[i]->getIsRented()) {
            message = QString("Vehicle '%1' is already rented").arg(vehicleId);
        } else {

            bool newIsRented = true;

            vehiclesQVector[i]->setIsRented(newIsRented);

            bool ok;

            saveVehiclesQVector(ok);

            if (!ok) {
                message = QString("Failed to rent vehicle '%1'").arg(vehicleId);
                vehiclesQVector[i]->setIsRented(!newIsRented);
                return;
            };

            message = QString("Successfully rented vehicle '%1'").arg(vehicleId);

        };

        return;

    };

    message = QString("Vehicle with id '%1' does not exist").arg(vehicleId);

    emit vehicleRented(vehicleId);
    emit vehicleUpdated(vehicleId);
    emit vehiclesChanged();

};
