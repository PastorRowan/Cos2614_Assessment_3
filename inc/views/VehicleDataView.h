
#pragma once

#include "models/models.h"
#include "CarDataView.h"
#include "MotorcycleDataView.h"

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace views {

    class VehicleDataView : public QWidget {

        Q_OBJECT

        protected:

            models::OptionalVehicleData optionalVehicleData;
            QVBoxLayout *vBoxLayout;
            QWidget *vehicleFormWidget;
            QFormLayout *vehicleFormLayout;
            QLabel *vehicleTypeIdLabel;
            QLabel *vehicleIdLabel;
            QLineEdit *brandField;
            QLineEdit *modelField;
            QLineEdit *pricePerDayField;
            QLabel *isRentedLabel;
            views::CarDataView *carDataView;
            views::MotorcycleDataView *motorcycleDataView;
            QPushButton *saveChangesButton;

            void refreshFields();

        public:

            VehicleDataView(
                QWidget *parent = nullptr
            );

            void setVehicleData(
                const models::VehicleData& vehicleData
            );

        // slots:

            void handleVehicleSelected(
                const models::VehicleData& vehicleData
            );

            void handleChangeBrandField(
                const QString& text
            );

            void handleChangeModelField(
                const QString& text
            );

            void handleChangepPricePerDayField(
                const QString& text
            );

            void handleSaveChanges();

        signals:

            void updateVehicle(
                const models::VehicleData& vehicleData
            );

    };

};
