
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

    models::VehicleRepository* vehicleRepository = new models::VehicleRepository(this);

    #if POPULATE_VEHICLES_FILE
        helpers::populateVehicleRepository(vehicleRepository);
    #endif

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

    views::VehiclesRepositoryView *vehiclesRepositoryView = new views::VehiclesRepositoryView(content, vehicleRepository);

    views::VehicleView *vehicleView = new views::VehicleView(content);

    QObject::connect(
        vehiclesRepositoryView,
        &views::VehiclesRepositoryView::vehicleSelected,
        vehicleView,
        &views::VehicleView::handleVehicleSelected
    );

    QObject::connect(
        vehicleView,
        &views::VehicleView::vehicleUpdated,
        vehiclesRepositoryView,
        &views::VehiclesRepositoryView::handleVehicleUpdated
    );

    QVBoxLayout *contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesRepositoryView);
    contentVLayout->addWidget(vehicleView);
    contentVLayout->addStretch();

    setCentralWidget(central);

};
