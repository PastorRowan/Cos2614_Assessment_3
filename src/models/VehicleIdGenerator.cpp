
#include "models/models.h"
#include "helpers/helpers.h"

#include <QString>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QDebug>

/**
 * Constructs a VehicleIdGenerator
 *
 * Initializes the generator using the specified file location and loads the
 * current vehicle ID from persistent storage
 *
 * If the current vehicle ID cannot be loaded, the application terminates
 *
 * currentVehicleIdFileLocationP - The file used to persist the current
 * vehicle ID counter
 */
models::VehicleIdGenerator::VehicleIdGenerator(
    const QString currentVehicleIdFileLocationP
):
    currentVehicleIdFileLocation(currentVehicleIdFileLocationP) {

    bool ok = false;

    loadCurrentVehicleId(ok);

    if (!ok) {
        qFatal() << "Error: failed to load current vehicle id";
    };

};

// Validates a numeric vehicle ID
bool models::VehicleIdGenerator::isVehicleIdValid(const long long vehicleId) {
    return vehicleId >= 1;
};

// Validates a string vehicle ID
bool models::VehicleIdGenerator::isVehicleIdValid(const QString& vehicleId) {
    return vehicleId.contains(QRegularExpression("^[1-9]\\d*$"));
};

// Gets the current vehicle ID file location
const QString& models::VehicleIdGenerator::getCurrentIdFileLocation() const {
    return currentVehicleIdFileLocation;
};

// Gets the current vehicle ID counter
long long models::VehicleIdGenerator::getCurrentVehicleId() const {
    return currentVehicleId;
};

// Converts the current vehicle ID to QString format
QString models::VehicleIdGenerator::getCurrentVehicleIdAsQString() const {
    return QString::number(currentVehicleId);
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
    helpers::ensurePathAndFileExist(
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
void models::VehicleIdGenerator::loadCurrentVehicleId(bool& ok) {

    // Ensures path and file exist
    helpers::ensurePathAndFileExist(
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

/**
 * Generates a new unique vehicle ID
 *
 * The internal vehicle ID counter is incremented and immediately written to
 * persistent storage to ensure uniqueness across application restarts
 *
 * If the updated counter cannot be saved, the application terminates
 *
 * The newly generated unique vehicle ID
 */
long long models::VehicleIdGenerator::generateId() {

    incrementCurrentVehicleId();

    bool ok = false;

    saveCurrentVehicleId(ok);

    if (!ok) {
        qFatal() << "Error failed to generate unique id because failed to save current id";
        return -1;
    };

    return currentVehicleId;

};
