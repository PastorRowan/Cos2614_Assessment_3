

// File input/output and persistence implementation for the VehiclesFile class

#include "VehiclesFile/VehiclesFile.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

/*
 * Ensures that a file and its parent directory path exist
 *
 * If the file does not exist:
 * - Missing directories are created
 * - The file is created
 * - Initial contents are written into the file
 *
 * Existing files are left unchanged
 */
void VehiclesFile::ensurePathAndFileExist(
    const QString& path,
    const QString& initialContents,
    bool& ok
) {

    QFile file(path);

    if (!file.exists()) {

        QFileInfo fileInfo(path);

        // Create directory path
        QDir dir;
        if (!dir.mkpath(fileInfo.path())) {
            qDebug() << "Failed to create directory:" << fileInfo.path();
            ok = false;
            return;
        };

        // Create empty file
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Failed to create file:" << file.errorString();
            ok = false;
            return;
        };

        // Write starting value
        QTextStream out(&file);
        out << initialContents;

        // Close file
        file.close();

    };

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
void VehiclesFile::saveCurrentVehicleId(bool& ok) {

    // Ensures path and file exist
    VehiclesFile::ensurePathAndFileExist(
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
void VehiclesFile::loadCurrentVehicleId(bool& ok) {

    // Ensures path and file exist
    VehiclesFile::ensurePathAndFileExist(
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
 * Saves all vehicles in the internal collection to persistent storage
 *
 * Each vehicle is serialized using the overloaded stream insertion operator
 * (`operator<<`) implemented by the corresponding vehicle class
 *
 * Vehicles are written line-by-line into the storage file
 *
 * Existing file contents are overwritten
 */
void VehiclesFile::saveVehiclesQVector(bool& ok) {

    // Ensures path and file exist
    VehiclesFile::ensurePathAndFileExist(
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

    for (unsigned int i = 0; i < vehiclesQVector.size(); ++i) {

        out << *vehiclesQVector[i];

        if (i != vehiclesQVector.size() - 1) {
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
 * - Stores reconstructed vehicles inside `vehiclesQVector`
 *
 * Supported vehicle types:
 * - vehicles::Car
 * - vehicles::Motorcycle
 *
 * Invalid file contents or unsupported type IDs will cause loading to fail.
 *
 * Dynamically allocated vehicle objects are owned by `vehiclesQVector`
 * and must later be deleted to avoid memory leaks.
 */
void VehiclesFile::loadVehiclesQVector(bool& ok) {

    // Ensures path and file exist
    VehiclesFile::ensurePathAndFileExist(
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
            qDebug() << QString(R"(A line is invalid in '%1')").arg(vehiclesFileLocation);
            ok = false;
            return;
        };

        const QString typeId = fields[0];

        vehicles::Vehicle* vehiclePointer = nullptr;

        switch (static_cast<vehicles::TypeId>(typeId.toInt())) {

            case vehicles::TypeId::car:
                vehiclePointer = new vehicles::Car();
                break;

            case vehicles::TypeId::motorCycle:
                vehiclePointer = new vehicles::Motorcycle();
                break;
        
            default:
                qDebug() << QString("invalid type id '%1' exists in '%2'")
                    .arg(
                        typeId,
                        vehiclesFileLocation
                    );
                vehiclesFile.close();
                ok = false;
                return;
                break;

        };

        QTextStream lineStream(&line, QIODevice::ReadOnly);

        lineStream >> *vehiclePointer;

        vehiclesQVector.push_back(vehiclePointer);

    };

    vehiclesFile.close();
    ok = true;

};
