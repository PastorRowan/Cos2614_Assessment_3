
#pragma once

#include "models/models.h"
#include "CarView.h"
#include "MotorcycleView.h"

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace views {

    class VehicleView : public QWidget {

        Q_OBJECT

        protected:

            models::OptionalVehicleData optionalVehicleData;
            QVBoxLayout *vBoxLayout;
            QWidget *vehicleFormWidget;
            QFormLayout *vehicleFormLayout;
            QLabel *VehicleTypeIdLabel;
            QLabel *vehicleIdLabel;
            QLineEdit *brandField;
            QLineEdit *modelField;
            QLineEdit *pricePerDayField;
            QLabel *isRentedLabel;
            views::CarView *carView;
            views::MotorcycleView *motorcycleView;
            QPushButton *saveChangesButton;

            void refreshFields();

        public:

            VehicleView(
                QWidget *parent = nullptr
            );

            void setVehicleData(
                const models::Vehicle* vehicle
            );

        // slots:

            void handleVehicleSelected(models::Vehicle* vehicleP);

        signals:

            void vehicleUpdated(const long long vehicleId);

    };
};
