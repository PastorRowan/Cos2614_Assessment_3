
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
            Vehicles::Iterator findVehicleIterator(Predicate predicate) {
                for (auto it = begin(); it != end(); ++it) {
                    auto vehicle = *it;
                    if (predicate(vehicle)) {
                        return it;
                    };
                };
                return end();
            };

            template<typename Predicate>
            Vehicles::ConstIterator findVehicleIterator(Predicate predicate) const {
                for (auto it = cbegin(); it != cend(); ++it) {
                    auto vehicle = *it;
                    if (predicate(vehicle)) {
                        return it;
                    };
                };
                return end();
            };

            template<typename Predicate>
            models::Vehicle* findVehicle(Predicate predicate) {
                Vehicles::Iterator it = findVehicleIterator(predicate);
                return it != end() ? *it : nullptr;
            };

            Vehicles::Iterator findVehicleIteratorById(const long long vehicleId) {
                return findVehicleIterator(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getVehicleId() == vehicleId;
                    }
                );
            };

            models::Vehicle* findVehicleById(const long long vehicleId) {
                return findVehicle(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getVehicleId() == vehicleId;
                    }
                );
            };

            template<typename Predicate>
            Vehicles findVehicles(Predicate predicate) {
                Vehicles foundVehicles;
                for (auto cit = cbegin(); cit != cend(); ++cit) {
                    auto vehicle = *cit;
                    if (predicate(vehicle)) {
                        foundVehicles.push_back(vehicle->clone());
                    };
                };
                return foundVehicles;
            };

            Vehicles findVehiclesByTypeId(const models::VehicleTypeId typeId) {
                return findVehicles(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getVehicleTypeId() == typeId;
                    }
                );
            };

            Vehicles findVehiclesByBrand(const QString brand) {
                return findVehicles(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getBrand() == brand;
                    }
                );
            };

            Vehicles findVehiclesByModel(const QString model) {
                return findVehicles(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getModel() == model;
                    }
                );
            };

            Vehicles findVehiclesByPricePerDay(const QString model) {
                return findVehicles(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getModel() == model;
                    }
                );
            };

            Vehicles findVehiclesByIsRented(const bool isRented) {
                return findVehicles(
                    [&](models::Vehicle* vehicle) {
                        return vehicle->getIsRented() == isRented;
                    }
                );
            };

    };

};
