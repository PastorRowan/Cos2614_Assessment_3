
#pragma once

#include "models/Motorcycle.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QFormLayout;
class QLineEdit;

namespace views {

    class MotorcycleDataView : public QWidget {

        Q_OBJECT

        private:

            std::shared_ptr<models::MotorcycleData> motorcycleData;
            QFormLayout *motorcycleFormLayout;
            QLineEdit *engineCapacityCCField;

            void refreshFields();

        public:

            MotorcycleDataView(
                QWidget *parent = nullptr
            );

            void setMotorcycleData(
                std::shared_ptr<models::MotorcycleData> motorcycleDataP
            );

            bool hasMotorcycleData() const;

        // slots:

            void handleChangeEngineCapacityCCField(
                const QString text
            );

    };

};
