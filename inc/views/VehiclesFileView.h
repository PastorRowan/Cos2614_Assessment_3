
#pragma once

#include "VehiclesFile/VehiclesFile.h"

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QTableWidget>

namespace views {

    class VehiclesFileView : public QWidget {

        Q_OBJECT

        private:

            VehiclesFile& vehiclesFile;
            QHBoxLayout *centralHBox;
            QWidget *content;
            QVBoxLayout *contentVBox;
            QTableWidget *table;

        public:

            explicit VehiclesFileView(
                QWidget *parent = nullptr,
                VehiclesFile& vehiclesFileRef
            );

            ~VehiclesFileView();

            void destroyTable();

            void refreshTable();

        // slots:

            void handleVehiclesChanged();

            void handleVehicleAdded(const QString vehicleId);

            void handleVehicleRemoved(const QString vehicleId);

            void handleVehicleUpdated(const QString vehicleId);

            void handleSelectionChanged();

        signals:

            void vehicleSelected(const QString vehicleId);

    };

};
