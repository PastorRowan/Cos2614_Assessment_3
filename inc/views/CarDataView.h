
#pragma once

#include "models/Car.h"

#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class CarDataView : public QWidget {

        Q_OBJECT

        private:

            models::OptionalCarData optionalCarData;
            QFormLayout *carFormLayout;
            QLineEdit *numberOfDoorsField;
            QLineEdit *numberOfSeatsField;

            void refreshFields();

        public:

            CarDataView(
                QWidget *parent = nullptr
            );

            models::OptionalCarData getVehicleData();

            void setCarData(
                const models::OptionalCarData optionalCarDataP
            );

        // slots:

        void handleChangeNumberOfDoorsField(
            const QString& text
        );

        void handleChangeNumberOfSeatsField(
            const QString& text
        );

    };

};
