
#pragma once

#include "vehicles/vehicles.h"

#include <QString>
#include <QVector>

// Manages vehicle storage, persistence, and rental operations
class VehiclesFile {

    private:

        // Alias for the internal vehicle container type
        typedef QVector<vehicles::Vehicle*> VehiclesQVector;

        // File path for vehicle data storage
        QString vehiclesFileLocation = "Not initialised";

        // File path used to store the current vehicle ID counter
        QString currentVehicleIdFileLocation = "Not initialised";

        // Ensures a file path exists
        static void ensurePathAndFileExist(
            const QString& path,
            const QString& initialContents,
            bool& ok
        );

        // Internal container storing all vehicle objects
        VehiclesQVector vehiclesQVector;

        // Gets the internal vehicle collection
        const VehiclesQVector& getVehiclesQVector() const;

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
            bool& ok
        );

        // Copy constructor
        VehiclesFile(const VehiclesFile& other, bool& ok);

        /**
         * Destructor
         * Releases all allocated vehicle resources
         */
        ~VehiclesFile();

        /**
         * Assignment operator
         * Performs deep-copy assignment from another VehiclesFile object
         */
        VehiclesFile& operator=(const VehiclesFile& rightVehicleFile);

        // Gets the vehicle data file location
        const QString& getVehiclesFileLocation() const;

        // Gets the current vehicle ID file location
        const QString& getCurrentIdFileLocation() const;

        // Converts the vehicle collection into a formatted QString
        QString composeAllVehicles() const;

        // Creates a formatted list of available (not rented) vehicles
        QString composeAvailableVehiclesOnly() const;

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

};
