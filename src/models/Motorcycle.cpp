
// Implementation of the Motorcycle class for the vehicle rental system

#include "models/Motorcycle.h"

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

// Constructs a Motorcycle object with full initialization
models::Motorcycle::Motorcycle(
    // QObject parent
    QObject *parent,
    const models::MotorcycleData motorcycleDataP
):
    Vehicle(
        parent,
        motorcycleDataP
    ),
    data(motorcycleDataP) {

};

const models::MotorcycleData* models::Motorcycle::getVehicleData() const {
    return &data;
};

// Gets the engine capacity
int models::Motorcycle::getEngineCapacityCC() const {
    return data.engineCapacityCC;
};

// Sets the engine capacity
void models::Motorcycle::setEngineCapacityCC(const int newEngineCapacityCC) {

    if (data.engineCapacityCC == newEngineCapacityCC) {
        return;
    };

    data.engineCapacityCC = newEngineCapacityCC;
    emit vehicleUpdated(getVehicleId());

};

// Converts engine capacity to QString
QString models::Motorcycle::getEngineCapacityCCAsQString() const {
    return QString::number(getEngineCapacityCC());
};

// Serializes the Motorcycle object into a pipe-separated string
QString models::Motorcycle::toQString() const {

    QString str = QString("%1|%2|%3|%4|%5|%6|%7")
        .arg(
            getVehicleTypeIdAsQString(),
            getVehicleIdAsQString(),
            getBrand(),
            getModel(),
            getPricePerDayAsQString(),
            getIsRentedAsQString(),
            getEngineCapacityCCAsQString()
        );

    return str;

};

// Creates a deep copy of the Motorcycle object
models::Vehicle* models::Motorcycle::clone() const {

    return new models::Motorcycle(
        nullptr,
        data
    );

};

// Writes the Motorcycle object to a text stream
void models::Motorcycle::writeToStream(QTextStream& out) const {
    out << toQString();
};

// Reads a Motorcycle object from a text stream
void models::Motorcycle::readFromStream(QTextStream& in) {

    const QString line = in.readLine();

    const QStringList fields = line.split('|');

    if (fields.size() < 7) {
        qDebug() << "Failed to read line from input stream";
        return;
    };

    bool ok = false;

    // Vehicle data fields
    data.vehicleTypeId = models::VehicleTypeId::motorCycle;
    data.vehicleId = fields.at(1).toLongLong(&ok);
    if (!ok) {
        qFatal() << "Error: failed to convert vehicle id QString to long long. Consider checking the file";
        return;
    };
    data.brand = fields.at(2);
    data.model = fields.at(3);
    data.pricePerDay = fields.at(4).toDouble(&ok);
    if (!ok) {
        qFatal() << "Error: failed to convert vehicle id QString to double. Consider checking the file";
        return;
    };
    data.isRented = models::Vehicle::isRentedQStringToBool(fields.at(5));

    // Car data fields
    data.engineCapacityCC = fields.at(6).toInt();

};
