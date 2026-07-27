
// Implementation of the base Vehicle class for the rental system

#include "models/Vehicle.h"

#include <QObject>
#include <QString>
#include <QTextStream>

// Constructs a Vehicle object with all base attributes initialized
models::Vehicle::Vehicle(
    QObject *parent,
    const models::VehicleData vehicleDataP
):
    QObject(parent) {

};

// Gets the vehicle type identifier
models::VehicleTypeId models::Vehicle::getVehicleTypeId() const {
    return getVehicleData().vehicleTypeId;
};

// Sets the vehicle type identifier
void models::Vehicle::setVehicleTypeId(const models::VehicleTypeId newVehicleTypeId) {

    if (getVehicleData().vehicleTypeId == newVehicleTypeId) {
        return;
    };

    getVehicleData().vehicleTypeId = newVehicleTypeId;
    emit vehicleUpdated(getVehicleId());
};

// Gets the vehicle ID
long long models::Vehicle::getVehicleId() const {
    return getVehicleData().vehicleId;
};

QString models::Vehicle::getVehicleIdAsQString() const {
    return QString::number(getVehicleData().vehicleId);
};

// Converts the vehicle type ID to a QString
QString models::Vehicle::getVehicleTypeIdAsQString() const {
    return QString::number(static_cast<int>(getVehicleData().vehicleTypeId));
};

// Sets the vehicle ID
void models::Vehicle::setVehicleId(const long long newVehicleId) {

    if (getVehicleData().vehicleId == newVehicleId) {
        return;
    };

    getVehicleData().vehicleId = newVehicleId;
    emit vehicleUpdated(getVehicleId());
};

// Gets the brand of the vehicle
QString models::Vehicle::getBrand() const {
    return getVehicleData().brand;
};

// Sets the brand of the vehicle
void models::Vehicle::setBrand(const QString& newBrand) {

    if (getVehicleData().brand == newBrand) {
        return;
    };

    getVehicleData().brand = newBrand;
    emit vehicleUpdated(getVehicleId());

};

// Gets the model of the vehicle
QString models::Vehicle::getModel() const {
    return getVehicleData().model;
};

// Sets the model of the vehicle
void models::Vehicle::setModel(const QString& newModel) {
    getVehicleData().model = newModel;
    emit vehicleUpdated(getVehicleId());
};

// Gets the rental price per day
double models::Vehicle::getPricePerDay() const {
    return getVehicleData().pricePerDay;
};

// Sets the rental price per day
void models::Vehicle::setPricePerDay(const double newPricePerDay) {
    getVehicleData().pricePerDay = newPricePerDay;
    emit vehicleUpdated(getVehicleId());
};

// Converts the price per day to QString
QString models::Vehicle::getPricePerDayAsQString() const {
    return QString::number(getPricePerDay());
};

// Gets the rental status of the vehicle
bool models::Vehicle::getIsRented() const {
    return getVehicleData().isRented;
};

// Sets the rental status of the vehicle
void models::Vehicle::setIsRented(const bool newIsRented) {
    getVehicleData().isRented = newIsRented;
    emit vehicleUpdated(getVehicleId());
};

// Converts rental status to QString
QString models::Vehicle::getIsRentedAsQString() const {
    return QString(getIsRented() ? "Yes" : "No");
};

bool models::Vehicle::isRentedQStringToBool(const QString& isRentedQString) {
    return isRentedQString == QString("Yes");
};

// Stream insertion operator for Vehicle serialization
QTextStream& models::operator<<(QTextStream& out, const models::Vehicle& v) {
    v.writeToStream(out);
    return out;
};

// Stream extraction operator for Vehicle deserialization
QTextStream& models::operator>>(QTextStream& in, models::Vehicle& v) {
    v.readFromStream(in);
    return in;
};
