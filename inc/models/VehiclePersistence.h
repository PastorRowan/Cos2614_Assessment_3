
#pragma once

#include "models/models.h"

#include <QObject>
#include <QString>
class QVector;

namespace models {

    // Manages vehicle storage, persistence, and rental operations
    class VehiclePersistence : public QObject {

        Q_OBJECT

        private:

            // File path for vehicle data storage
            QString VehicleFileLocation = "Not initialised";

            // Sets the vehicle data file location
            void setVehicleFileLocation(const QString VehicleFileLocationP);

            // Saves the current vehicle collection to disk
            void saveVehicles(bool& ok);

            // Loads vehicle data from storage
            void loadVehicles(bool& ok);

        public:

            // Constructs a VehiclePersistence manager
            VehiclePersistence(
                QObject* parent,
                const QString VehicleFileLocationP
            );

            /**
            * Destructor
            */
            ~VehiclePersistence() = default;

            void clear();

        // slots:

            void handleVehiclesUpdated();

    };

};
