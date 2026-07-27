
#pragma once

#include "models/Motorcycle.h"

#include <QWidget>
#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class MotorcycleDataView : public QWidget {

        Q_OBJECT

        private:

            models::OptionalMotorcycleData optionalMotorcycleData;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

            void refreshFields();

        public:

            MotorcycleDataView(
                QWidget *parent = nullptr
            );

            models::OptionalMotorcycleData getVehicleData();

            void setMotorcycleData(
                const models::OptionalMotorcycleData optionalMotorcycleDataP
            );

        // slots:

            void handleChangeEngineCapacityCCField(
                const QString& text
            );

    };

};
