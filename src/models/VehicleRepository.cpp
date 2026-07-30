
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

models::Vehicles::iterator models::VehicleRepository::findVehicleIteratorById(
    const long long vehicleId
) {

    for (auto it = vehicles.begin(); it != vehicles.end(); ++it) {
        auto vehicle = *it;
        if (vehicle->getVehicleId() == vehicleId) {
            return it;
        };
    };

    return vehicles.end();

};

void models::VehicleRepository::setVehicleIsRented(
    const long long vehicleId,
    const bool newIsRented
) {

    auto vehicle = searchVehicleById(vehicleId);

    if (vehicle == nullptr) {
        qDebug() << QString("Failed to find vehicle with id '%1' to sent is rented to '%2'").arg(vehicleId, newIsRented);
        return;
    };

    if (vehicle->getIsRented() == newIsRented) {
        qDebug() << QString("Vehicle with id '%1' isRented attribute is already set to '%2'").arg(vehicleId, newIsRented);
        return;
    };

    vehicle->setIsRented(newIsRented);

    bool ok;

    vehiclesPersistence.saveVehicles(vehicles, ok);

    if (!ok) {
        qDebug()
            << QString("Failed to set isRented to '%1' on vehicle with id '%2' because failed to save vehicles").arg(newIsRented, vehicleId);
        vehicle->setIsRented(!newIsRented);
        return;
    };

    qDebug()
        << QString("Successfully set isRented to '%1' on vehicle with id '%2'").arg(newIsRented, vehicleId);

    emit vehiclesChanged();
    emit vehicleUpdated(vehicleId);
    if (newIsRented) {
        emit vehicleRented(vehicleId);
    } else {
        emit vehicleReturned(vehicleId);
    };

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

    Vehicle* vehicle = searchVehicleById(vehicleData.vehicleId);

    if (vehicle == nullptr) {
        qDebug() << "Vehicle not found";
        return;
    };

    vehicle->setVehicleData(vehicleData);

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
void models::VehicleRepository::removeVehicleById(
    const long long vehicleId
) {

    auto it = findVehicleIteratorById(vehicleId);

    if (it == vehicles.end()) {
        qDebug() << "Vehicle to remove was not found in list";
        return;
    };

    auto vehicle = *it;

    vehicles.erase(it);
    delete vehicle;

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
    setVehicleIsRented(vehicleId, true);
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
    setVehicleIsRented(vehicleId, false);
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
    auto it = findVehicleIteratorById(vehicleId);
    if (it == vehicles.end()) {
        return nullptr;
    };
    return *it;
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
