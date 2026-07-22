
// Implementation of vehicle return functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>
#include <QDebug>

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
    const QString& vehicleId
) {

    for (unsigned int i = 0; i < vehiclesQVector.size(); i++) {

        if (vehiclesQVector[i]->getVehicleId() == vehicleId) {

            if (!vehiclesQVector[i]->getIsRented()) {
                qDebug() << QString("Vehicle '%1' is not rented out").arg(vehicleId);
            } else {

                bool newIsRented = false;

                vehiclesQVector[i]->setIsRented(newIsRented);

                bool ok;

                saveVehiclesQVector(ok);

                if (!ok) {
                    qDebug() << QString("Failed to rent vehicle '%1'").arg(vehicleId);
                    vehiclesQVector[i]->setIsRented(!newIsRented);
                    return;
                };

                emit vehiclesChanged();
                emit vehicleUpdated(vehicleId);
                emit vehicleReturned(vehicleId);

                qDebug() << QString("Successfully returned vehicle '%1'").arg(vehicleId);

            };

            return;

        };

    };

    qDebug() << "Vehicle with vehicle id does not exist";

};
