
#include "MainWindow.h"
#include "VehiclesFile/VehiclesFile.h"
#include "VehiclesFile/populateVehiclesFile.h"
#include "views/views.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) {

    VehiclesFile vehiclesFile = VehiclesFile(
        QString("/files/vehiclesQVector.txt"),
        QString("/files/currentVehicleId.txt"),
        this
    );

    #if POPULATE_VEHICLES_FILE
        populateVehiclesFile(vehiclesFile);
    #endif

    QWidget *central = new QWidget(this);
    central->setContentsMargins(10, 10, 10, 10);

    QWidget *content = new QWidget(central);
    content->setMinimumWidth(800);

    QHBoxLayout *centralHLayout = new QHBoxLayout(central);
    centralHLayout->addStretch();
    centralHLayout->addWidget(content);
    centralHLayout->addStretch();

    views::VehiclesFileView *vehiclesFileView = new views::VehiclesFileView(content, vehiclesFile);
    QLabel *title = new QLabel(content);
    title->setText("Vehicle Rental System");
    title->setAlignment(Qt::AlignCenter);

    views::VehicleView *vehicleView = new views::VehicleView(content, nullptr);

    QObject::connect(
        vehicleView,
        &views::VehicleView::vehicleUpdated,
        vehiclesFileView,
        &views::VehiclesFileView::handleVehicleUpdated
    );

    QVBoxLayout *contentVLayout = new QVBoxLayout(content);
    contentVLayout->addWidget(title);
    contentVLayout->addWidget(vehiclesFileView);
    contentVLayout->addWidget(vehicleView);
    contentVLayout->addStretch();

    setCentralWidget(central);

};

MainWindow::~MainWindow() {};
