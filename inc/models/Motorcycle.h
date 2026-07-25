
#pragma once

#include "models/Vehicle.h"

class QObject;
class QString;

namespace models {

    struct MotorcycleData : public VehicleData {
        models::VehicleTypeId VehicleTypeId = models::VehicleTypeId::motorCycle;
        int engineCapacityCC = -1;
    };

    // Represents a motorcycle vehicle type
    class Motorcycle : public models::Vehicle {

        private:

            MotorcycleData data;

        public:

            /**
             * Default constructor
             * Creates an uninitialized Motorcycle object with default placeholder values
             */
            Motorcycle() {};

            /**
             * Parameterized constructor
             * Initializes a Motorcycle instance with all required vehicle attributes
             * and its specific engine capacity attribute
             */
            Motorcycle(
                // QObject parent
                QObject *parent,
                MotorcycleData data
            );

            // Destructor
            ~Motorcycle() {};

            // Gets the engine capacity
            int getEngineCapacityCC() const;

            // Sets the engine capacity
            void setEngineCapacityCC(const int newEngineCapacityCC);

            // Converts the engine capacity to a QString
            QString engineCapacityCCToQString() const;

            // Converts the motorcycle object to a formatted QString
            QString toQString() const override;

            // Creates a deep copy of the motorcycle object
            models::Vehicle* clone() const override;

            // Writes the motorcycle data to a text stream
            void writeToStream(QTextStream& out) const override;

            // Reads motorcycle data from a text stream
            void readFromStream(QTextStream& in) override;

    };

};
