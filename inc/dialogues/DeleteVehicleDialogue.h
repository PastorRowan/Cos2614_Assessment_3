
#pragma once

#include "models/Vehicle.h"

#include <QDialog>
#include <QObject>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

namespace dialogues {

    /**
     * Dialog used to confirm the deletion of a vehicle
     *
     * Displays information about the selected vehicle and asks the user
     * to confirm whether it should be permanently removed from the
     * repository.
     *
     * The dialog does not perform the deletion itself. If the user
     * confirms the action, the dialog emits the deleteVehicle signal
     * containing the selected vehicle's ID.
     */
    class DeleteVehicleDialogue : public QDialog {

        Q_OBJECT

    private:

        std::shared_ptr<const models::VehicleData> vehicleData = nullptr;

        QVBoxLayout *vBoxLayout;
        QLabel *title;
        QLabel *vehicleDetailsLabel;
        QLabel *warningLabel;
        QWidget *bottomButtonBarWidget;
        QHBoxLayout *bottomButtonBarLayout;
        QPushButton *noButton;
        QPushButton *yesButton;

    // private slots:

        void handleDismiss();

        /**
         * Handles confirmation of the deletion
         */
        void handleDelete();

    public:

        /**
         * Constructs a DeleteVehicleDialogue.
         *
         * parent - The parent widget.
         */
        explicit DeleteVehicleDialogue(QWidget* parent = nullptr);

        /**
         * Sets the vehicle that is about to be deleted.
         *
         * Updates the dialog's message to display the vehicle's details.
         *
         * vehicle The vehicle selected for deletion.
         */
        void setVehicleData(
            std::shared_ptr<const models::VehicleData> vehicleDataP
        );

        bool hasVehicle() const;

        void open();

    signals:

        /**
         * Emitted when the user confirms the deletion
         *
         * vehicleId - The ID of the vehicle to delete
         */
        void deleteVehicle(
            const long long vehicleId
        );

    };

}
