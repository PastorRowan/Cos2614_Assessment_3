
#pragma once

#include "models/Motorcycle.h"

#include <QWidget>
#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class MotorcycleView : public QWidget {

        Q_OBJECT

        private:

            models::OptionalMotorcycleData optionalMotorcycleData;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

        protected:

            void refreshFields();

        public:

            MotorcycleView(
                QWidget *parent = nullptr
            );

            void setMotorcycleData(
                const models::OptionalMotorcycleData optionalMotorcycleDataP
            );

    };

};
