
#pragma once

#include "models/Vehicle.h"

class QObject;
class QString;

namespace models {

    struct CarData : public VehicleData {
        models::VehicleTypeId VehicleTypeId = models::VehicleTypeId::car;
        int numberOfDoors = -1;
        int numberOfSeats = -1;
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
            ~Car() {};

            // Gets the number of doors
            int getNumberOfDoors() const;

            // Sets the number of doors
            void setNumberOfDoors(const int newNumberOfDoors);

            // Converts the number of doors to a QString
            QString numberOfDoorsToQString() const;

            // Gets the number of seats
            int getNumberOfSeats() const;

            // Sets the number of seats
            void setNumberOfSeats(const int newNumberOfSeats);

            // Converts the number of seats to a QString.
            QString numberOfSeatsToQString() const;

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
