
// Implementation of the addCar functionality for VehiclesFile

#include "VehiclesFile/VehiclesFile.h"

#include <QString>
#include <QDebug>

/**
 * Adds a new Car object to the vehicle collection and saves it to storage
 *
 * This function creates a new instance of `vehicles::Car` using the provided
 * vehicle and car-specific attributes, appends it to the internal
 * `vehiclesQVector` container, and persists the updated collection
 *
 * If saving the vehicle collection fails, the newly created vehicle is removed
 * from the collection and an error message is returned
 *
 * After successfully saving the collection, the function increments and saves
 * the current vehicle ID counter to ensure future vehicles receive unique IDs
 */
void VehiclesFile::addCar(

    // Vehicle attributes
    const QString brandP,
    const QString modelP,
    const double pricePerDayP,

    // Car attributes
    const int numberOfDoorsP,
    const int numberOfSeatsP

) {

    vehicles::Vehicle*
    newVehicle = new vehicles::Car(
        vehicleIdToQString(),
        brandP,
        modelP,
        pricePerDayP,
        false,
        numberOfDoorsP,
        numberOfSeatsP
    );

    vehiclesQVector.push_back(newVehicle);

    bool ok;

    saveVehiclesQVector(ok);

    if (!ok) {
        qDebug() << QString("Failed to add vehicle because failed to save vehiclesQVector: %1").arg(newVehicle->toQString());
        delete vehiclesQVector.last();
        vehiclesQVector.pop_back();
        return;
    };

    incrementAndSaveCurrentVehicleId(ok);

    if (!ok) {
        qDebug() << QString("Failed to add vehicle because failed to increment and save current vehicle id: %1").arg(newVehicle->toQString());
        delete vehiclesQVector.last();
        vehiclesQVector.pop_back();
        return;
    };

    qDebug() << QString("Successfully added vehicle: %1").arg(newVehicle->toQString());

    emit vehiclesChanged();
    emit vehicleAdded(newVehicle->getVehicleId());

};
