
#pragma once

#include <QObject>
#include <QString>
#include <limits>
#include <memory>
class QTextStream;

namespace models {

    // Enumeration identifying the type of vehicle
    enum class VehicleTypeId {
        car,
        motorCycle,
        count
    };

    // Converts the type identifier to a QString
    QString vehicleTypeIdToPrettyQString(VehicleTypeId vehicleTypeId);

    // Default vehicle type identifier
    const VehicleTypeId DEFAULT_VEHICLE_TYPE_ID = VehicleTypeId::count;

    // Default vehicle identifier
    const long long DEFAULT_VEHICLE_ID = -1;

    // Default vehicle brand
    const QString DEFAULT_BRAND = "";

    // Default vehicle model
    const QString DEFAULT_MODEL = "";

    // Default daily rental price
    const double DEFAULT_PRICE_PER_DAY = -1.0;

    // Minimum daily rental price
    const double MINIMUM_PRICE_PER_DAY = 0.0;

    // Maximum daily rental price
    const double MAXIMUM_PRICE_PER_DAY = std::numeric_limits<double>::max();

    // Default rental status
    const bool DEFAULT_IS_RENTED = false;

    /**
     * VehicleData
     * Stores the common data associated with a vehicle
     *
     * This abstract base structure contains the properties shared by all
     * vehicle types
     * Derived structures add type-specific fields and provide
     * implementations for validation and cloning
     */
    struct VehicleData {

        // The type of vehicle
        VehicleTypeId vehicleTypeId = DEFAULT_VEHICLE_TYPE_ID;

        // The unique vehicle identifier
        long long vehicleId = DEFAULT_VEHICLE_ID;

        // The vehicle manufacturer
        QString brand = DEFAULT_BRAND;

        // The vehicle model
        QString model = DEFAULT_MODEL;

        // The rental price per day
        double pricePerDay = DEFAULT_PRICE_PER_DAY;

        // Indicates whether the vehicle is currently rented
        bool isRented = DEFAULT_IS_RENTED;

        /**
         * Constructs a VehicleData object
         *
         * vehicleTypeIdP - The vehicle type
         * vehicleIdP - The unique vehicle identifier
         * brandP - The vehicle brand
         * modelP - The vehicle model
         * pricePerDayP - The daily rental price
         * isRentedP - Whether the vehicle is currently rented
         */
        VehicleData(
            VehicleTypeId vehicleTypeIdP = DEFAULT_VEHICLE_TYPE_ID,
            long long vehicleIdP = DEFAULT_VEHICLE_ID,
            const QString brandP = DEFAULT_BRAND,
            const QString modelP = DEFAULT_MODEL,
            double pricePerDayP = DEFAULT_PRICE_PER_DAY,
            bool isRentedP = DEFAULT_IS_RENTED
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

        // Returns the vehicle identifier as a QString
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

        // Destroys the vehicle data object
        virtual ~VehicleData() = default;

        /**
         * Validates the stored vehicle data
         *
         * message - Receives a description of the validation error if
         * validation fails
         *
         * Returns true if the data is valid, otherwise false
         */
        virtual bool isValid(QString& message) const = 0;

        /**
         * Creates a deep copy of the vehicle data
         *
         * Returns a unique pointer to the cloned vehicle data
         */
        virtual std::unique_ptr<VehicleData> clone() const = 0;

    };

    /**
     * Vehicle
     * Abstract base class representing a vehicle
     *
     * Defines the common interface implemented by all vehicle types
     * Derived classes provide storage for their specific VehicleData implementation,
     * support cloning, serialisation, and formatted string conversion
     */
    class Vehicle : public QObject {

        Q_OBJECT

        private:

        public:

            /**
             * Default constructor, creates a vehicle in an uninitialized state.
             * Most fields contain placeholder values and should be set before use.
             */
            explicit Vehicle() {};

            /**
             * Parameterized constructor
             * Initializes QObject and all core properties of a vehicle
             */
            explicit Vehicle(
                QObject *parent
            );

            /**
             * Virtual destructor
             * Ensures proper cleanup of derived vehicle objects
             */
            virtual ~Vehicle() = default;

            // Returns a constant reference to the vehicle data
            virtual const VehicleData& getVehicleData() const = 0;

            // Returns a mutable reference to the vehicle data
            virtual VehicleData& getVehicleData() = 0;

            /**
             * @brief Replaces the vehicle data
             *
             * vehicleData - The new vehicle data
             */
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

            /**
             * Emitted when a vehicle has been updated
             *
             * vehicleId - The identifier of the updated vehicle
             */
            void vehicleUpdated(const long long vehicleId);

    };

    // Stream insertion operator for Vehicle
    QTextStream& operator<<(QTextStream& out, const Vehicle& vehicle);

    // Stream extraction operator for Vehicle
    QTextStream& operator>>(QTextStream& in, Vehicle& vehicle);

};
