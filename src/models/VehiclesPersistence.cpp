
#include "models/models.h"

// Gets the vehicle data file location
const QString& VehiclePersistence::getVehiclesFileLocation() const {
    return VehiclePersistenceLocation;
};

// Sets the vehicle data file location
void VehiclePersistence::setVehiclesFileLocation(const QString VehiclePersistenceLocationP) {
    VehiclePersistenceLocation = VehiclePersistenceLocationP;
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
void VehiclePersistence::savevehicles(bool& ok) {

    // Ensures path and file exist
    VehiclePersistence::ensurePathAndFileExist(
        VehiclePersistenceLocation,
        QString(""),
        ok
    );

    if (!ok) {
        qDebug() << QString(R"(Failed to ensure file path exists '%1')").arg(VehiclePersistenceLocation);
        return;
    };

    QFile VehiclePersistence(VehiclePersistenceLocation);

    if (!VehiclePersistence.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qDebug() << "Failed to open file:" << VehiclePersistence.errorString();
        ok = false;
        return;
    };

    QTextStream out(&VehiclePersistence);

    for (unsigned int i = 0; i < vehicles.size(); ++i) {

        out << *vehicles[i];

        if (i != vehicles.size() - 1) {
            out << '\n';
        };

    };

    out.flush();
    VehiclePersistence.close();

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
void VehiclePersistence::loadvehicles(bool& ok) {

    // Ensures path and file exist
    VehiclePersistence::ensurePathAndFileExist(
        VehiclePersistenceLocation,
        QString(""),
        ok
    );

    if (!ok) {
        qDebug() << "Failed to ensure path exists: " << VehiclePersistenceLocation;
        ok = false;
        return;
    };

    QFile VehiclePersistence(VehiclePersistenceLocation);

    if (!VehiclePersistence.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file:" << VehiclePersistence.errorString();
        ok = false;
        return;
    };

    QTextStream inp(&VehiclePersistence);
    QString line;

    while (!inp.atEnd()) {

        line = inp.readLine();

        const QStringList fields = line.split('|');

        if (fields.size() <= 5) {
            qDebug() << QString(R"(A line is invalid in '%1')").arg(VehiclePersistenceLocation);
            ok = false;
            return;
        };

        const QString VehicleTypeId = fields[0];

        models::Vehicle* vehiclePointer = nullptr;

        switch (static_cast<models::VehicleTypeId>(VehicleTypeId.toInt())) {

            case models::VehicleTypeId::car:
                vehiclePointer = new models::Car();
                break;

            case models::VehicleTypeId::motorCycle:
                vehiclePointer = new models::Motorcycle();
                break;
        
            default:
                qDebug() << QString("invalid type id '%1' exists in '%2'")
                    .arg(
                        VehicleTypeId,
                        VehiclePersistenceLocation
                    );
                VehiclePersistence.close();
                ok = false;
                return;
                break;

        };

        QTextStream lineStream(&line, QIODevice::ReadOnly);

        lineStream >> *vehiclePointer;

        vehiclePointer->setParent(this);

        QObject::connect(
            vehiclePointer,
            &models::Vehicle::vehicleUpdated,
            this,
            &VehiclePersistence::handleVehicleUpdated
        );

        vehicles.push_back(vehiclePointer);

    };

    VehiclePersistence.close();
    ok = true;

};
