
#pragma once

#include "models/Vehicles.h"

#include <QString>

namespace models {

    // Manages vehicle storage, persistence, and rental operations
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

            void clear();

    };

};
