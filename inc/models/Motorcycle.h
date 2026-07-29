
#pragma once

#include "models/Vehicle.h"

#include <memory>
class QObject;
class QString;

namespace models {

    // Default engine capacity in CC (cubic centimetres)
    const int DEFAULT_ENGINE_CAPACITY_CC = 0;

    struct MotorcycleData : public VehicleData {

        // The engine capacity in CC
        int engineCapacityCC = DEFAULT_ENGINE_CAPACITY_CC;

        /**
         * Constructs a MotorcycleData object
         *
         * brandP - The motorcycle brand
         * modelP - The motorcycle model
         * pricePerDayP - The daily rental price
         * engineCapacityCCP - The engine capacity in cubic centimetres
         * isRentedP - Whether the motorcycle is currently rented
         * vehicleIdP - The unique vehicle identifier
         */
        MotorcycleData(
            const QString brandP = models::DEFAULT_BRAND,
            const QString modelP = models::DEFAULT_MODEL,
            double pricePerDayP = models::DEFAULT_PRICE_PER_DAY,
            int engineCapacityCCP = models::DEFAULT_ENGINE_CAPACITY_CC,
            bool isRentedP = models::DEFAULT_IS_RENTED,
            long long vehicleIdP = models::DEFAULT_VEHICLE_ID
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

        // Returns the engine capacity as a QString
        QString getEngineCapacityCCAsQString() {
            return QString::number(engineCapacityCC);
        };

        /**
         * Validates the motorcycle data.
         *
         * message - Receives a description of the validation error if validation fails
         *
         * Returns true if the data is valid, otherwise false
         */
        bool isValid(QString& message) const override {
            if (pricePerDay < 0.0) {
                message = "PRICE_PER_DAY must be greater than or equal to 0";
                return false;
            } else if (engineCapacityCC <= -1) {
                message = "ENGINE_CAPACITY_CC must be greater than or equal to 0";
                return false;
            } else {
                return true;
            };
        };


        /**
         * Creates a deep copy of this MotorcycleData object
         *
         * A unique pointer to the cloned MotorcycleData object
         */
        [[nodiscard]]
        std::unique_ptr<VehicleData> clone() const override {
            return std::make_unique<MotorcycleData>(*this);
        };

    };

    /**
     * Motorcycle
     * Represents a motorcycle in the vehicle rental system
     *
     * Implements the Vehicle interface using a MotorcycleData object to
     * store both the common vehicle attributes and motorcycle-specific
     * properties
     */
    class Motorcycle : public Vehicle {

        private:

            // The data describing this motorcycle
            MotorcycleData data;

        public:

            /**
             * Default constructor
             * Creates an uninitialized Motorcycle object with default placeholder values
             */
            explicit Motorcycle() {};

            /**
             * Parameterized constructor
             * Initializes a Motorcycle instance with all required vehicle attributes
             * and its specific engine capacity attribute
             */
            explicit Motorcycle(
                // QObject parent
                QObject *parent,
                MotorcycleData data
            );

            // Destructor
            ~Motorcycle() = default;

            // Returns a constant reference to the vehicle data
            const VehicleData& getVehicleData() const override;

            // Returns a mutable reference to the vehicle data
            VehicleData& getVehicleData() override;

            /**
             * Replaces the motorcycle data
             *
             * vehicleData - The new vehicle data
             */
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
