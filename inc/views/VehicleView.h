
#pragma once

#include "vehicles/vehicles.h"
#include "CarView.h"
#include "MotorcycleView.h"

#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

namespace views {

    class VehicleView : public QWidget {

        Q_OBJECT

        protected:

            vehicles::Vehicle* vehicle;
            QVBoxLayout *vBoxLayout;
            QLabel *typeIdLabel;
            QLabel *vehicleIdLabel;
            QLineEdit *brandField;
            QLineEdit *modelField;
            QLineEdit *pricePerDayField;
            QLabel *isRentedLabel;
            views::CarView *carView;
            views::MotorcycleView *motorcycleView;

            void refreshFields();

        public:

            VehicleView(
                QWidget *parent = nullptr,
                vehicles::Vehicle* vehicleP = nullptr
            );

            const vehicles::Vehicle* getVehicle() const;

            void setVehicle(
                vehicles::Vehicle* vehicleP
            );

        // slots:

            void handleVehicleUpdated(const QString vehicleId);

        signals:

            void vehicleUpdated(const QString vehicleId);

    };
};
