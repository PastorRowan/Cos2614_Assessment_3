
#pragma once

#include "models/models.h"

#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class CarView : public QWidget {

        Q_OBJECT

        private:

            models::Car* car;
            QFormLayout *carFormLayout;
            QLineEdit *numberOfDoorsField;
            QLineEdit *numberOfSeatsField;

        protected:

            void refreshFields();

        public:

            CarView(
                QWidget *parent = nullptr,
                models::Car* carP = nullptr
            );

            const models::Car* getCar() const;

            void setCar(models::Car* newCar);

    };

};
