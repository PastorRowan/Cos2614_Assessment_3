
#pragma once

#include "models/Vehicle.h"

#include <memory>
class QObject;
class QString;

namespace models {

    // Default number of doors for a car
    const int DEFAULT_NUMBER_OF_DOORS = 0;

    // Default number of seats for a car
    const int DEFAULT_NUMBER_OF_SEATS = 0;

    /**
     * CarData
     * struct that stores the data associated with a car
     *
     * Extends VehicleData by adding car-specific attributes such as the
     * number of doors and seats
     */
    struct CarData : public VehicleData {

        // The number of doors
        int numberOfDoors = DEFAULT_NUMBER_OF_DOORS;

        // The number of seats
        int numberOfSeats = DEFAULT_NUMBER_OF_SEATS;

        /**
         * Constructs a CarData object
         *
         * brandP - The vehicle brand
         * modelP - The vehicle model
         * pricePerDayP - The daily rental price
         * numberOfDoorsP - The number of doors
         * numberOfSeatsP - The number of seats
         * isRentedP - Whether the vehicle is currently rented
         * vehicleIdP - The unique vehicle identifier (Should generally be left empty until
         * the vehicle id generator gives it can id)
         */
        CarData(
            const QString brandP = models::DEFAULT_BRAND,
            const QString modelP = models::DEFAULT_MODEL,
            double pricePerDayP = models::DEFAULT_PRICE_PER_DAY,
            int numberOfDoorsP = DEFAULT_NUMBER_OF_DOORS,
            int numberOfSeatsP = DEFAULT_NUMBER_OF_SEATS,
            bool isRentedP = models::DEFAULT_IS_RENTED,
            long long vehicleIdP = models::DEFAULT_VEHICLE_ID
        ):
            VehicleData(
                VehicleTypeId::car,
                vehicleIdP,
                brandP,
                modelP,
                pricePerDayP,
                isRentedP
            ),
            numberOfDoors(numberOfDoorsP),
            numberOfSeats(numberOfSeatsP) {
        };

        // Returns the number of doors as a QString
        QString getNumberOfDoorsAsQString() {
            return QString::number(numberOfDoors);
        };

        // Returns the number of seats as a QString
        QString getNumberOfSeatsAsQString() {
            return QString::number(numberOfSeats);
        };

        /**
         * isValid
         * Validates the car data
         *
         * message - Receives a description of the validation error if
         * validation fails
         *
         * Returns True if the data is valid, otherwise false
         */
        bool isValid(QString& message) const override {
            if (pricePerDay < models::MINIMUM_PRICE_PER_DAY || pricePerDay > models::MAXIMUM_PRICE_PER_DAY) {
                message = "PRICE_PER_DAY must be greater than or equal to 0";
                return false;
            } else if (numberOfDoors <= -1) {
                message = "NUMBER_OF_DOORS must be greater than or equal to 0";
                return false;
            } else if (numberOfSeats <= 0) {
                message = "NUMBER_OF_SEATS must be greater than or equal to 1";
                return false;
            } else {
                return true;
            };
        };

        /**
         * clone
         * Creates a deep copy of this CarData object
         * Returns a unique pointer to the cloned CarData object
         */
        [[nodiscard]]
        std::unique_ptr<VehicleData> clone() const override {
            return std::make_unique<CarData>(*this);
        };

    };

    /**
     * Car
     * Represents a car in the vehicle rental system.
     *
     * Implements the Vehicle interface using a CarData object to store
     * both the common vehicle attributes and car-specific properties
     */
    class Car : public Vehicle {

        private:

            CarData data;

        public:

            /**
             * Default constructor
             * Creates an uninitialized Car object with default placeholder values
             */
            explicit Car() {};

            /**
             * Parameterized constructor
             * Initializes a Car object with both general vehicle
             * attributes and car-specific properties
             */
            explicit Car(
                // QObject parent
                QObject *parent,
                CarData carDataP
            );

            // Destructor
            ~Car() = default;

            // Returns a constant reference to the vehicle data
            const VehicleData& getVehicleData() const override;

            // Returns a mutable reference to the vehicle data
            VehicleData& getVehicleData() override;

            /**
             * Replaces the vehicle data
             * vehicleData - The new vehicle data
             */
            void setVehicleData(const models::VehicleData& vehicleData) override;

            // Gets the number of doors
            int getNumberOfDoors() const;

            // Converts the number of doors to a QString
            QString getNumberOfDoorsAsQString() const;

            // Sets the number of doors
            void setNumberOfDoors(const int newNumberOfDoors);

            // Gets the number of seats
            int getNumberOfSeats() const;

            // Converts the number of seats to a QString.
            QString getNumberOfSeatsAsQString() const;

            // Sets the number of seats
            void setNumberOfSeats(const int newNumberOfSeats);

            // Converts the car object to a formatted QString.
            QString toQString() const override;

            // Creates a deep copy of the car object
            models::Vehicle* clone() const override;

            // Writes the car data to a text stream.
            void writeToStream(QTextStream& out) const override;

            // Reads the car data from a text stream
            void readFromStream(QTextStream& in) override;

    };

};
