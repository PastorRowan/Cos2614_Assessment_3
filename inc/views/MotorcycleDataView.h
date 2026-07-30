
#pragma once

#include "models/Motorcycle.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QFormLayout;
class QLineEdit;

namespace views {

    /**
     * A widget for viewing and editing motorcycle-specific vehicle data
     *
     * Displays editable fields for properties unique to motorcycles, such as
     * engine capacity. The view can be bound to a models::MotorcycleData
     * instance and automatically updates the underlying data whenever the user
     * modifies the input field
     */
    class MotorcycleDataView : public QWidget {

        Q_OBJECT

        private:

            // The currently displayed motorcycle data
            std::shared_ptr<models::MotorcycleData> motorcycleData;

            // Form layout containing the input fields
            QFormLayout *motorcycleFormLayout;

            // Input field for the engine capacity in cubic centimetres
            QLineEdit *engineCapacityCCField;

            /**
             * Updates all input fields to reflect the current motorcycle data
             *
             * If no motorcycle data is assigned, the field is cleared or reset to its default state
             */
            void refreshFields();

        public:

            /**
             * Constructs a MotorcycleDataView widget
             *
             * Creates the user interface and initializes the input field
             *
             * parent The parent widget. Defaults to nullptr
             */
            explicit MotorcycleDataView(
                QWidget *parent = nullptr
            );

            /**
             * Assigns the motorcycle data displayed by the view
             *
             * The view immediately refreshes its field to display the values
             * contained in the supplied MotorcycleData object
             *
             * motorcycleDataP - Shared pointer to the motorcycle data to display
             */
            void setMotorcycleData(
                std::shared_ptr<models::MotorcycleData> motorcycleDataP
            );

            /**
             * Determines whether the view currently has motorcycle data
             *
             * Returns true if a MotorcycleData object has been assigned, otherwise false
             */
            bool hasMotorcycleData() const;

        // slots:

            /**
             * Updates the engine capacity in the current motorcycle data
             *
             * Called whenever the engine capacity input field changes
             *
             * text - The new field contents
             */
            void handleChangeEngineCapacityCCField(
                const QString text
            );

    };

};
