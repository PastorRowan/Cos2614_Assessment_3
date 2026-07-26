
#pragma once

#include "models/Car.h"

#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class CarView : public QWidget {

        Q_OBJECT

        private:

            models::OptionalCarData optionalCarData;
            QFormLayout *carFormLayout;
            QLineEdit *numberOfDoorsField;
            QLineEdit *numberOfSeatsField;

        protected:

            void refreshFields();

        public:

            CarView(
                QWidget *parent = nullptr
            );

            void setCarData(
                const models::OptionalCarData optionalCarDataP
            );

    };

};
