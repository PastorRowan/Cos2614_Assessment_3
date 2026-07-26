
#pragma once

#include "models/VehicleRepository.h"

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QTableWidget>

namespace views {

    class VehiclesRepositoryView : public QWidget {

        Q_OBJECT

        private:

            models::VehicleRepository* vehicleRepository;
            QHBoxLayout *centralHBox;
            QWidget *content;
            QVBoxLayout *contentVBox;
            QTableWidget *table;

        public:

            explicit VehiclesRepositoryView(
                QWidget *parent,
                models::VehicleRepository* vehicleRepositoryP
            );

            ~VehiclesRepositoryView();

            void destroyTable();

            void refreshTable();

        // slots:

            void handleVehiclesChanged();

            void handleVehicleAdded(const long long vehicleId);

            void handleVehicleRemoved(const long long vehicleId);

            void handleVehicleUpdated(const long long vehicleId);

            void handleSelectionChanged();

        signals:

            void vehicleSelected(models::Vehicle* vehicle);

    };

};
