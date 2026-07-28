
#pragma once

#include "models/Vehicle.h"
#include "views/VehicleDataView.h"

#include <QDialog>
#include <QObject>
class QVBoxLayout;
class QLabel;
class QComboBox;
class QWidget;

namespace dialogues {

    // Dialogue responsible for interactively adding a motorcycle
    class AddVehicleDialogue : public QDialog {

        Q_OBJECT

        private:

            std::unique_ptr<models::VehicleData> vehicleData;

            QVBoxLayout *vBoxLayout;
            QLabel *title;
            QComboBox *vehicleTypeComboBox;
            views::VehicleDataView *vehicleDataView;

        // private slots:

            void handleVehicleTypeChanged(
                int vehicleTypeId
            );

            void handleAddVehicle(
                const models::VehicleData& vehicleData
            );

        public:

            explicit AddVehicleDialogue(
                QWidget *parent
            );

            ~AddVehicleDialogue() = default;

            void open();

        // slots:

        signals:

            void addVehicle(
                const models::VehicleData& vehicleData
            );

    };

};
