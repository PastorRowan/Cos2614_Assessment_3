
#pragma once

#include <QString>

namespace models {

    class VehicleIdGenerator  {

        private:

            // File path used to store the current vehicle ID counter
            QString currentVehicleIdFileLocation = "Not initialised";

            // Current numeric vehicle ID counter
            long long currentVehicleId = -1;

            // Validates a numeric vehicle ID
            static bool isVehicleIdValid(const long long id);

            // Validates a vehicle ID represented as a QString
            static bool isVehicleIdValid(const QString& id);

            // Gets the current vehicle ID counter
            long long getCurrentVehicleId() const;

            // Sets the current vehicle ID counter
            void setCurrentVehicleId(const long long newCurrentVehicleId);

            // Decrements the current vehicle ID counter
            void decrementCurrentVehicleId();

            // Increments the current vehicle ID counter
            void incrementCurrentVehicleId();

            // Increments and saves the current vehicle ID
            void incrementAndSaveCurrentVehicleId(bool& ok);

            // Sets the current vehicle ID file location
            void setCurrentIdFileLocation(const QString currentVehicleIdFileLocationP);

            // Saves the current vehicle ID to storage
            void saveCurrentVehicleId(bool& ok);

            // Loads the current vehicle ID from storage
            void loadCurrentVehicleId(bool& ok);

            // Gets the current vehicle ID file location
            const QString& getCurrentIdFileLocation() const;

        public:

            /**
            * Destructor
            */
            ~VehicleIdGenerator() = default;

    };

};
