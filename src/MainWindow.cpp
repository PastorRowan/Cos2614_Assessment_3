
#include "Config.h"

#include "MainWindow.h"
#include "models/VehicleRepository.h"
#include "helpers/populateVehicleRepository.h"
#include "views/views.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) {

    QWidget *central = new QWidget(this);
    central->setContentsMargins(10, 10, 10, 10);

    QWidget *content = new QWidget(central);
    content->setMaximumWidth(800);

    QHBoxLayout *centralHLayout = new QHBoxLayout(central);
    centralHLayout->addStretch();
    centralHLayout->addWidget(content);
    centralHLayout->addStretch();

    QLabel *title = new QLabel(content);
    title->setText("Vehicle Rental System");
    title->setAlignment(Qt::AlignCenter);

    models::VehicleRepository* vehicleRepository = new models::VehicleRepository(this);

    #if POPULATE_VEHICLES_FILE
        helpers::populateVehicleRepository(vehicleRepository);
    #endif

    views::VehiclesRepositoryView *vehiclesRepositoryView = new views::VehiclesRepositoryView(content, vehicleRepository);

    views::VehicleDataView *vehicleDataView = new views::VehicleDataView(content);

    QObject::connect(
        vehiclesRepositoryView,
        &views::VehiclesRepositoryView::vehicleSelected,
        vehicleDataView,
        &views::VehicleDataView::handleVehicleSelected
    );

    QObject::connect(
        vehicleDataView,
        &views::VehicleDataView::updateVehicle,
        vehicleRepository,
        &models::VehicleRepository::handleUpdateVehicle
    );

    QVBoxLayout *contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesRepositoryView);
    contentVLayout->addWidget(vehicleDataView);
    contentVLayout->addStretch();

    setCentralWidget(central);

};
