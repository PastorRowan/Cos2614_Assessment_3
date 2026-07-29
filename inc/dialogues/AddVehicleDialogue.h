
#pragma once

#include "models/Vehicle.h"
#include "views/VehicleDataView.h"

#include <QDialog>
#include <QObject>
#include <memory>
class QVBoxLayout;
class QLabel;
class QComboBox;
class QWidget;

namespace dialogues {

    /**
     * AddVehicleDialogue
     * Dialog used to create and add a new vehicle.
     *
     * This dialog allows the user to select the type of vehicle to create
     * (for example, a car or motorcycle) and enter the corresponding vehicle
     * information using a dynamically selected
     * views::VehicleDataView. Once the user confirms the input, the dialog
     * emits the addVehicle() signal containing the completed vehicle data.
     */
    class AddVehicleDialogue : public QDialog {

        Q_OBJECT

        private:

            // Main vertical layout for the dialog
            QVBoxLayout *vBoxLayout;

            // Displays the dialog title
            QLabel *title;

            // Allows the user to select the type of vehicle to add
            QComboBox *vehicleTypeComboBox;

            // Displays the input fields for the selected vehicle type
            views::VehicleDataView *vehicleDataView;

        // private slots:

            /**
             * Handles changes to the selected vehicle type
             * Updates the displayed VehicleDataView to match the selected vehicle type
             */
            void handleVehicleTypeChanged(
                int vehicleTypeId
            );

            /**
             * Handles the request to add a vehicle
             *
             * Emits the addVehicle() signal with the supplied vehicle data and typically closes the dialog
             *
             * vehicleData - Shared pointer to the vehicle data entered by the user
             */
            void handleAddVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

        public:

            /**
             * Constructs an AddVehicleDialogue
             *
             * The parent widget that owns this dialog
             */
            explicit AddVehicleDialogue(
                QWidget *parent
            );

            // Deconstructor
            ~AddVehicleDialogue() = default;

            // Opens the dialog for user interaction.
            void open();

        // slots:

        // currently empty

        signals:

            /**
             * Emitted when the user has successfully entered a vehicle.
             *
             * vehicleData - Shared pointer to the newly entered vehicle data.
             */
            void addVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

    };

};
