
#pragma once

#include "vehicles/Vehicle.h"

#include <QString>
#include <QStringList>

namespace vehicles {

    // Represents a Car vehicle type
    class Car : public Vehicle {

        private:

            vehicles::TypeId typeId = vehicles::TypeId::car;
            int numberOfDoors = -1;
            int numberOfSeats = -1;

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

                // Vehicle attributes
                const QString vehicleIdP,
                const QString brandP,
                const QString modelP,
                const double pricePerDayP,
                const bool isRentedP,

                // Car attributes
                const int numberOfDoorsP,
                const int numberOfSeatsP

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
            vehicles::Vehicle* clone() const override;

            // Writes the car data to a text stream.
            void writeToStream(QTextStream& out) const override;

            // Reads the car data from a text stream
            void readFromStream(QTextStream& in) override;

    };

};
