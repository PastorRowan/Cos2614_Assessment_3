
#pragma once

#include "models/models.h"

#include <QWidget>
#include <QObject>
#include <QFormLayout>
#include <QLineEdit>

namespace views {

    class MotorcycleView : public QWidget {

        Q_OBJECT

        private:

            models::Motorcycle* motorcycle;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

        protected:

            void refreshFields();

        public:

            MotorcycleView(
                QWidget *parent = nullptr,
                models::Motorcycle* motorcycleP = nullptr
            );

            const models::Motorcycle* getMotorcycle() const;

            void setMotorcycle(models::Motorcycle* newMotorcycle);

    };

};
