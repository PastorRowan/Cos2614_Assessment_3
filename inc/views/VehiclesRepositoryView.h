
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

    class VehiclesRepositoryView : public QWidget {

        Q_OBJECT

        private:

            models::VehicleRepository* vehicleRepository;
            QHBoxLayout *centralHBox;
            QWidget *content;
            QVBoxLayout *contentVBox;
            QTableWidget *table;

            int searchRowById(
                const long long vehicleId
            );

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

            void handleUpdateVehicle(
                const std::shared_ptr<const models::VehicleData> vehicleData
            );

            void handleSelectionChanged();

        signals:

            void vehicleSelected(
                const std::shared_ptr<const models::VehicleData> vehicleData
            );

    };

};
