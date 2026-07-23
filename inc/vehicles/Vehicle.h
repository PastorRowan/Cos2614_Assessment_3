
#pragma once

#include <QString>
#include <QStringList>

class QTextStream;

namespace vehicles {

    // Enumeration identifying the type of vehicle.
    enum class TypeId {
        car,
        motorCycle,
        count
    };

    // Abstract base class representing a generic vehicle.
    class Vehicle {

        private:

            vehicles::TypeId typeId = vehicles::TypeId::count;
            QString vehicleId = "Not initialised";
            QString brand = "Not initialised";
            QString model = "Not initialised";
            double pricePerDay = -1.0;
            bool isRented = false;

        public:

            /**
             * Default constructor, creates a vehicle in an uninitialized state.
             * Most fields contain placeholder values and should be set before use.
             */
            Vehicle() {};

            /**
             * Parameterized constructor
             * Initializes all core properties of a vehicle
             */
            Vehicle(
                const vehicles::TypeId typeIdP,
                const QString vehicleIdP,
                const QString brandP,
                const QString modelP,
                const double pricePerDayP,
                const bool isRentedP
            );

            /**
             * Virtual destructor
             * Ensures proper cleanup of derived vehicle objects
             */
            virtual ~Vehicle() = default;

            // Gets the vehicle type identifier
            vehicles::TypeId getTypeId() const;

            // Sets the vehicle type identifier
            void setTypeId(const TypeId newTypeId);

            // Converts the type identifier to a QString
            QString typeIdToQString() const;

            // Gets the unique vehicle ID
            QString getVehicleId() const;

            // Sets the unique vehicle ID
            void setVehicleId(const QString& newVehicleId);

            // Gets the vehicle brand
            QString getBrand() const;

            // Sets the vehicle brand
            void setBrand(const QString& newBrand);

            // Gets the vehicle model
            QString getModel() const;

            // Sets the vehicle model.
            void setModel(const QString& newModel);

            // Gets the rental price per day
            double getPricePerDay() const;

            // Sets the rental price per day
            void setPricePerDay(const double newPricePerDay);

            // Converts the price per day to a QString
            QString pricePerDayToQString() const;

            // Checks whether the vehicle is currently rented
            bool getIsRented() const;

            // Sets the rental status of the vehicle
            void setIsRented(const bool newIsRented);

            // Converts the rental status to a QString (0 = not rented, 1 = is rented)
            QString isRentedToQString() const;

            // Converts a rental status QString into a boolean value
            static bool isRentedQStringToBool(const QString& isRentedQString);

            // Returns a string representation of the vehicle
            virtual QString toQString() const = 0;

            // Creates a deep copy of the vehicle object
            virtual vehicles::Vehicle* clone() const = 0;

            // Writes the vehicle data to a text stream
            virtual void writeToStream(QTextStream& out) const = 0;

            // Reads the vehicle data from a text stream
            virtual void readFromStream(QTextStream& in) = 0;

    };

    // Stream insertion operator for Vehicle
    QTextStream& operator<<(QTextStream& out, const Vehicle& vehicle);

    // Stream extraction operator for Vehicle
    QTextStream& operator>>(QTextStream& in, Vehicle& vehicle);

};
