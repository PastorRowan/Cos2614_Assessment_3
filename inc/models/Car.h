
#pragma once

#include "models/Vehicle.h"

#include <memory>
class QObject;
class QString;

namespace models {

    struct CarData : public VehicleData {

        int numberOfDoors = -1;
        int numberOfSeats = -1;

        CarData(
            const QString brandP = "Not initialised",
            const QString modelP = "Not initialised",
            double pricePerDayP = -1.0,
            int numberOfDoorsP = -1,
            int numberOfSeatsP = -1,
            bool isRentedP = false,
            long long vehicleIdP = -1
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

        QString getNumberOfDoorsAsQString() {
            return QString::number(numberOfDoors);
        };

        QString getNumberOfSeatsAsQString() {
            return QString::number(numberOfSeats);
        };

        [[nodiscard]]
        std::unique_ptr<VehicleData> clone() const override {
            return std::make_unique<CarData>(*this);
        };

    };

    // Represents a Car vehicle type
    class Car : public Vehicle {

        private:

            CarData data;

        public:

            /**
             * Default constructor
             * Creates an uninitialized Car object with default placeholder values
             */
            Car() {};

            /**
             * Parameterized constructor
             * Initializes a Car object with both general vehicle
             * attributes and car-specific properties
             */
            Car(
                // QObject parent
                QObject *parent,
                CarData carDataP
            );

            // Destructor
            ~Car() = default;

            const VehicleData& getVehicleData() const override;

            VehicleData& getVehicleData() override;

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
