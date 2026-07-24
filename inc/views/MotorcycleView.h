
#pragma once

#include "vehicles/vehicles.h"

#include <QWidget>
#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class MotorcycleView : public QWidget {

        Q_OBJECT

        private:

            vehicles::Motorcycle* motorcycle;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

        protected:

            void refreshFields();

        public:

            MotorcycleView(
                QWidget *parent = nullptr,
                vehicles::Motorcycle* motorcycleP = nullptr
            );

            const vehicles::Motorcycle* getMotorcycle() const;

            void setMotorcycle(vehicles::Motorcycle* newMotorcycle);

    };

};
