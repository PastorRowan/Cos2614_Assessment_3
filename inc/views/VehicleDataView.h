
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

    /**
     * A widget for viewing and editing vehicle information
     *
     * Displays the common properties shared by all vehicle types, including
     * brand, model, rental status, and price per day
     * Depending on the selected vehicle type, the widget also displays either a
     * CarDataView or MotorcycleDataView to allow editing of
     * vehicle-specific properties
     *
     * When the user confirms their changes, the widget emits the
     * confirmVehicle() signal containing the updated vehicle data
     */
    class VehicleDataView : public QWidget {

        Q_OBJECT

        protected:

            // The currently displayed vehicle data
            std::shared_ptr<models::VehicleData> vehicleData = nullptr;

            // The main vertical layout for the widget
            QVBoxLayout *vBoxLayout;

            // Widget containing the vehicle form
            QWidget *vehicleFormWidget;

            // Form layout containing the common vehicle fields
            QFormLayout *vehicleFormLayout;

            // Displays the vehicle type
            QLabel *vehicleTypeIdLabel;

            // Displays the vehicle identifier
            QLabel *vehicleIdLabel;

            // Input field for the vehicle brand
            QLineEdit *brandField;

            // Input field for the vehicle model
            QLineEdit *modelField;

            // Input field for the vehicle rental price per day
            QLineEdit *pricePerDayField;

            // Selection box indicating whether the vehicle is rented
            QComboBox *isRentedComboBox;

            // View used for editing car-specific properties
            views::CarDataView *carDataView;

            // View used for editing motorcycle-specific properties
            views::MotorcycleDataView *motorcycleDataView;

            // Button used to confirm changes
            QPushButton *confirmButton;

            /**
             * Updates all fields to reflect the current vehicle data
             *
             * Refreshes both the common vehicle fields and the appropriate
             * type-specific view
             * If no vehicle data is assigned, the fields are cleared or reset to their default state
             */
            void refreshFields();

        public:

            /**
             * Constructs a VehicleDataView widget
             *
             * Creates the user interface and initializes all controls
             *
             * parent The parent widget, defaults to nullptr
             */
            explicit VehicleDataView(
                QWidget *parent = nullptr
            );

            /**
             * Returns the currently displayed vehicle data
             *
             * Returns a shared pointer to the current vehicle data, or nullptr
             * if no vehicle has been assigned
             */
            std::shared_ptr<const models::VehicleData> getVehicleData() const;

            /**
             * Assigns the vehicle data displayed by the view
             *
             * The widget immediately refreshes all fields to display the
             * supplied vehicle information
             *
             * vehicleDataP - Shared pointer to the vehicle data to display
             */
            void setVehicleData(
                std::shared_ptr<const models::VehicleData> vehicleDataP
            );

            /**
             * Determines whether the view currently has vehicle data
             *
             * Returns true if a VehicleData object has been assigned, otherwise false
             */
            bool hasVehicle() const;

            /**
             * Sets the text displayed on the confirmation button
             *
             * text - The button text
             */
            void setConfirmButtonText(const QString text);

        // slots:

            /**
             * Displays the selected vehicle
             *
             * Updates the widget to display the supplied vehicle data
             *
             * vehicleDataP - The selected vehicle data
             */
            void handleVehicleSelected(
                std::shared_ptr<const models::VehicleData> vehicleDataP
            );

            /**
             * Updates the vehicle brand
             *
             * Called whenever the brand input field changes
             *
             * text - The new field contents
             */
            void handleChangeBrandField(
                const QString text
            );

            /**
             * Updates the vehicle model
             *
             * Called whenever the model input field changes
             *
             * text - The new field contents
             */
            void handleChangeModelField(
                const QString text
            );

            /**
             * Updates the vehicle rental price per day
             *
             * Called whenever the price per day input field changes
             *
             * text - The new field contents
             */
            void handleChangepPricePerDayField(
                const QString text
            );

            /**
             * Updates the vehicle rental status
             *
             * Called whenever the rental status selection changes
             *
             * index - The index of the selected item
             */
            void handleChangeIsRentedComboBox(
                int index
            );

            /**
             * Confirms the current vehicle data
             *
             * Emits the confirmVehicle() signal containing the current vehicle data
             */
            void handleConfirm();

        signals:


            /**
             * Emitted when the user confirms the vehicle data
             *
             * vehicleData The confirmed vehicle data
             */
            void confirmVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

    };

};
