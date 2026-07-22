
#pragma once

#include "vehicles/vehicles.h"

#include <QObject>
#include <QString>
#include <QVector>

// Manages vehicle storage, persistence, and rental operations
class VehiclesFile : public QObject {

    Q_OBJECT

    private:

        // Alias for the internal vehicle container type
        typedef QVector<vehicles::Vehicle*> VehiclesQVector;

        // File path for vehicle data storage
        QString vehiclesFileLocation = "Not initialised";

        // File path used to store the current vehicle ID counter
        QString currentVehicleIdFileLocation = "Not initialised";

        // Internal container storing all vehicle objects
        VehiclesQVector vehiclesQVector;

        // Ensures a file path exists
        static void ensurePathAndFileExist(
            const QString& path,
            const QString& initialContents,
            bool& ok
        );

        // Sets the vehicle data file location
        void setVehiclesFileLocation(const QString vehiclesFileLocationP);

        // Saves the current vehicle collection to disk
        void saveVehiclesQVector(bool& ok);

        // Loads vehicle data from storage
        void loadVehiclesQVector(bool& ok);

        // Releases all dynamically allocated vehicle objects
        void destroyVehiclesQVector();

        // Current numeric vehicle ID counter
        long long currentVehicleId = -1;

        // Validates a numeric vehicle ID
        static bool isVehicleIdValid(const long long id);

        // Validates a vehicle ID represented as a QString
        static bool isVehicleIdValid(const QString& id);

        // Converts the current vehicle ID to a QString
        QString vehicleIdToQString() const;

        // Gets the current vehicle ID counter
        long long getCurrentVehicleId() const;

        // Sets the current vehicle ID counter
        void setCurrentVehicleId(const long long newCurrentVehicleId);

        // Decrements the current vehicle ID counter
        void decrementCurrentVehicleId();

        // Increments the current vehicle ID counter
        void incrementCurrentVehicleId();

        // Increments and saves the current vehicle ID
        void incrementAndSaveCurrentVehicleId(bool& ok);

        // Sets the current vehicle ID file location
        void setCurrentIdFileLocation(const QString currentVehicleIdFileLocationP);

        // Saves the current vehicle ID to storage
        void saveCurrentVehicleId(bool& ok);

        // Loads the current vehicle ID from storage
        void loadCurrentVehicleId(bool& ok);

    public:

        // Constructs a VehiclesFile manager
        VehiclesFile(
            const QString vehiclesFileLocationParameter,
            const QString currentVehicleIdFileLocationParameter,
            QObject* parent = nullptr
        );

        /**
         * Destructor
         * Releases all allocated vehicle resources
         */
        ~VehiclesFile();

        // Gets the vehicle data file location
        const QString& getVehiclesFileLocation() const;

        // Gets the current vehicle ID file location
        const QString& getCurrentIdFileLocation() const;

        // Gets the internal vehicle collection
        const VehiclesQVector& getVehiclesQVector() const;

        /**
         * Adds a new car to the collection
         * Automatically generates a unique vehicle ID
         */
        void addCar(

            // Vehicle attributes
            const QString brandP,
            const QString modelP,
            const double pricePerDayP,

            // Car attributes
            const int numberOfDoorsP,
            const int numberOfSeatsP,

            // Success or error message
            QString& message

        );

        /**
         * Adds a new motorcycle to the collection
         * Automatically generates a unique vehicle ID
         */
        void addMotorcycle(

            const QString brandP,
            const QString modelP,
            const double pricePerDayP,

            const int engineCapacityCCP,

            QString& message

        );

        /**
         * Searches for a vehicle by its ID
         * Returns a pointer to the matching vehicle, or nullptr if not found
         */
        const vehicles::Vehicle* searchVehicleById(const QString& vehicleId) const;

        // Marks a vehicle as rented using its ID
        void rentVehicleById(
            const QString& vehicleId,
            QString& message
        );

        // Marks a rented vehicle as returned (not rented)
        void returnVehicleById(
            const QString& vehicleId,
            QString& message
        );

    signals:

        /// Emitted whenever the vehicle collection changes.
        void vehiclesChanged();

        /// Emitted after a vehicle is added.
        void vehicleAdded(const vehicles::Vehicle* vehicle);

        /// Emitted after a vehicle is removed.
        void vehicleRemoved(const QString& vehicleId);

        /// Emitted after a vehicle's data changes.
        void vehicleUpdated(const QString& vehicleId);

        /// Emitted after a vehicle is rented.
        void vehicleRented(const QString& vehicleId);

        /// Emitted after a vehicle is returned.
        void vehicleReturned(const QString& vehicleId);

};
