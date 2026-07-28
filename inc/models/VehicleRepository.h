
#pragma once

#include "models/VehicleIdGenerator.h"
#include "models/VehiclesPersistence.h"
#include "models/Car.h"
#include "models/Motorcycle.h"

#include <QObject>

namespace models {

    class VehicleRepository : public QObject {

        Q_OBJECT

        private:

            models::VehicleIdGenerator vehicleIdGenerator;

            models::VehiclesPersistence vehiclesPersistence;

            // Internal container storing all vehicle objects
            Vehicles vehicles;

            // Releases all dynamically allocated vehicle objects
            void destroyVehicles();

        public:

            VehicleRepository(
                QObject* parent
            );

            ~VehicleRepository() = default;

            // Gets the internal vehicle collection
            const Vehicles& getVehicles() const;

            /**
            *
            *
            */
            void addVehicle(
                const VehicleData& vehicleData
            );

            /**
            * Adds a new motorcycle to the collection
            * Automatically generates a unique vehicle ID
            */
            void updateVehicle(
                const VehicleData& vehicleData
            );

            /**
            * Removes a vehicle in the collection
            */
            void removeVehicle(
                const long long vehicleId
            );

            void clear();

            /**
            * Searches for a vehicle by its ID
            * Returns a pointer to the matching vehicle, or nullptr if not found
            */
            models::Vehicle* searchVehicleById(const long long vehicleId);

            // Marks a vehicle as rented using its ID
            void rentVehicleById(const long long vehicleId);

            // Marks a rented vehicle as returned (not rented)
            void returnVehicleById(const long long vehicleId);

        // slots:

            void handleUpdateVehicle(const models::VehicleData& vehicleData);

        signals:

            /// Emitted whenever the vehicle collection changes.
            void vehiclesChanged();

            /// Emitted after a vehicle is added.
            void vehicleAdded(const long long vehicleId);

            /// Emitted after a vehicle is removed.
            void vehicleRemoved(const long long vehicleId);

            /// Emitted after a vehicle's data changes.
            void vehicleUpdated(const long long vehicleId);

            /// Emitted after a vehicle is rented.
            void vehicleRented(const long long vehicleId);

            /// Emitted after a vehicle is returned.
            void vehicleReturned(const long long vehicleId);

    };

};
