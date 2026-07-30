
#pragma once

#include "models/Car.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QFormLayout;
class QLineEdit;

namespace views {

    /**
     * CarDataView
     * A widget for viewing and editing car-specific vehicle data
     *
     * Displays editable fields for properties unique to cars, such as the
     * number of doors and seats
     * The view can be bound to a models::CarData instance and automatically updates the underlying
     * data whenever the user modifies the input fields
     */
    class CarDataView : public QWidget {

        Q_OBJECT

        private:

            // The currently displayed car data
            std::shared_ptr<models::CarData> carData;

            // Form layout containing the input fields
            QFormLayout *carFormLayout;

            // Input field for the number of doors
            QLineEdit *numberOfDoorsField;

            // Input field for the number of seats
            QLineEdit *numberOfSeatsField;

            // Updates all input fields to reflect the current car data
            void refreshFields();

        public:

            /**
             * Constructs a CarDataView widget
             *
             * Creates the user interface and initializes the input fields
             *
             * parent - The parent widget, defaults to nullptr
             */
            explicit CarDataView(
                QWidget *parent = nullptr
            );

            /**
             * Assigns the car data displayed by the view
             *
             * The view immediately refreshes its fields to display the values
             * contained in the supplied CarData object
             *
             * carDataP - Shared pointer to the car data to display
             */
            void setCarData(
                std::shared_ptr<models::CarData> carDataP
            );

            /**
             * Determines whether the view currently has car data
             *
             * Returns true if a CarData object has been assigned, otherwise false
             */
            bool hasCarData() const;

        // slots:

            /**
             * Updates the number of doors in the current car data
             *
             * Called whenever the number of doors input field changes
             *
             * text - The new field contents
             */
            void handleChangeNumberOfDoorsField(
                const QString text
            );

            /**
             * Updates the number of seats in the current car data
             *
             * Called whenever the number of seats input field changes
             *
             * text - The new field contents
             */
            void handleChangeNumberOfSeatsField(
                const QString text
            );

    };

};
