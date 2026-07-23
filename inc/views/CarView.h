
#pragma once

#include "VehicleView.h"
#include "vehicles/vehicles.h"

#include <QObject>
#include <QLineEdit>
#include <QVBoxLayout>

namespace views {

    class CarView : public QWidget {

        Q_OBJECT

        private:

            vehicles::Car* car;
            QVBoxLayout *vBoxLayout;
            QLineEdit *numberOfDoorsField;
            QLineEdit *numberOfSeatsField;

        protected:

            void refreshFields();

        public:

            CarView(
                QWidget *parent = nullptr,
                vehicles::Car* carP = nullptr
            );

            const vehicles::Car* getCar() const;

            void setCar(vehicles::Car* newCar);

    };

};
