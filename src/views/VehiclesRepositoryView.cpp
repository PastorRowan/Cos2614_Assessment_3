
#include "views/views.h"
#include "VehiclePersistence/VehiclePersistence.h"

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

views::VehiclesRepositoryView::VehiclesRepositoryView(
    QWidget* parent,
    VehiclePersistence* VehiclePersistenceP
):
    QWidget(parent),
    VehiclePersistence(VehiclePersistenceP) {

    // QObject::connect();
    centralHBox = new QHBoxLayout(this);
    contentVBox = new QVBoxLayout();
    table = new QTableWidget(this);

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

    QObject::connect(
        VehiclePersistence,
        &VehiclePersistence::vehiclesChanged,
        this,
        &VehiclePersistenceView::handleVehiclesChanged
    );

    QObject::connect(
        VehiclePersistence,
        &VehiclePersistence::vehicleAdded,
        this,
        &VehiclePersistenceView::handleVehicleAdded
    );

    QObject::connect(
        VehiclePersistence,
        &VehiclePersistence::vehicleRemoved,
        this,
        &VehiclePersistenceView::handleVehicleRemoved
    );

    QObject::connect(
        VehiclePersistence,
        &VehiclePersistence::vehicleUpdated,
        this,
        &VehiclePersistenceView::handleVehicleUpdated
    );

    QObject::connect(
        table,
        &QTableWidget::itemSelectionChanged,
        this,
        &VehiclePersistenceView::handleSelectionChanged
    );

};

views::VehiclePersistenceView::~VehiclePersistenceView() {
    destroyTable();
};

void views::VehiclePersistenceView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

void views::VehiclePersistenceView::refreshTable() {

    destroyTable();

    const auto vehicles = VehiclePersistence->getvehicles();

    table->setRowCount(vehicles.size());

    for (unsigned int row = 0; row < vehicles.size(); ++row) {
        const auto vehicle = vehicles.at(row);
        table->setItem(row, 0, new QTableWidgetItem(vehicle->VehicleTypeIdToQString()));
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

void views::VehiclePersistenceView::handleVehiclesChanged() {
    qDebug() << "handleVehiclesChanged called";
};

void views::VehiclePersistenceView::handleVehicleAdded(const QString vehicleId) {
    qDebug() << "handleVehicleAdded called with: " << vehicleId;
};

void views::VehiclePersistenceView::handleVehicleRemoved(const QString vehicleId) {
    qDebug() << "handleVehicleRemoved called with: " << vehicleId;
};

void views::VehiclePersistenceView::handleVehicleUpdated(const QString vehicleId) {
    qDebug() << "handleVehicleUpdated called with: " << vehicleId;
};

void views::VehiclePersistenceView::handleSelectionChanged() {

    int row = table->currentRow();

    if (row < 0) {
        return;
    };

    auto item = table->item(row, 1);

    if (!item)
        return;

    QString vehicleId = item->text();

    auto vehicle = VehiclePersistence->searchVehicleById(vehicleId);

    emit vehicleSelected(vehicle);

};
