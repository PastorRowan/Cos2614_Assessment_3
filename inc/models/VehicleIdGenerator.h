
#pragma once

#include <QString>

namespace models {

    class VehicleIdGenerator  {

        private:

            // File path used to store the current vehicle ID counter
            QString currentVehicleIdFileLocation = "Not initialised";

            // Current numeric vehicle ID counter
            long long currentVehicleId = -1;

            // Gets the current vehicle ID file location
            const QString& getCurrentIdFileLocation() const;

            // Sets the current vehicle ID counter
            void setCurrentVehicleId(const long long newCurrentVehicleId);

            // Decrements the current vehicle ID counter
            void decrementCurrentVehicleId();

            // Increments the current vehicle ID counter
            void incrementCurrentVehicleId();

            // Saves the current vehicle ID to storage
            void saveCurrentVehicleId(bool& ok);

            // Loads the current vehicle ID from storage
            void loadCurrentVehicleId(bool& ok);

            // Validates a numeric vehicle ID
            static bool isVehicleIdValid(const long long id);

            // Validates a vehicle ID represented as a QString
            static bool isVehicleIdValid(const QString& id);

        public:

            /**
             * Constructor
             */
            VehicleIdGenerator(
                const QString currentVehicleIdFileLocationP
            );

            /**
             * Destructor
             */
            ~VehicleIdGenerator() = default;

            // Gets the current vehicle ID counter
            long long getCurrentVehicleId() const;

            // Returns the current vehicle identifier as a QString
            QString getCurrentVehicleIdAsQString() const;

            /**
             * Generates a new unique vehicle identifier
             *
             * The identifier is incremented, persisted to storage, and returned
             * to the caller
             *
             * Returns a newly generated unique vehicle identifier
             */
            long long generateId();

    };

};
