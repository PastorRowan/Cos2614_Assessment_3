
#pragma once

#include "VehiclePersistence/VehiclePersistence.h"
#include "models/models.h"

#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QTableWidget>

namespace views {

    class VehiclePersistenceView : public QWidget {

        Q_OBJECT

        private:

            VehiclePersistence* VehiclePersistence;
            QHBoxLayout *centralHBox;
            QWidget *content;
            QVBoxLayout *contentVBox;
            QTableWidget *table;

        public:

            explicit VehiclePersistenceView(
                QWidget *parent,
                VehiclePersistence* VehiclePersistenceP
            );

            ~VehiclePersistenceView();

            void destroyTable();

            void refreshTable();

        // slots:

            void handleVehiclesChanged();

            void handleVehicleAdded(const QString vehicleId);

            void handleVehicleRemoved(const QString vehicleId);

            void handleVehicleUpdated(const QString vehicleId);

            void handleSelectionChanged();

        signals:

            void vehicleSelected(models::Vehicle* vehicle);

    };

};
