
// Implementation of the base Vehicle class for the rental system

#include "models/Vehicle.h"

#include <QObject>
#include <QString>
#include <QTextStream>

// Constructs a Vehicle object with all base attributes initialized
models::Vehicle::Vehicle(
    QObject *parent,
    const VehicleData vehicleDataP
):
    QObject(parent),
    data(vehicleDataP) {

};

// Gets the vehicle type identifier
models::VehicleTypeId models::Vehicle::getVehicleTypeId() const {
    return data.VehicleTypeId;
};

// Sets the vehicle type identifier
void models::Vehicle::setVehicleTypeId(const models::VehicleTypeId newVehicleTypeId) {

    if (data.VehicleTypeId == newVehicleTypeId) {
        return;
    };

    data.VehicleTypeId = newVehicleTypeId;
    emit vehicleUpdated(getVehicleId());
};

// Converts the vehicle type ID to a QString
QString models::Vehicle::VehicleTypeIdToQString() const {
    return QString::number(static_cast<int>(data.VehicleTypeId));
};

// Gets the vehicle ID
QString models::Vehicle::getVehicleId() const {
    return data.vehicleId;
};

// Sets the vehicle ID
void models::Vehicle::setVehicleId(const QString& newVehicleId) {

    if (data.vehicleId == newVehicleId) {
        return;
    };

    data.vehicleId = newVehicleId;
    emit vehicleUpdated(getVehicleId());
};

// Gets the brand of the vehicle
QString models::Vehicle::getBrand() const {
    return data.brand;
};

// Sets the brand of the vehicle
void models::Vehicle::setBrand(const QString& newBrand) {

    if (data.brand == newBrand) {
        return;
    };

    data.brand = newBrand;
    emit vehicleUpdated(getVehicleId());

};

// Gets the model of the vehicle
QString models::Vehicle::getModel() const {
    return data.model;
};

// Sets the model of the vehicle
void models::Vehicle::setModel(const QString& newModel) {
    data.model = newModel;
    emit vehicleUpdated(getVehicleId());
};

// Gets the rental price per day
double models::Vehicle::getPricePerDay() const {
    return data.pricePerDay;
};

// Sets the rental price per day
void models::Vehicle::setPricePerDay(const double newPricePerDay) {
    data.pricePerDay = newPricePerDay;
    emit vehicleUpdated(getVehicleId());
};

// Converts the price per day to QString
QString models::Vehicle::pricePerDayToQString() const {
    return QString::number(getPricePerDay());
};

// Gets the rental status of the vehicle
bool models::Vehicle::getIsRented() const {
    return data.isRented;
};

// Sets the rental status of the vehicle
void models::Vehicle::setIsRented(const bool newIsRented) {
    data.isRented = newIsRented;
    emit vehicleUpdated(getVehicleId());
};

// Converts rental status to QString
QString models::Vehicle::isRentedToQString() const {
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
