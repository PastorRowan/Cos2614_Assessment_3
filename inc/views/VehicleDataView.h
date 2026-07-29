
#pragma once

#include "models/Vehicle.h"
#include "CarDataView.h"
#include "MotorcycleDataView.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QVBoxLayout;
class QFormLayout;
class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class QString;

namespace views {

    class VehicleDataView : public QWidget {

        Q_OBJECT

        protected:

            std::shared_ptr<models::VehicleData> vehicleData;
            QVBoxLayout *vBoxLayout;
            QWidget *vehicleFormWidget;
            QFormLayout *vehicleFormLayout;
            QLabel *vehicleTypeIdLabel;
            QLabel *vehicleIdLabel;
            QLineEdit *brandField;
            QLineEdit *modelField;
            QLineEdit *pricePerDayField;
            QComboBox *isRentedComboBox;
            views::CarDataView *carDataView;
            views::MotorcycleDataView *motorcycleDataView;
            QPushButton *confirmButton;

            void refreshFields();

        public:

            VehicleDataView(
                QWidget *parent = nullptr
            );

            const std::shared_ptr<const models::VehicleData> getVehicleData() const;

            void setVehicleData(
                const std::shared_ptr<const models::VehicleData> vehicleDataP
            );

            bool hasVehicle() const;

            void setConfirmButtonText(const QString text);

        // slots:

            void handleVehicleSelected(
                const std::shared_ptr<const models::VehicleData> vehicleDataP
            );

            void handleChangeBrandField(
                const QString text
            );

            void handleChangeModelField(
                const QString text
            );

            void handleChangepPricePerDayField(
                const QString text
            );

            void handleChangeIsRentedComboBox(
                int index
            );

            void handleConfirm();

        signals:

            void confirmVehicle(
                const std::shared_ptr<const models::VehicleData> vehicleData
            );

    };

};
