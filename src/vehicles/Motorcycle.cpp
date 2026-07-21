
// Implementation of the Motorcycle class for the vehicle rental system

#include "vehicles/Motorcycle.h"

#include <QString>
#include <QTextStream>
#include <QStringList>

// Constructs a Motorcycle object with full initialization
vehicles::Motorcycle::Motorcycle(

    // Vehicle attributes
    const QString idP,
    const QString brandP,
    const QString modelP,
    const double pricePerDayP,
    const bool isRentedP,

    // Motorcycle attributes
    const int engineCapacityCCP

):
    Vehicle(
        vehicles::TypeId::motorCycle,
        idP,
        brandP,
        modelP,
        pricePerDayP,
        isRentedP
    ),
    engineCapacityCC(engineCapacityCCP) {

};

// Gets the engine capacity
int vehicles::Motorcycle::getEngineCapacityCC() const {
    return engineCapacityCC;
};

// Sets the engine capacity
void vehicles::Motorcycle::setEngineCapacityCC(const int newEngineCapacityCC) {
    engineCapacityCC = newEngineCapacityCC;
};

// Converts engine capacity to QString
QString vehicles::Motorcycle::engineCapacityCCToQString() const {
    return QString::number(getEngineCapacityCC());
};

// Serializes the Motorcycle object into a pipe-separated string
QString vehicles::Motorcycle::toQString() const {

    QString str = QString("%1|%2|%3|%4|%5|%6|%7")
        .arg(
            typeIdToQString(),
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
vehicles::Vehicle* vehicles::Motorcycle::clone() const {

    return new vehicles::Motorcycle(

        getVehicleId(),
        getBrand(),
        getModel(),
        getPricePerDay(),
        getIsRented(),

        getEngineCapacityCC()

    );

};

// Writes the Motorcycle object to a text stream
void vehicles::Motorcycle::writeToStream(QTextStream& out) const {
    out << toQString();
};

// Reads a Motorcycle object from a text stream
void vehicles::Motorcycle::readFromStream(QTextStream& in) {

    QString line = in.readLine();

    const QStringList fields = line.split('|');

    if (fields.size() < 7) {
        return;
    };

    // Base class fields
    setTypeId(vehicles::TypeId::motorCycle);
    setVehicleId(fields[1]);
    setBrand(fields[2]);
    setModel(fields[3]);
    setPricePerDay(fields[4].toDouble());
    setIsRented(vehicles::Vehicle::isRentedQStringToBool(fields[5]));

    // Motorcycle specific fields
    setEngineCapacityCC(fields[6].toInt());

};
