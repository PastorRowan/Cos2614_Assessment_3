
// Implementation of the Car class for the vehicle rental system.

#include "models/Car.h"

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

// Constructs a Car object with full initialization
models::Car::Car(
    // QObject parent
    QObject *parent,
    const models::CarData carDataP
):
    Vehicle(
        parent,
        carDataP
    ),
    data(carDataP) {
    
};

const models::CarData* models::Car::getVehicleData() const {
    return &data;
};

// Gets the number of doors
int models::Car::getNumberOfDoors() const {
    return data.numberOfDoors;
};

// Sets the number of doors
void models::Car::setNumberOfDoors(const int newNumberOfDoors) {

    if (data.numberOfDoors == newNumberOfDoors) {
        return;
    };

    data.numberOfDoors = newNumberOfDoors;
    emit vehicleUpdated(getVehicleId());

};

// Converts number of doors to QString
QString models::Car::getNumberOfDoorsAsQString() const {
    return QString::number(getNumberOfDoors());
};

// Gets the number of seats
int models::Car::getNumberOfSeats() const {
    return data.numberOfSeats;
};

// Sets the number of seats
void models::Car::setNumberOfSeats(const int newNumberOfSeats) {

    if (data.numberOfSeats == newNumberOfSeats) {
        return;
    };

    data.numberOfSeats = newNumberOfSeats;
    emit vehicleUpdated(getVehicleId());

};

// Converts number of seats to QString
QString models::Car::getNumberOfSeatsAsQString() const {
    return QString::number(getNumberOfSeats());
};

// Serializes the Car object into a pipe-separated string
QString models::Car::toQString() const {

    QString str = QString("%1|%2|%3|%4|%5|%6|%7|%8")
        .arg(
            getVehicleTypeIdAsQString(),
            getVehicleIdAsQString(),
            getBrand(),
            getModel(),
            getPricePerDayAsQString(),
            getIsRentedAsQString(),
            getNumberOfDoorsAsQString(),
            getNumberOfSeatsAsQString()
        );

    return str;

};

// Creates a deep copy of the Car object
models::Vehicle* models::Car::clone() const {

    return new models::Car(
        nullptr,
        data
    );

};

// Writes the Car object to a text stream
void models::Car::writeToStream(QTextStream& out) const {
    out << toQString();
};

// Reads a Car object from a text stream
void models::Car::readFromStream(QTextStream& in) {

    const QString line = in.readLine();

    const QStringList fields = line.split('|');

    if (fields.size() < 8) {
        qDebug() << "Failed to read line from input stream";
        return;
    };

    bool ok = false;

    // Vehicle data fields
    data.vehicleTypeId = models::VehicleTypeId::car;
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
    data.numberOfDoors = fields.at(6).toInt();
    data.numberOfSeats = fields.at(7).toInt();

};
