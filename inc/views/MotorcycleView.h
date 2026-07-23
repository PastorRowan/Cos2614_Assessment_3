
#pragma once

#include "vehicles/vehicles.h"

#include <QWidget>
#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>

namespace views {

    class MotorcycleView : public QWidget {

        Q_OBJECT

        private:

            vehicles::Motorcycle* motorcycle;
            QVBoxLayout *vBoxLayout;
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
