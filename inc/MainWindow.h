
#pragma once

#include "models/VehicleRepository.h"
#include "models/Vehicle.h"
#include "views/views.h"
#include "dialogues/dialogues.h"

#include <QMainWindow>
class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QPushButton;
#include <memory>

/**
 * The main application window for the Vehicle Rental Management System
 *
 * The MainWindow coordinates the application's primary user interface,
 * providing access to the vehicle repository and vehicle editing views
 * It owns the main layouts, creates and manages the vehicle repository,
 * displays the list of vehicles, allows users to edit vehicle details,
 * and provides access to the dialog used to add new vehicles
 */
class MainWindow : public QMainWindow {

    private:

        // Repository containing all vehicle records
        models::VehicleRepository* vehicleRepository;

        // Dialog used to add new vehicles to the repository
        dialogues::AddVehicleDialogue *addVehicleDialogue;

        // Dialog used to delete vehicles in the repository
        dialogues::DeleteVehicleDialogue *deleteVehicleDialogue;

        // The central widget of the main window
        QWidget* central;

        // Container widget holding the main application content
        QWidget* content;

        // The main horizontal layout of the window
        QHBoxLayout* centralHLayout;

        // The main vertical layout for the content widget
        QVBoxLayout* contentVLayout;

        // Label displaying the application title
        QLabel* title;

        // View displaying the repository of vehicles
        views::VehiclesRepositoryView* vehiclesRepositoryView;

        QWidget* buttonBarWidget;

        QHBoxLayout* buttonBarHBox;

        // Button used to open the Add Vehicle dialog
        QPushButton* addVehicleButton;

        // Button used to delete the selected Vehicle
        QPushButton* deleteVehicleButton;

        // View displaying and editing the selected vehicle
        views::VehicleDataView* vehicleDataView;

    public:

        /**
         * Constructs the application's main window
         *
         * Initializes the user interface, creates the vehicle repository,
         * sets up the repository and vehicle data views, creates the
         * Add Vehicle dialog, and connects the required signals and slots
         *
         * parent The parent widget, defaults to nullptr
         */
        explicit MainWindow(QWidget *parent = nullptr);

        // Destroys the MainWindow
        ~MainWindow() = default;

    // public slots:

        void handleVehicleSelected(
            std::shared_ptr<const models::VehicleData> vehicleData
        );

};
