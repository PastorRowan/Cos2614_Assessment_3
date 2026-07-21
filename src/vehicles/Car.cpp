
// Implementation of the Car class for the vehicle rental system.

#include "vehicles/Car.h"

#include <QString>
#include <QTextStream>
#include <QStringList>

// Constructs a Car object with full initialization
vehicles::Car::Car(

    // Vehicle attributes
    const QString vehicleIdP,
    const QString brandP,
    const QString modelP,
    const double pricePerDayP,
    const bool isRentedP,

    // Car attributes
    const int numberOfDoorsP,
    const int numberOfSeatsP

):
    Vehicle(
        vehicles::TypeId::car,
        vehicleIdP,
        brandP,
        modelP,
        pricePerDayP,
        isRentedP
    ),
    numberOfDoors(numberOfDoorsP),
    numberOfSeats(numberOfSeatsP) {
        
    };

// Gets the number of doors
int vehicles::Car::getNumberOfDoors() const {
    return numberOfDoors;
};

// Sets the number of doors
void vehicles::Car::setNumberOfDoors(const int newNumberOfDoors) {
    numberOfDoors = newNumberOfDoors;
};

// Converts number of doors to QString
QString vehicles::Car::numberOfDoorsToQString() const {
    return QString::number(getNumberOfDoors());
};

// Gets the number of seats
int vehicles::Car::getNumberOfSeats() const {
    return numberOfSeats;
};

// Sets the number of seats
void vehicles::Car::setNumberOfSeats(const int newNumberOfSeats) {
    numberOfSeats = newNumberOfSeats;
};

// Converts number of seats to QString
QString vehicles::Car::numberOfSeatsToQString() const {
    return QString::number(getNumberOfSeats());
};

// Serializes the Car object into a pipe-separated string
QString vehicles::Car::toQString() const {

    QString str = QString("%1|%2|%3|%4|%5|%6|%7|%8")
        .arg(
            typeIdToQString(),
            getVehicleId(),
            getBrand(),
            getModel(),
            pricePerDayToQString(),
            isRentedToQString(),
            numberOfDoorsToQString(),
            numberOfSeatsToQString()
        );

    return str;

};

// Creates a deep copy of the Car object
vehicles::Vehicle* vehicles::Car::clone() const {

    return new vehicles::Car(

        getVehicleId(),
        getBrand(),
        getModel(),
        getPricePerDay(),
        getIsRented(),

        getNumberOfDoors(),
        getNumberOfSeats()

    );

};

// Writes the Car object to a text stream
void vehicles::Car::writeToStream(QTextStream& out) const {
    out << toQString();
};

// Reads a Car object from a text stream
void vehicles::Car::readFromStream(QTextStream& in) {

    QString line = in.readLine();

    const QStringList fields = line.split('|');

    if (fields.size() < 8) {
        return;
    };

    // Base class fields
    setTypeId(vehicles::TypeId::car);
    setVehicleId(fields[1]);
    setBrand(fields[2]);
    setModel(fields[3]);
    setPricePerDay(fields[4].toDouble());
    setIsRented(vehicles::Vehicle::isRentedQStringToBool(fields[5]));

    // Car specific fields
    setNumberOfDoors(fields[6].toInt());
    setNumberOfSeats(fields[7].toInt());

};
