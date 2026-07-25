
// Implementation of the Motorcycle class for the vehicle rental system

#include "vehicles/Motorcycle.h"

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QStringList>

// Constructs a Motorcycle object with full initialization
models::Motorcycle::Motorcycle(
    // QObject parent
    QObject *parent,
    MotorcycleData motorcycleDataP
):
    Vehicle(
        parent,
        motorcycleDataP
    ),
    data(motorcycleDataP) {

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
QString models::Motorcycle::engineCapacityCCToQString() const {
    return QString::number(getEngineCapacityCC());
};

// Serializes the Motorcycle object into a pipe-separated string
QString models::Motorcycle::toQString() const {

    QString str = QString("%1|%2|%3|%4|%5|%6|%7")
        .arg(
            VehicleTypeIdToQString(),
            getVehicleId(),
            getBrand(),
            getModel(),
            pricePerDayToQString(),
            isRentedToQString(),
            engineCapacityCCToQString()
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

    // Vehicle data fields
    data.VehicleTypeId = models::VehicleTypeId::motorCycle;
    data.vehicleId = fields.at(1);
    data.brand = fields.at(2);
    data.model = fields.at(3);
    data.pricePerDay = fields.at(4).toDouble();
    data.isRented = models::Vehicle::isRentedQStringToBool(fields.at(5));

    // Car data fields
    data.engineCapacityCC = fields.at(6).toInt();

};
