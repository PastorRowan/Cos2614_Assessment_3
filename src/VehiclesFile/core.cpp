
// Implementation of the VehiclesFile class

#include "VehiclesFile/VehiclesFile.h"

#include <QString>
#include <QRegularExpression>
#include <QDebug>
#include <QCoreApplication>

// Constructs a VehiclesFile object and loads persisted vehicle data
VehiclesFile::VehiclesFile(
    const QString vehiclesFileLocationParameter,
    const QString currentVehicleIdFileLocationParameter,
    bool& ok
):
    vehiclesFileLocation(QCoreApplication::applicationDirPath() + vehiclesFileLocationParameter),
    currentVehicleIdFileLocation(QCoreApplication::applicationDirPath() + currentVehicleIdFileLocationParameter) {

    loadCurrentVehicleId(ok);

    if (!ok) {
        qDebug() << "Failed to load current vehicle id";
        ok = false;
        return;
    };

    vehiclesQVector.reserve(currentVehicleId + 50);

    loadVehiclesQVector(ok);

    if (!ok) {
        qDebug() << "Failed to load vehiclesQVector";
        ok = false;
        return;
    };

    ok = true;

};

// Copy constructor for VehiclesFile
VehiclesFile::VehiclesFile(
    const VehiclesFile& other,
    bool& ok
):
    VehiclesFile(
        other.getVehiclesFileLocation(),
        other.getCurrentIdFileLocation(),
        ok
    ) {

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

/**
 * Assignment operator for VehiclesFile
 *
 * Performs a deep copy of another VehiclesFile object by cloning all stored
 * vehicle objects
 *
 * Existing vehicle objects owned by this instance are destroyed before copying
 */
VehiclesFile& VehiclesFile::operator=(const VehiclesFile& rightVehicleFile) {

    if (this == &rightVehicleFile) {
        return *this;
    };

    bool ok;

    setVehiclesFileLocation(rightVehicleFile.getVehiclesFileLocation());
    setCurrentIdFileLocation(rightVehicleFile.getCurrentIdFileLocation());
    setCurrentVehicleId(rightVehicleFile.getCurrentVehicleId());

    destroyVehiclesQVector();

    VehiclesFile::VehiclesQVector& leftVehiclesQVector = vehiclesQVector;
    const VehiclesFile::VehiclesQVector& rightVehiclesQVector = rightVehicleFile.getVehiclesQVector();

    leftVehiclesQVector.reserve(rightVehiclesQVector.size() + 50);

    for (unsigned int i = 0; i < rightVehiclesQVector.size(); i++) {
        leftVehiclesQVector.push_back(rightVehiclesQVector[i]->clone());
    };

    return *this;

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
