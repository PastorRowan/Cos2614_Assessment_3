
#pragma once

#include "models/VehicleRepository.h"
#include "models/Vehicle.h"

#include <QWidget>
#include <QObject>
#include <memory>
class QHBoxLayout;
class QVBoxLayout;
class QTableWidget;

namespace views {

    /**
     * A widget for displaying and managing a repository of vehicles
     *
     * Displays all vehicles in a table and keeps the table synchronized with
     * the associated VehicleRepository
     * The view responds to repository changes such as vehicles being added,
     * removed, or updated, and emits a signal whenever the user selects a vehicle
     */
    class VehiclesRepositoryView : public QWidget {

        Q_OBJECT

        private:

            // The vehicle repository displayed by the view
            models::VehicleRepository* vehicleRepository;

            // The main horizontal layout for the widget
            QHBoxLayout *centralHBox;

            // Container widget for the table
            QWidget *content;

            // The main vertical layout for the content widget
            QVBoxLayout *contentVBox;

            // Table displaying all vehicles in the repository
            QTableWidget *table;

            /**
             * Searches the table for the row containing a vehicle ID
             *
             * vehicleId - The identifier of the vehicle to locate
             * Returns the row index if the vehicle is found; otherwise -1
             */
            int searchRowById(
                const long long vehicleId
            );

        public:

            /**
             * Constructs a VehiclesRepositoryView widget
             *
             * Creates the user interface, populates the table from the supplied
             * repository, and connects the required signals and slots
             *
             * parent - The parent widget
             * vehicleRepositoryP - The repository displayed by the view
             */
            explicit VehiclesRepositoryView(
                QWidget *parent,
                models::VehicleRepository* vehicleRepositoryP
            );

            // Destroys the VehiclesRepositoryView
            ~VehiclesRepositoryView() = default;

            // Removes all rows and contents from the table
            void destroyTable();

            // Rebuilds the table using the current repository contents
            void refreshTable();

        // slots:

            /**
             * Refreshes the table after the repository changes
             *
             * Called when the repository reports that its contents have changed
             */
            void handleVehiclesChanged();

            /**
             * Adds a newly created vehicle to the table
             *
             * vehicleId The identifier of the added vehicle
             */
            void handleVehicleAdded(const long long vehicleId);

            /**
             * Removes a vehicle from the table
             *
             * vehicleId - The identifier of the removed vehicle
             */
            void handleVehicleRemoved(const long long vehicleId);

            /**
             * Updates the displayed information for a vehicle
             *
             * vehicleId - The identifier of the updated vehicle
             */
            void handleVehicleUpdated(const long long vehicleId);

            /**
             * Updates a vehicle in the repository
             *
             * Called when edited vehicle data has been confirmed
             *
             * vehicleData - The updated vehicle data
             */
            void handleUpdateVehicle(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

            /**
             * Handles changes to the current table selection
             *
             * Emits the vehicleSelected() signal with the selected vehicle,
             * or a null pointer if no valid selection exists
             */
            void handleSelectionChanged();

        signals:

            /**
             * Emitted when the user selects a vehicle in the table
             *
             * vehicleData The selected vehicle data
             */
            void vehicleSelected(
                std::shared_ptr<const models::VehicleData> vehicleData
            );

    };

};
