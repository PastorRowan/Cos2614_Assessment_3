
// Implementation of the addMotorcycle functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>

/**
 * Adds a new Motorcycle object to the vehicle collection and saves it to storage
 *
 * This function creates a new instance of `vehicles::Motorcycle` using the
 * provided vehicle and motorcycle-specific attributes, appends it to the
 * internal `vehiclesQVector` container, and persists the updated collection
 *
 * If saving the vehicle collection fails, the newly created motorcycle is
 * removed from the collection and an error message is returned
 *
 * After successfully saving the collection, the function increments and saves
 * the current vehicle ID counter to ensure future vehicles receive unique IDs
 */void VehiclesFile::addMotorcycle(

    // Vehicle attributes
    const QString brandP,
    const QString modelP,
    const double pricePerDayP,

    // Car attributes
    const int engineCapacityCCP,

    // Output message indicating success or failure
    QString& message

) {

    vehicles::Vehicle* newVehicle =
        new vehicles::Motorcycle(
            vehicleIdToQString(),
            brandP,
            modelP,
            pricePerDayP,
            false,
            engineCapacityCCP
        )
    ;

    vehiclesQVector.push_back(newVehicle);

    bool ok;

    saveVehiclesQVector(
        ok
    );

    if (!ok) {
        message = QString("Failed to add vehicle:\n%1").arg(newVehicle->toQString());
        delete vehiclesQVector.last();
        vehiclesQVector.pop_back();
        return;
    };

    incrementAndSaveCurrentVehicleId(ok);

    if (!ok) {
        message = QString("Failed to save currentVehicleId vehicle:\n%1").arg(currentVehicleId);
        return;
    };

    message = QString("Successfully added vehicle:\n%1").arg(newVehicle->toQString());

};
