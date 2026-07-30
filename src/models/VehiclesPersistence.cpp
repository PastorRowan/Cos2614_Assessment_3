
#include "models/models.h"
#include "helpers/helpers.h"

#include <QFile>
#include <QDebug>
#include <QObject>
#include <QTextStream>

/**
 * Constructs a VehiclesPersistence object
 *
 * Initializes the persistence manager with the specified vehicle storage file
 *
 * vehiclesFileLocationP - The file used to store serialized vehicle data
 */
models::VehiclesPersistence::VehiclesPersistence(
    const QString vehiclesFileLocationP
):
    vehiclesFileLocation(vehiclesFileLocationP) {

};

// Gets the vehicle data file location
const QString& models::VehiclesPersistence::getVehiclesFileLocation() const {
    return vehiclesFileLocation;
};

// Sets the vehicle data file location
void models::VehiclesPersistence::setVehiclesFileLocation(
    const QString vehiclesFileLocationP
) {
    vehiclesFileLocation = vehiclesFileLocationP;
};

/**
 * Saves all vehicles in the internal collection to persistent storage
 *
 * Each vehicle is serialized using the overloaded stream insertion operator
 * (`operator<<`) implemented by the corresponding vehicle class
 *
 * Vehicles are written line-by-line into the storage file
 *
 * Existing file contents are overwritten
 */
void models::VehiclesPersistence::saveVehicles(
    const models::Vehicles& vehicles,
    bool& ok
) {

    // Ensures path and file exist
    helpers::ensurePathAndFileExist(
        vehiclesFileLocation,
        QString(""),
        ok
    );

    if (!ok) {
        qDebug() << QString(R"(Failed to ensure file path exists '%1')").arg(vehiclesFileLocation);
        return;
    };

    QFile vehiclesFile(vehiclesFileLocation);

    if (!vehiclesFile.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Failed to open file:" << vehiclesFile.errorString();
        ok = false;
        return;
    };

    QTextStream out(&vehiclesFile);

    for (unsigned int i = 0; i < vehicles.size(); ++i) {

        out << *vehicles.at(i);

        if (i != vehicles.size() - 1) {
            out << '\n';
        };

    };

    out.flush();
    vehiclesFile.close();

    ok = true;

};

/**
 * Loads all vehicles from persistent storage into memory
 *
 * This function:
 * - Reads the vehicle storage file line-by-line
 * - Parses serialized vehicle records
 * - Detects the vehicle type using the stored type ID
 * - Dynamically creates the correct derived vehicle object
 * - Reconstructs object state using the overloaded stream extraction operator
 *   (`operator>>`).
 * - Stores reconstructed vehicles inside `vehicles`
 *
 * Supported vehicle types:
 * - models::Car
 * - models::Motorcycle
 *
 * Invalid file contents or unsupported type IDs will cause loading to fail.
 *
 * Dynamically allocated vehicle objects are owned by `vehicles`
 * and must later be deleted to avoid memory leaks.
 */
void models::VehiclesPersistence::loadVehicles(
    models::Vehicles& vehicles,
    bool& ok
) {

    // Ensures path and file exist
    helpers::ensurePathAndFileExist(
        vehiclesFileLocation,
        QString(""),
        ok
    );

    if (!ok) {
        qDebug() << "Failed to ensure path exists: " << vehiclesFileLocation;
        ok = false;
        return;
    };

    QFile vehiclesFile(vehiclesFileLocation);

    if (!vehiclesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << vehiclesFile.errorString();
        ok = false;
        return;
    };

    QTextStream inp(&vehiclesFile);
    QString line;

    while (!inp.atEnd()) {

        line = inp.readLine();

        const QStringList fields = line.split('|');

        if (fields.size() <= 5) {
            qDebug() << QString("A line is invalid in '%1'").arg(vehiclesFileLocation);
            ok = false;
            return;
        };

        const QString vehicleTypeIdQString = fields.at(0);

        const int vehicleTypeIdInt = vehicleTypeIdQString.toInt(&ok);

        if (!ok) {
            qDebug() << QString("vehicle type id '%1' is invalid in file location '%2'").arg(vehicleTypeIdQString, vehiclesFileLocation);
            return;
        };

        models::Vehicle* vehiclePointer = nullptr;

        switch (static_cast<models::VehicleTypeId>(vehicleTypeIdInt)) {

            case models::VehicleTypeId::car:
                vehiclePointer = new models::Car();
                break;

            case models::VehicleTypeId::motorCycle:
                vehiclePointer = new models::Motorcycle();
                break;
        
            default:
                qDebug() << QString("invalid type id '%1' exists in '%2'")
                    .arg(
                        vehicleTypeIdQString,
                        vehiclesFileLocation
                    );
                vehiclesFile.close();
                ok = false;
                return;
                break;

        };

        QTextStream lineStream(&line, QIODevice::ReadOnly);

        lineStream >> *vehiclePointer;

        vehicles.push_back(vehiclePointer);

    };

    vehiclesFile.close();
    ok = true;

};

/**
 * Clears all persisted vehicle data
 *
 * This function is intended to remove all stored vehicle data from
 * persistent storage
 *
 * This function is currently not implemented
 */
void models::VehiclesPersistence::clear() {
    qDebug() << "NOT IMPLEMENTED YET";
};
