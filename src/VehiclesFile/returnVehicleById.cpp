
// Implementation of vehicle return functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>

/**
 * Returns a rented vehicle by its unique ID
 *
 * This function searches for a vehicle with the specified ID and:
 * - Checks if it exists
 * - Verifies that it is currently rented
 * - Marks it as not rented
 * - Saves the updated state to persistent storage
 *
 * If saving fails, the state change is reverted
 */
void VehiclesFile::returnVehicleById(
    const QString& vehicleId,
    QString& message
) {

    for (unsigned int i = 0; i < vehiclesQVector.size(); i++) {

        if (vehiclesQVector[i]->getVehicleId() != vehicleId) {
            continue;
        };

        if (!vehiclesQVector[i]->getIsRented()) {
            message = QString("Vehicle '%1' is not rented out").arg(vehicleId);
        } else {

            bool newIsRented = false;

            vehiclesQVector[i]->setIsRented(newIsRented);

            bool ok;

            saveVehiclesQVector(ok);

            if (!ok) {
                message = QString("Failed to rent vehicle '%1'").arg(vehicleId);
                vehiclesQVector[i]->setIsRented(!newIsRented);
                return;
            };

            message = QString("Successfully returned vehicle '%1'").arg(vehicleId);

        };

        return;

    };

};
