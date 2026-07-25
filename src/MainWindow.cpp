
#include "Config.h"

#include "MainWindow.h"
#include "VehiclePersistence/VehiclePersistence.h"
#include "VehiclePersistence/populateVehiclePersistence.h"
#include "views/views.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) {

    VehiclePersistence* VehiclePersistence = new VehiclePersistence(
        QString("/files/vehicles.txt"),
        QString("/files/currentVehicleId.txt"),
        this
    );

    #if POPULATE_VEHICLES_FILE
        populateVehiclePersistence(VehiclePersistence);
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

    views::VehiclePersistenceView *VehiclePersistenceView = new views::VehiclePersistenceView(content, VehiclePersistence);

    views::VehicleView *vehicleView = new views::VehicleView(content, nullptr);

    QObject::connect(
        VehiclePersistenceView,
        &views::VehiclePersistenceView::vehicleSelected,
        vehicleView,
        &views::VehicleView::handleVehicleSelected
    );

    QObject::connect(
        vehicleView,
        &views::VehicleView::vehicleUpdated,
        VehiclePersistenceView,
        &views::VehiclePersistenceView::handleVehicleUpdated
    );

    QVBoxLayout *contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(VehiclePersistenceView);
    contentVLayout->addWidget(vehicleView);
    contentVLayout->addStretch();

    setCentralWidget(central);

};

MainWindow::~MainWindow() {};
