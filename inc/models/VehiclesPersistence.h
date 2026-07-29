
#pragma once

#include "models/Vehicles.h"

#include <QString>

namespace models {

    /**
     * VehiclesPersistence
     * Handles persistence of vehicle collections
     *
     * The VehiclesPersistence class provides functionality for saving a
     * collection of vehicles to a file and restoring that collection from
     * persistent storage
     * It also provides utilities for clearing the persisted data
     */
    class VehiclesPersistence {

        private:

            // File path for vehicle data storage
            QString vehiclesFileLocation = "Not initialised";

            // Gets the vehicle data file location
            const QString& getVehiclesFileLocation() const;

            // Sets the vehicle data file location
            void setVehiclesFileLocation(
                const QString vehiclesFileLocationP
            );

        public:

            // Constructs a VehiclesPersistence manager
            VehiclesPersistence(const QString vehiclesFileLocationP);

            /**
            * Destructor
            */
            ~VehiclesPersistence() = default;

            // Saves the current vehicle collection to disk
            void saveVehicles(const models::Vehicles& vehicles, bool& ok);

            // Loads vehicle data from storage
            void loadVehicles(models::Vehicles& vehicles, bool& ok);

            /**
             * Clears the persisted vehicle data
             *
             * Removes all stored vehicle data from the file
             */
            void clear();

    };

};
