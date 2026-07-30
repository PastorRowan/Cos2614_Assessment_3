
#pragma once

#include "models/Vehicle.h"

#include <QVector>
#include <QtAlgorithms>

namespace models {

    /**
     * Vehicles
     * Container type used to store vehicle pointers
     */
    typedef QVector<models::Vehicle*> VehiclesQVector;

    class Vehicles : public VehiclesQVector {

        private:

        public:

            ~Vehicles() {
                qDeleteAll(*this);
                clear();
            };

            template<typename Predicate>
            models::Vehicle* findVehicle(Predicate predicate) {
                for (auto vehicle : *this) {
                    if (predicate(vehicle)) {
                        return vehicle;
                    };
                };
                return nullptr;
            };

            models::Vehicle* findVehicleById(const long long vehicleId) {
                return findVehicle(
                    [&](Vehicle* vehicle) {
                        return vehicle->getVehicleId() == vehicleId;
                    }
                );
            };

            template<typename Predicate>
            VehiclesQVector findVehicles(Predicate predicate) {
                VehiclesQVector foundVehicles = {};
                for (auto vehicle : *this) {
                    if (predicate(vehicle)) {
                        foundVehicles.push_back(vehicle);
                    };
                };
                return foundVehicles;
            };

            VehiclesQVector findVehiclesByTypeId(const models::VehicleTypeId typeId) {
                return findVehicles(
                    [&](Vehicle* vehicle) {
                        return vehicle->getVehicleTypeId() == typeId;
                    }
                );
            };

            VehiclesQVector findVehiclesByBrand(const QString brand) {
                return findVehicles(
                    [&](Vehicle* vehicle) {
                        return vehicle->getBrand() == brand;
                    }
                );
            };

            VehiclesQVector findVehiclesByModel(const QString model) {
                return findVehicles(
                    [&](Vehicle* vehicle) {
                        return vehicle->getModel() == model;
                    }
                );
            };

            VehiclesQVector findVehiclesByPricePerDay(const QString model) {
                return findVehicles(
                    [&](Vehicle* vehicle) {
                        return vehicle->getModel() == model;
                    }
                );
            };

    };

};
