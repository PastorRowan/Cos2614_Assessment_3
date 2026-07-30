
#include "models/models.h"

#include <QString>
#include <QCoreApplication>
#include <QtAlgorithms>
#include <memory>
#include <QDebug>

/**
 * Constructs a VehicleRepository
 *
 * Initializes the vehicle ID generator and persistence manager using the
 * application's data files
 * Space is reserved in the internal vehicle
 * collection to reduce reallocations as vehicles are added
 *
 * parent - The parent QObject that owns this repository
 */
models::VehicleRepository::VehicleRepository(
    QObject* parent
):
    QObject(parent),
    vehicleIdGenerator(QCoreApplication::applicationDirPath() + QString("/files/vehicles.txt")),
    vehiclesPersistence(QCoreApplication::applicationDirPath() + QString("/files/currentVehicleId.txt")) {

    vehicles.reserve(vehicleIdGenerator.getCurrentVehicleId() + 50);

};

/**
 * Destroys all vehicles stored in the internal collection
 *
 * Dynamically allocated vehicle objects are deleted and the collection is
 * cleared afterward
 */
void models::VehicleRepository::destroyVehicles() {
    qDeleteAll(vehicles);
    vehicles.clear();
};

/**
 * Gets the internal vehicle collection
 *
 * Returns a constant reference to the internal vehicles list
 */
const models::Vehicles& models::VehicleRepository::getVehicles() const {
    return vehicles;
};

/**
 * Adds a new Car object to the vehicle collection and saves it to storage
 *
 * This function creates a new instance of `models::Car` using the provided
 * vehicle and car-specific attributes, appends it to the internal
 * `vehicles` container, and persists the updated collection
 *
 * If saving the vehicle collection fails, the newly created vehicle is removed
 * from the collection and an error message is returned
 *
 * After successfully saving the collection, the function increments and saves
 * the current vehicle ID counter to ensure future vehicles receive unique IDs
 */
void models::VehicleRepository::addVehicle(
    const models::VehicleData& vehicleData
) {

    qDebug() << "VehicleRepository addVehicle is running with vehicleData.brand: " << vehicleData.brand;

    models::Vehicle* newVehicle = nullptr;

    switch (vehicleData.vehicleTypeId) {

        case models::VehicleTypeId::car: {
            auto carData = static_cast<const models::CarData&>(vehicleData);
            models::CarData copy = carData;
            copy.vehicleId = vehicleIdGenerator.generateId();
            newVehicle = new models::Car(this, copy);
            break;
        };

        case models::VehicleTypeId::motorCycle: {
            auto motorcycleData = static_cast<const models::MotorcycleData&>(vehicleData);
            models::MotorcycleData copy = motorcycleData;
            copy.vehicleId = vehicleIdGenerator.generateId();
            newVehicle = new models::Motorcycle(this, copy);
            break;
        };

        default: {
            qDebug() << "Unknown vehicle type";
            return;
        };

    };

    vehicles.push_back(newVehicle);

    bool ok;
    vehiclesPersistence.saveVehicles(vehicles, ok);

    if (!ok) {
        qDebug() << QString("Failed to add vehicle '%1' because failed to save vehicles").arg(newVehicle->toQString());
        delete vehicles.last();
        vehicles.pop_back();
        return;
    };

    qDebug() << QString("Successfully added vehicle '%1'").arg(newVehicle->toQString());

    emit vehiclesChanged();
    emit vehicleAdded(newVehicle->getVehicleId());

};

/**
 * Updates an existing vehicle
 *
 * Searches for the vehicle matching the supplied vehicle ID, replaces its
 * stored data, and saves the updated repository to persistent storage
 *
 * If the vehicle cannot be found or the updated repository cannot be saved,
 * the update is aborted
 *
 * On success, the vehiclesChanged() and vehicleUpdated() signals are emitted
 *
 * vehicleData - The updated vehicle data
 */
void models::VehicleRepository::updateVehicle(
    const models::VehicleData& vehicleData
) {

    qDebug()
        << "vehicleDataP:"
        << "type =" << static_cast<int>(vehicleData.vehicleTypeId)
        << ", id =" << vehicleData.vehicleId
        << ", brand =" << vehicleData.brand
        << ", model =" << vehicleData.model
        << ", pricePerDay =" << vehicleData.pricePerDay
        << ", isRented =" << vehicleData.isRented;

    Vehicle* vehicle = searchVehicleById(vehicleData.vehicleId);

    qDebug() << "Found Vehicle update: " << vehicle->toQString();

    if (vehicle == nullptr) {
        qDebug() << "Vehicle not found";
        return;
    };

    qDebug() << "Vehicle before update: " << vehicle->toQString();

    vehicle->setVehicleData(vehicleData);

    qDebug() << "Vehicle after update: " << vehicle->toQString();

    bool ok;
    vehiclesPersistence.saveVehicles(vehicles, ok);

    if (!ok) {
        qDebug() << "Failed to save updated vehicle";
        return;
    };

    emit vehiclesChanged();
    emit vehicleUpdated(vehicleData.vehicleId);

};

/**
 * Removes a vehicle from the repository
 *
 * Searches for the specified vehicle, removes it from the collection,
 * destroys the object, and releases its memory
 *
 * If no matching vehicle exists, a debug message is logged
 *
 * vehicleId - The unique identifier of the vehicle to remove
 */
void models::VehicleRepository::removeVehicle(
    const long long vehicleId
) {

    for (unsigned int i = 0; i < vehicles.size(); ++i) {
        auto vehicle = vehicles.at(i);
        if (vehicle->getVehicleId() == vehicleId) {
            vehicles.remove(i);
            delete vehicle;
            return;
        };
    };

    qDebug() << "Vehicle not found in list";

};

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
void models::VehicleRepository::rentVehicleById(
    const long long vehicleId
) {

    for (unsigned int i = 0; i < vehicles.size(); i++) {

        if (vehicles[i]->getVehicleId() != vehicleId) {
            continue;
        };

        if (vehicles[i]->getIsRented()) {
            qDebug() << QString("Vehicle '%1' is already rented").arg(vehicleId);
        } else {

            bool newIsRented = true;

            vehicles[i]->setIsRented(newIsRented);

            bool ok;

            vehiclesPersistence.saveVehicles(vehicles, ok);

            if (!ok) {
                qDebug() << QString("Failed to rent vehicle '%1'").arg(vehicleId);
                vehicles[i]->setIsRented(!newIsRented);
                return;
            };

            qDebug() << QString("Successfully rented vehicle '%1'").arg(vehicleId);

            emit vehiclesChanged();
            emit vehicleUpdated(vehicleId);
            emit vehicleRented(vehicleId);

        };

        return;

    };

    qDebug() << QString("Vehicle with id '%1' does not exist").arg(vehicleId);

};

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
void models::VehicleRepository::returnVehicleById(
    const long long vehicleId
) {

    for (unsigned int i = 0; i < vehicles.size(); i++) {

        if (vehicles[i]->getVehicleId() == vehicleId) {

            if (!vehicles[i]->getIsRented()) {
                qDebug() << QString("Vehicle '%1' is not rented out").arg(vehicleId);
            } else {

                bool newIsRented = false;

                vehicles[i]->setIsRented(newIsRented);

                bool ok;

                vehiclesPersistence.saveVehicles(vehicles, ok);

                if (!ok) {
                    qDebug() << QString("Failed to rent vehicle '%1'").arg(vehicleId);
                    vehicles[i]->setIsRented(!newIsRented);
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

/**
 * Searches for a vehicle by its unique ID
 *
 * Iterates through the internal vehicle collection and returns a pointer
 * to the first vehicle matching the provided ID
 *
 * This function does not modify the vehicle collection
 */
models::Vehicle* models::VehicleRepository::searchVehicleById(
    const long long vehicleId
) {

    for (unsigned int i = 0; i < vehicles.size(); i++) {
        if (vehicles[i]->getVehicleId() == vehicleId) {
            return vehicles[i];
        };
    };

    return nullptr;

};

/**
  * Removes all vehicles in the collection by:
  * Emptying the vehicles list
  * Saving the empty vehicles list
  */
void models::VehicleRepository::clear() {

    destroyVehicles();

    bool ok = false;

    vehiclesPersistence.saveVehicles(vehicles, ok);

    if (!ok) {
        qDebug() << "Failed to save vehicles list while clearing vehicles";
        return;
    };

};

/**
 * Handles an add-vehicle request
 *
 * Convenience slot that forwards a shared VehicleData object to addVehicle()
 *
 * vehicleData - Shared pointer containing the vehicle data
 */
void models::VehicleRepository::handleAddVehicle(
    std::shared_ptr<const models::VehicleData> vehicleData
) {

    qDebug() << "VehicleRepository handleAddVehicle is running with vehicleData->brand: " << vehicleData->brand;

    addVehicle(*vehicleData);

};

/**
 * Handles an update-vehicle request
 *
 * Convenience slot that forwards a shared VehicleData object to
 * updateVehicle()
 *
 * vehicleData - Shared pointer containing the updated vehicle data
 */
void models::VehicleRepository::handleUpdateVehicle(
    std::shared_ptr<const models::VehicleData> vehicleData
) {
    updateVehicle(*vehicleData);
};
