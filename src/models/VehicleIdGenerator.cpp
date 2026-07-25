
#include "models/models.h"

#include <QString>
#include <QTextStream>

// Validates a numeric vehicle ID
bool models::VehicleIdGenerator::isVehicleIdValid(const long long vehicleId) {
    return vehicleId >= 0;
};

// Validates a string vehicle ID
bool models::VehicleIdGenerator::isVehicleIdValid(const QString& vehicleId) {
    return vehicleId.contains(QRegularExpression("^\\d+$"));
};

// Converts the current vehicle ID to QString format
QString models::VehicleIdGenerator::vehicleIdToQString() const {
    return QString::number(currentVehicleId);
};

// Gets the current vehicle ID file location
const QString& models::VehicleIdGenerator::getCurrentIdFileLocation() const {
    return currentVehicleIdFileLocation;
};

// Gets the current vehicle ID counter
long long models::VehicleIdGenerator::getCurrentVehicleId() const {
    return currentVehicleId;
};

// Sets the current vehicle ID counter
void models::VehicleIdGenerator::setCurrentVehicleId(const long long newCurrentVehicleId) {
    currentVehicleId = newCurrentVehicleId;
};

// Decrements the current vehicle ID counter
void models::VehicleIdGenerator::decrementCurrentVehicleId() {
    currentVehicleId--;
};

// Increments the current vehicle ID counter
void models::VehicleIdGenerator::incrementCurrentVehicleId() {
    currentVehicleId++;
};

/**
 * Loads the current vehicle ID from persistent storage
 *
 * Reads the vehicle ID from the file specified by
 * `currentVehicleIdFileLocation`
 *
 * The file and directory path are automatically created if necessary
 *
 * Newly created files are initialized with a default vehicle ID of `0`
 */
void models::VehicleIdGenerator::saveCurrentVehicleId(bool& ok) {

    // Ensures path and file exist
    VehiclePersistence::ensurePathAndFileExist(
        currentVehicleIdFileLocation,
        QString("0"),
        ok
    );

    if (!ok) {
        qDebug() << "Failed to save vehicle id";
        return;
    };

    QFile currentIdFile(currentVehicleIdFileLocation);

    if (!currentIdFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Failed to open file:" << currentIdFile.errorString();
        ok = false;
        return;
    };

    QTextStream out(&currentIdFile);

    out << currentVehicleId;

    out.flush();
    currentIdFile.close();

    ok = true;

};

/**
 * Loads the current vehicle ID from persistent storage
 *
 * Reads the vehicle ID from the file specified by
 * `currentVehicleIdFileLocation`
 *
 * The file and directory path are automatically created if necessary
 * 
 * Newly created files are initialized with a default vehicle ID of `0`
 */
void VehiclePersistence::loadCurrentVehicleId(bool& ok) {

    // Ensures path and file exist
    VehiclePersistence::ensurePathAndFileExist(
        currentVehicleIdFileLocation,
        QString("0"),
        ok
    );

    if (!ok) {
        qDebug() << "Failed to load current vehicle id";
        return;
    };

    QFile currentIdFile(currentVehicleIdFileLocation);

    // Open file
    if (!currentIdFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << currentIdFile.errorString();
        ok = false;
        return;
    };

    // Extract currentVehicleId
    QTextStream inp(&currentIdFile);
    inp >> currentVehicleId;

    // Close the file
    currentIdFile.close();

    ok = true;

};
