
#include "VehiclesFile/VehiclesFileView.h"

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>

VehiclesFileView::VehiclesFileView(
    VehiclesFile& vehiclesFileRef,
    QWidget* parent
): QWidget(parent), vehiclesFile(vehiclesFileRef) {

    // QObject::connect();
    centralHBox = new QHBoxLayout(this);
    contentVBox = new QVBoxLayout();
    table = new QTableWidget();

    centralHBox->addStretch();
    centralHBox->addLayout(contentVBox);
    centralHBox->addStretch();

    table->setFixedHeight(430);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({
        "TYPE_ID",
        "VEHICLE_ID",
        "BRAND",
        "MODEL",
        "PRICE_PER_DAY",
        "IS_RENTED"
    });

    table->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    table->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    table->horizontalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents
    );
    table->verticalHeader()->setSectionResizeMode(
        QHeaderView::ResizeToContents
    );

    refreshTable();

    contentVBox->addWidget(table, 1);

    setLayout(centralHBox);

};

VehiclesFileView::~VehiclesFileView() {
    destroyTable();
};

void VehiclesFileView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

void VehiclesFileView::refreshTable() {

    destroyTable();

    const auto vehicles = vehiclesFile.getVehiclesQVector();

    table->setRowCount(vehicles.size());

    for (unsigned int row = 0; row < vehicles.size(); ++row) {
        const auto vehicle = vehicles.at(row);
        table->setItem(row, 0, new QTableWidgetItem(vehicle->typeIdToQString()));
        table->setItem(row, 1, new QTableWidgetItem(vehicle->getVehicleId()));
        table->setItem(row, 2, new QTableWidgetItem(vehicle->getBrand()));
        table->setItem(row, 3, new QTableWidgetItem(vehicle->getModel()));
        table->setItem(row, 4, new QTableWidgetItem(vehicle->pricePerDayToQString()));
        table->setItem(row, 5, new QTableWidgetItem(vehicle->isRentedToQString()));
    };

    int width =
        table->verticalHeader()->width() +
        table->horizontalHeader()->length() +
        table->frameWidth() * 2 +
        34;

    table->setFixedWidth(width);

};
