
#pragma once

#include "VehiclesFile/VehiclesFile.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>

class VehiclesFileView : public QWidget {

    private:

        VehiclesFile& vehiclesFile;
        QHBoxLayout *centralHBox;
        QWidget *content;
        QVBoxLayout *contentVBox;
        QTableWidget *table;

    public:

        explicit VehiclesFileView(
            VehiclesFile& vehiclesFileRef,
            QWidget* parent = nullptr
        );

        ~VehiclesFileView();

        void destroyTable();

        void refreshTable();

        void handleVehiclesChanged();

        void handleVehicleAdded(const QString vehicleId);

        void handleVehicleRemoved(const QString vehicleId);

        void handleVehicleUpdated(const QString vehicleId);

        void handleVehicleRented(const QString vehicleId);

        void handleVehicleReturned(const QString vehicleId);

};
