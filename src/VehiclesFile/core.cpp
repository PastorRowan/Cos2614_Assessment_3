
// Implementation of the VehiclesFile class

#include "VehiclesFile/VehiclesFile.h"

#include <QObject>
#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include <QCoreApplication>

// Constructs a VehiclesFile object and loads persisted vehicle data
VehiclesFile::VehiclesFile(
    const QString vehiclesFileLocationParameter,
    const QString currentVehicleIdFileLocationParameter,
    QObject* parent
):
    QObject(parent),
    vehiclesFileLocation(QCoreApplication::applicationDirPath() + vehiclesFileLocationParameter),
    currentVehicleIdFileLocation(QCoreApplication::applicationDirPath() + currentVehicleIdFileLocationParameter) {

    bool ok = false;

    loadCurrentVehicleId(ok);

    if (!ok) {
        qFatal() << "Failed to load current vehicle id";
        return;
    };

    vehiclesQVector.reserve(currentVehicleId + 50);

    loadVehiclesQVector(ok);

    if (!ok) {
        qFatal() << "Failed to load vehiclesQVector";
        return;
    };

};

/**
 * Destructor for VehiclesFile.
 *
 * Releases all dynamically allocated vehicle objects stored in the internal
 * vehicle container
 */
VehiclesFile::~VehiclesFile() {
    destroyVehiclesQVector();
};

// Validates a numeric vehicle ID
bool VehiclesFile::isVehicleIdValid(const long long vehicleId) {
    return vehicleId >= 0;
};

// Validates a string vehicle ID
bool VehiclesFile::isVehicleIdValid(const QString& vehicleId) {
    return vehicleId.contains(QRegularExpression("^\\d+$"));
};

// Converts the current vehicle ID to QString format
QString VehiclesFile::vehicleIdToQString() const {
    return QString::number(currentVehicleId);
};

// Gets the vehicle data file location
const QString& VehiclesFile::getVehiclesFileLocation() const {
    return vehiclesFileLocation;
};

// Sets the vehicle data file location
void VehiclesFile::setVehiclesFileLocation(const QString vehiclesFileLocationP) {
    vehiclesFileLocation = vehiclesFileLocationP;
};

// Gets the current vehicle ID file location
const QString& VehiclesFile::getCurrentIdFileLocation() const {
    return currentVehicleIdFileLocation;
};

/**
 * Gets the internal vehicle collection
 *
 * Returns a constant reference to the internal vehicle QVector
 */
const VehiclesFile::VehiclesQVector& VehiclesFile::getVehiclesQVector() const {
    return vehiclesQVector;
};

/**
 * Destroys all vehicles stored in the internal collection
 *
 * Dynamically allocated vehicle objects are deleted and the collection is
 * cleared afterward
 */
void VehiclesFile::destroyVehiclesQVector() {

    for (unsigned int i = 0; i < vehiclesQVector.size(); i++) {
        delete vehiclesQVector[i];
    };

    vehiclesQVector.clear();

};

// Gets the current vehicle ID counter
long long VehiclesFile::getCurrentVehicleId() const {
    return currentVehicleId;
};

// Sets the current vehicle ID counter
void VehiclesFile::setCurrentVehicleId(const long long newCurrentVehicleId) {
    currentVehicleId = newCurrentVehicleId;
};

// Decrements the current vehicle ID counter
void VehiclesFile::decrementCurrentVehicleId() {
    currentVehicleId--;
};

// Increments the current vehicle ID counter
void VehiclesFile::incrementCurrentVehicleId() {
    currentVehicleId++;
};

// Increments and persists the current vehicle ID counter
void VehiclesFile::incrementAndSaveCurrentVehicleId(bool &ok) {
    incrementCurrentVehicleId();
    saveCurrentVehicleId(ok);
};

// Sets the current vehicle ID file location
void VehiclesFile::setCurrentIdFileLocation(const QString currentVehicleIdFileLocationP) {
    currentVehicleIdFileLocation = currentVehicleIdFileLocationP;
};
