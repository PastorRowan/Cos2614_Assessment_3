
#pragma once

#include <QObject>
#include <QString>
#include <memory>
class QTextStream;

namespace models {

    // Enumeration identifying the type of vehicle.
    enum class VehicleTypeId {
        car,
        motorCycle,
        count
    };

    struct VehicleData {

        VehicleTypeId vehicleTypeId = VehicleTypeId::count;
        long long vehicleId = -1;
        QString brand = "Not initialised";
        QString model = "Not initialised";
        double pricePerDay = -1.0;
        bool isRented = false;

        VehicleData(
            VehicleTypeId vehicleTypeIdP = VehicleTypeId::count,
            long long vehicleIdP = -1,
            const QString brandP = "Not initialised",
            const QString modelP = "Not initialised",
            double pricePerDayP = -1.0,
            bool isRentedP = false
        ):
            vehicleTypeId(vehicleTypeIdP),
            vehicleId(vehicleIdP),
            brand(brandP),
            model(modelP),
            pricePerDay(pricePerDayP),
            isRented(isRentedP) {
        };

        // Converts the vehicle type ID to a QString
        QString getVehicleTypeIdAsQString() const {
            return QString::number(static_cast<int>(vehicleTypeId));
        };

        QString getVehicleIdAsQString() const {
            return QString::number(vehicleId);
        };

        // Converts the price per day to QString
        QString getPricePerDayAsQString() const {
            return QString::number(pricePerDay);
        };

        // Converts rental status to QString
        QString getIsRentedAsQString() const {
            return QString(isRented ? "Yes" : "No");
        };

        virtual ~VehicleData() = default;

        virtual std::unique_ptr<VehicleData> clone() const = 0;

    };

    // Abstract base class representing a generic vehicle.
    class Vehicle : public QObject {

        Q_OBJECT

        private:

            // VehicleData data {};

        public:

            /**
             * Default constructor, creates a vehicle in an uninitialized state.
             * Most fields contain placeholder values and should be set before use.
             */
            Vehicle() {};

            /**
             * Parameterized constructor
             * Initializes QObject and all core properties of a vehicle
             */
            Vehicle(
                QObject *parent
            );

            /**
             * Virtual destructor
             * Ensures proper cleanup of derived vehicle objects
             */
            virtual ~Vehicle() = default;

            virtual const VehicleData& getVehicleData() const = 0;

            virtual VehicleData& getVehicleData() = 0;

            virtual void setVehicleData(const models::VehicleData& vehicleData) = 0;

            // Gets the vehicle type identifier
            models::VehicleTypeId getVehicleTypeId() const;

            // Converts the type identifier to a QString
            QString getVehicleTypeIdAsQString() const;

            // Sets the vehicle type identifier
            void setVehicleTypeId(const VehicleTypeId newVehicleTypeId);

            // Gets the unique vehicle ID
            long long getVehicleId() const;

            QString getVehicleIdAsQString() const;

            // Sets the unique vehicle ID
            void setVehicleId(const long long newVehicleId);

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

            // Converts the price per day to a QString
            QString getPricePerDayAsQString() const;

            // Sets the rental price per day
            void setPricePerDay(const double newPricePerDay);

            // Checks whether the vehicle is currently rented
            bool getIsRented() const;

            // Converts the rental status to a QString (0 = not rented, 1 = is rented)
            QString getIsRentedAsQString() const;

            // Sets the rental status of the vehicle
            void setIsRented(const bool newIsRented);

            // Converts a rental status QString into a boolean value
            static bool isRentedQStringToBool(const QString& isRentedQString);

            // Returns a string representation of the vehicle
            virtual QString toQString() const = 0;

            // Creates a deep copy of the vehicle object
            virtual models::Vehicle* clone() const = 0;

            // Writes the vehicle data to a text stream
            virtual void writeToStream(QTextStream& out) const = 0;

            // Reads the vehicle data from a text stream
            virtual void readFromStream(QTextStream& in) = 0;

        signals:

            void vehicleUpdated(const long long vehicleId);

    };

    // Stream insertion operator for Vehicle
    QTextStream& operator<<(QTextStream& out, const Vehicle& vehicle);

    // Stream extraction operator for Vehicle
    QTextStream& operator>>(QTextStream& in, Vehicle& vehicle);

};
