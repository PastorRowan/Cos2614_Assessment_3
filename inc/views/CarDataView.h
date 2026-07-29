
#pragma once

#include "models/Car.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QFormLayout;
class QLineEdit;

namespace views {

    class CarDataView : public QWidget {

        Q_OBJECT

        private:

            std::shared_ptr<models::CarData> carData;
            QFormLayout *carFormLayout;
            QLineEdit *numberOfDoorsField;
            QLineEdit *numberOfSeatsField;

            void refreshFields();

        public:

            explicit CarDataView(
                QWidget *parent = nullptr
            );

            void setCarData(
                std::shared_ptr<models::CarData> carDataP
            );

            bool hasCarData() const;

        // slots:

            void handleChangeNumberOfDoorsField(
                const QString text
            );

            void handleChangeNumberOfSeatsField(
                const QString text
            );

    };

};
