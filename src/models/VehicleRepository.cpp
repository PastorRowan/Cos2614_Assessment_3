
#include "models/models.h"

#include <QString>
#include <QCoreApplication>
#include <QtAlgorithms>
#include <QDebug>

// Constructs a VehicleRepository object and loads persisted vehicle data
models::VehicleRepository::VehicleRepository(
    const QString currentVehicleIdFileLocationP,
    const QString VehicleFileLocationP,
    QObject* parent
):
    QObject(parent),
    vehicleIdGenerator(QCoreApplication::applicationDirPath() + VehiclePersistenceLocationParameter),
    vehiclePersistence(QCoreApplication::applicationDirPath() + currentVehicleIdFileLocationParameter) {

    bool ok = false;

    loadCurrentVehicleId(ok);

    if (!ok) {
        qFatal() << "Failed to load current vehicle id";
        return;
    };

    vehicles.reserve(currentVehicleId + 50);

    loadvehicles(ok);

    if (!ok) {
        qFatal() << "Failed to load vehicles";
        return;
    };

};

/**
 * Destroys all vehicles stored in the internal collection
 *
 * Dynamically allocated vehicle objects are deleted and the collection is
 * cleared afterward
 */
void models::VehicleRepository::destroyvehicles() {

    for (unsigned int i = 0; i < vehicles.size(); i++) {
        delete vehicles[i];
    };

    vehicles.clear();

};

/**
 * Destructor for VehiclePersistence.
 *
 * Releases all dynamically allocated vehicle objects stored in the internal
 * vehicle container
 */
models::VehicleRepository::~VehicleRepository() {
    destroyvehicles();
};

/**
 * Gets the internal vehicle collection
 *
 * Returns a constant reference to the internal vehicle QVector
 */
const models::VehicleRepository::vehicles& models::VehicleRepository::getvehicles() const {
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
void models::VehicleRepository::addCar(
    const models::CarData carData
) {

    models::Vehicle*
    newVehicle = new models::Car(
        this,
        carData
    );

    vehicles.push_back(newVehicle);

    bool ok;

    savevehicles(ok);

    if (!ok) {
        qDebug() << QString("Failed to add vehicle because failed to save vehicles: %1").arg(newVehicle->toQString());
        delete vehicles.last();
        vehicles.pop_back();
        return;
    };

    incrementAndSaveCurrentVehicleId(ok);

    if (!ok) {
        qDebug() << QString("Failed to add vehicle because failed to increment and save current vehicle id: %1").arg(newVehicle->toQString());
        delete vehicles.last();
        vehicles.pop_back();
        return;
    };

    qDebug() << QString("Successfully added vehicle: %1").arg(newVehicle->toQString());

    emit vehiclesChanged();
    emit vehicleAdded(newVehicle->getVehicleId());

};

/**
 * Adds a new Motorcycle object to the vehicle collection and saves it to storage
 *
 * This function creates a new instance of `models::Motorcycle` using the
 * provided vehicle and motorcycle-specific attributes, appends it to the
 * internal `vehicles` container, and persists the updated collection
 *
 * If saving the vehicle collection fails, the newly created motorcycle is
 * removed from the collection and an error message is returned
 *
 * After successfully saving the collection, the function increments and saves
 * the current vehicle ID counter to ensure future vehicles receive unique IDs
 */
void models::VehicleRepository::addMotorcycle(
    const models::CarData motorcycleData
) {

    models::Vehicle* newVehicle =
        new models::Motorcycle(
            this,
            motorcycleData
        )
    ;

    vehicles.push_back(newVehicle);

    bool ok;

    savevehicles(
        ok
    );

    if (!ok) {
        qDebug() << QString("Failed to add vehicle: %1").arg(newVehicle->toQString());
        delete vehicles.last();
        vehicles.pop_back();
        return;
    };

    incrementAndSaveCurrentVehicleId(ok);

    if (!ok) {
        qDebug() << QString("Failed to save currentVehicleId vehicle: %1").arg(currentVehicleId);
        return;
    };

    qDebug() << QString("Successfully added vehicle: %1").arg(newVehicle->toQString());

    emit vehiclesChanged();
    emit vehicleAdded(newVehicle->getVehicleId());

};

/**
  * Removes a vehicle in the collection
  */
void models::VehicleRepository::removeVehicle(
    const QString& vehicleId
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
    const QString& vehicleId
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

            savevehicles(ok);

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
    const QString& vehicleId
) {

    for (unsigned int i = 0; i < vehicles.size(); i++) {

        if (vehicles[i]->getVehicleId() == vehicleId) {

            if (!vehicles[i]->getIsRented()) {
                qDebug() << QString("Vehicle '%1' is not rented out").arg(vehicleId);
            } else {

                bool newIsRented = false;

                vehicles[i]->setIsRented(newIsRented);

                bool ok;

                savevehicles(ok);

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
    const QString& vehicleId
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

    // Clear vehicles
    qDeleteAll(vehicles);
    vehicles.clear();

    bool ok = false;

    savevehicles(ok);

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

// Increments and persists the current vehicle ID counter
void models::VehicleRepository::incrementAndSaveCurrentVehicleId(bool &ok) {
    incrementCurrentVehicleId();
    saveCurrentVehicleId(ok);
};

// Sets the current vehicle ID file location
void models::VehicleRepository::setCurrentIdFileLocation(const QString currentVehicleIdFileLocationP) {
    currentVehicleIdFileLocation = currentVehicleIdFileLocationP;
};

void models::VehiclePersistence::handleVehicleUpdated(const QString vehicleId) {
    emit vehicleUpdated(vehicleId);
};
