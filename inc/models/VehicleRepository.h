
#pragma once

#include "models/models.h"

namespace models {

    class VehicleRepository {

        private:

            models::VehicleIdGenerator vehicleIdGenerator;

            models::VehiclePersistence vehiclePersistence;

            // Alias for the internal vehicle container type
            typedef QVector<models::Vehicle*> Vehicles;

            // Internal container storing all vehicle objects
            Vehicles vehicles;

            // Releases all dynamically allocated vehicle objects
            void destroyVehicles();

        public:

            // Gets the internal vehicle collection
            const Vehicles& getVehicles() const;

            /**
            * Adds a new car to the collection
            * Automatically generates a unique vehicle ID
            */
            void addCar(
                const models::CarData carData
            );

            /**
            * Adds a new motorcycle to the collection
            * Automatically generates a unique vehicle ID
            */
            void addMotorcycle(
                const models::MotorcycleData
            );

            /**
            * Removes a vehicle in the collection
            */
            void removeVehicle(
                const QString& vehicleId
            );

            void clear();

            /**
            * Searches for a vehicle by its ID
            * Returns a pointer to the matching vehicle, or nullptr if not found
            */
            models::Vehicle* searchVehicleById(const QString& vehicleId);

            // Marks a vehicle as rented using its ID
            void rentVehicleById(
                const QString& vehicleId
            );

            // Marks a rented vehicle as returned (not rented)
            void returnVehicleById(
                const QString& vehicleId
            );

        // slots:

            void handleVehicleUpdated(const QString vehicleId);

        signals:

            /// Emitted whenever the vehicle collection changes.
            void vehiclesChanged();

            /// Emitted after a vehicle is added.
            void vehicleAdded(const QString vehicleId);

            /// Emitted after a vehicle is removed.
            void vehicleRemoved(const QString vehicleId);

            /// Emitted after a vehicle's data changes.
            void vehicleUpdated(const QString vehicleId);

            /// Emitted after a vehicle is rented.
            void vehicleRented(const QString vehicleId);

            /// Emitted after a vehicle is returned.
            void vehicleReturned(const QString vehicleId);

    };

};
