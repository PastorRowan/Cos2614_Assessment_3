
// Implementation of the base Vehicle class for the rental system

#include "vehicles/Vehicle.h"

#include <QString>
#include <QTextStream>

// Constructs a Vehicle object with all base attributes initialized
vehicles::Vehicle::Vehicle(

    const vehicles::TypeId typeIdP,
    const QString vehicleIdP,
    const QString brandP,
    const QString modelP,
    const double pricePerDayP,
    const bool isRentedP

):
    typeId(typeIdP),
    vehicleId(vehicleIdP),
    brand(brandP),
    model(modelP),
    pricePerDay(pricePerDayP),
    isRented(isRentedP) {

};

// Gets the vehicle type identifier
vehicles::TypeId vehicles::Vehicle::getTypeId() const {
    return typeId;
};

// Sets the vehicle type identifier
void vehicles::Vehicle::setTypeId(const vehicles::TypeId newTypeId) {
    typeId = newTypeId;
};

// Converts the vehicle type ID to a QString
QString vehicles::Vehicle::typeIdToQString() const {
    return QString::number(static_cast<int>(typeId));
};

// Gets the vehicle ID
QString vehicles::Vehicle::getVehicleId() const {
    return vehicleId;
};

// Sets the vehicle ID
void vehicles::Vehicle::setVehicleId(const QString& newVehicleId) {
    vehicleId = newVehicleId;
};

// Gets the brand of the vehicle
QString vehicles::Vehicle::getBrand() const {
    return brand;
};

// Sets the brand of the vehicle
void vehicles::Vehicle::setBrand(const QString& newBrand) {
    brand = newBrand;
};

// Gets the model of the vehicle
QString vehicles::Vehicle::getModel() const {
    return model;
};

// Sets the model of the vehicle
void vehicles::Vehicle::setModel(const QString& newModel) {
    model = newModel;
};

// Gets the rental price per day
double vehicles::Vehicle::getPricePerDay() const {
    return pricePerDay;
};

// Sets the rental price per day
void vehicles::Vehicle::setPricePerDay(const double newPricePerDay) {
    pricePerDay = newPricePerDay;
};

// Converts the price per day to QString
QString vehicles::Vehicle::pricePerDayToQString() const {
    return QString::number(getPricePerDay());
};

// Gets the rental status of the vehicle
bool vehicles::Vehicle::getIsRented() const {
    return isRented;
};

// Sets the rental status of the vehicle
void vehicles::Vehicle::setIsRented(const bool newIsRented) {
    isRented = newIsRented;
};

// Converts rental status to QString
QString vehicles::Vehicle::isRentedToQString() const {
    return QString(getIsRented() ? "Yes" : "No");
};

bool vehicles::Vehicle::isRentedQStringToBool(const QString& isRentedQString) {
    return isRentedQString == QString("Yes");
};

// Stream insertion operator for Vehicle serialization
QTextStream& vehicles::operator<<(QTextStream& out, const vehicles::Vehicle& v) {
    v.writeToStream(out);
    return out;
};

// Stream extraction operator for Vehicle deserialization
QTextStream& vehicles::operator>>(QTextStream& in, vehicles::Vehicle& v) {
    v.readFromStream(in);
    return in;
};
