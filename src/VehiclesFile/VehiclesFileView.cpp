
#include "VehiclesFile/VehiclesFileView.h"

#include <QObject>
#include <QWidget>
#include <QTableWidget>

VehiclesFileView::VehiclesFileView(
    VehiclesFile& vehiclesFileRef,
    QWidget* parent = nullptr
): QWidget(parent), vehiclesFile(vehiclesFileRef) {
    // QObject::connect();
    table = new QTableWidget(this);
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({
        "TYPE_ID",
        "VEHICLE_ID",
        "BRAND",
        "MODEL",
        "PRICE_PER_DAY",
        "IS_RENTED"
    });
    refresh();
};

VehiclesFileView::~VehiclesFileView() {
    destroyTable();
};

void VehiclesFileView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

void VehiclesFileView::refresh() {

    destroyTable();

    const auto vehicles = vehiclesFile.getVehiclesQVector();

    table->setRowCount(vehicles.size());

    for (unsigned int row = 0; row < vehicles.size(); ++row) {
        const auto vehicle = vehicles.at(row);
        table->setItem(row, 0, new QTableWidgetItem(vehicle->typeIdToQString()));
        table->setItem(row, 1, new QTableWidgetItem(vehicle->getVehicleId()));
        table->setItem(row, 2, new QTableWidgetItem(vehicle->getModel()));
        table->setItem(row, 3, new QTableWidgetItem(vehicle->pricePerDayToQString()));
        table->setItem(row, 4, new QTableWidgetItem(vehicle->isRentedToQString()));
    };

};
