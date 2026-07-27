
#pragma once

#include "models/Vehicle.h"

#include <optional>
class QObject;
class QString;

namespace models {

    struct MotorcycleData : public VehicleData {

        models::VehicleTypeId vehicleTypeId = models::VehicleTypeId::motorCycle;
        int engineCapacityCC = -1;

        MotorcycleData(
            const QString brandP = "Not initialised",
            const QString modelP = "Not initialised",
            double pricePerDayP = -1.0,
            int engineCapacityCCP = -1,
            bool isRentedP = false,
            long long vehicleIdP = -1
        ):
            VehicleData(
                VehicleTypeId::motorCycle,
                vehicleIdP,
                brandP,
                modelP,
                pricePerDayP,
                isRentedP
            ),
            engineCapacityCC(engineCapacityCCP) {
        };
    };

    typedef std::optional<MotorcycleData> OptionalMotorcycleData;

    // Represents a motorcycle vehicle type
    class Motorcycle : public Vehicle {

        private:

            MotorcycleData data;

        public:

            /**
             * Default constructor
             * Creates an uninitialized Motorcycle object with default placeholder values
             */
            Motorcycle() {};

            /**
             * Parameterized constructor
             * Initializes a Motorcycle instance with all required vehicle attributes
             * and its specific engine capacity attribute
             */
            Motorcycle(
                // QObject parent
                QObject *parent,
                MotorcycleData data
            );

            // Destructor
            ~Motorcycle() = default;

            const VehicleData& getVehicleData() const override;

            VehicleData& getVehicleData() override;

            void setVehicleData(const models::VehicleData& vehicleData) override;

            // Gets the engine capacity
            int getEngineCapacityCC() const;

            // Converts the engine capacity to a QString
            QString getEngineCapacityCCAsQString() const;

            // Sets the engine capacity
            void setEngineCapacityCC(const int newEngineCapacityCC);

            // Converts the motorcycle object to a formatted QString
            QString toQString() const override;

            // Creates a deep copy of the motorcycle object
            models::Vehicle* clone() const override;

            // Writes the motorcycle data to a text stream
            void writeToStream(QTextStream& out) const override;

            // Reads motorcycle data from a text stream
            void readFromStream(QTextStream& in) override;

    };

};
