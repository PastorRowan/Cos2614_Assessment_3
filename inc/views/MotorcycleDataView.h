
#pragma once

#include "models/Motorcycle.h"

#include <QWidget>
#include <QObject>
class QFormLayout;
class QLineEdit;

namespace views {

    class MotorcycleDataView : public QWidget {

        Q_OBJECT

        private:

            models::MotorcycleData* motorcycleData;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

            void refreshFields();

        public:

            MotorcycleDataView(
                QWidget *parent = nullptr
            );

            void setMotorcycleData(
                models::MotorcycleData* motorcycleDataP
            );

            bool hasMotorcycleData() const;

        // slots:

            void handleChangeEngineCapacityCCField(
                const QString& text
            );

    };

};
