
#pragma once

#include "models/VehicleIdGenerator.h"
#include "models/VehiclesPersistence.h"
#include "models/Car.h"
#include "models/Motorcycle.h"

#include <QObject>
#include <memory>

namespace models {

    /**
     * VehicleRepository
     * Stores and manages the application's collection of vehicles
     *
     * The repository owns all vehicle objects and provides operations for
     * modifying and querying the collection
     * It is also responsible for generating unique vehicle identifiers, persisting vehicle data, and
     * notifying interested objects whenever the collection changes
     */
    class VehicleRepository : public QObject {

        Q_OBJECT

        private:

            // Generates unique identifiers for newly added vehicles
            models::VehicleIdGenerator vehicleIdGenerator;

            // Handles loading and saving the vehicle collection
            models::VehiclesPersistence vehiclesPersistence;

            // Internal container storing all vehicle objects
            Vehicles vehicles;

            // Releases all dynamically allocated vehicle objects
            void destroyVehicles();

        public:

            /**
             * Constructs a VehicleRepository
             *
             * parent - The parent QObject
             */
            explicit VehicleRepository(
                QObject* parent
            );

            // Destroys the repository
            ~VehicleRepository() = default;

            // Returns a constant reference to the collection of vehicles
            const Vehicles& getVehicles() const;

            /**
             * Adds a new vehicle to the repository
             *
             * A unique vehicle identifier is generated automatically before the vehicle is stored
             *
             * vehicleData - The data describing the vehicle to add
             */
            void addVehicle(
                const models::VehicleData& vehicleData
            );

            /**
            * Adds a new motorcycle to the collection
            * Automatically generates a unique vehicle ID
            */
            void updateVehicle(
                const models::VehicleData& vehicleData
            );

            /**
            * Removes a vehicle in the collection
            */
            void removeVehicle(
                const long long vehicleId
            );

            /**
             * Removes all vehicles from the repository
             *
             * All owned vehicle objects are destroyed and the repository is returned to an empty state
             */
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

            /**
             * Handles requests to add a vehicle
             *
             * vehicleData - Shared pointer to the vehicle data to add
             */
            void handleAddVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

            /**
             * Handles requests to update a vehicle
             *
             * vehicleData - Shared pointer to the updated vehicle data
             */
            void handleUpdateVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

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
