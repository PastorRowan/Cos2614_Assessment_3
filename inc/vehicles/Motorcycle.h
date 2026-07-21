
#pragma once

#include "vehicles/Vehicle.h"

#include <QStringList>

class QString;

namespace vehicles {

    // Represents a motorcycle vehicle type
    class Motorcycle : public vehicles::Vehicle {

        private:

            vehicles::TypeId typeId = vehicles::TypeId::motorCycle;
            int engineCapacityCC = -1;

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

                // Vehicle attributes
                const QString idP,
                const QString brandP,
                const QString modelP,
                const double pricePerDayP,
                const bool isRentedP,

                // Motorcycle attributes
                const int engineCapacityCCP

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
            vehicles::Vehicle* clone() const override;

            // Writes the motorcycle data to a text stream
            void writeToStream(QTextStream& out) const override;

            // Reads motorcycle data from a text stream
            void readFromStream(QTextStream& in) override;

    };

};
