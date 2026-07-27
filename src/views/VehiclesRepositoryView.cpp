
#include "views/views.h"
#include "models/VehicleRepository.h"

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

views::VehiclesRepositoryView::VehiclesRepositoryView(
    QWidget *parent,
    models::VehicleRepository* vehicleRepositoryP
):
    QWidget(parent),
    vehicleRepository(vehicleRepositoryP) {

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
        vehicleRepository,
        &models::VehicleRepository::vehiclesChanged,
        this,
        &VehiclesRepositoryView::handleVehiclesChanged
    );

    QObject::connect(
        vehicleRepository,
        &models::VehicleRepository::vehicleAdded,
        this,
        &VehiclesRepositoryView::handleVehicleAdded
    );

    QObject::connect(
        vehicleRepository,
        &models::VehicleRepository::vehicleRemoved,
        this,
        &VehiclesRepositoryView::handleVehicleRemoved
    );

    QObject::connect(
        vehicleRepository,
        &models::VehicleRepository::vehicleUpdated,
        this,
        &VehiclesRepositoryView::handleVehicleUpdated
    );

    QObject::connect(
        table,
        &QTableWidget::itemSelectionChanged,
        this,
        &VehiclesRepositoryView::handleSelectionChanged
    );

};

views::VehiclesRepositoryView::~VehiclesRepositoryView() {
    destroyTable();
};

void views::VehiclesRepositoryView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

void views::VehiclesRepositoryView::refreshTable() {

    destroyTable();

    const auto vehicles = vehicleRepository->getVehicles();

    table->setRowCount(vehicles.size());

    for (unsigned int row = 0; row < vehicles.size(); ++row) {
        const auto vehicle = vehicles.at(row);
        table->setItem(row, 0, new QTableWidgetItem(vehicle->getVehicleTypeIdAsQString()));
        table->setItem(row, 1, new QTableWidgetItem(vehicle->getVehicleIdAsQString()));
        table->setItem(row, 2, new QTableWidgetItem(vehicle->getBrand()));
        table->setItem(row, 3, new QTableWidgetItem(vehicle->getModel()));
        table->setItem(row, 4, new QTableWidgetItem(vehicle->getPricePerDayAsQString()));
        table->setItem(row, 5, new QTableWidgetItem(vehicle->getIsRentedAsQString()));
    };

    int width =
        table->verticalHeader()->width() +
        table->horizontalHeader()->length() +
        table->frameWidth() * 2 +
        34;

    table->setFixedWidth(width);

};

void views::VehiclesRepositoryView::handleVehiclesChanged() {
    qDebug() << "handleVehiclesChanged called";
};

void views::VehiclesRepositoryView::handleVehicleAdded(const long long vehicleId) {
    qDebug() << "handleVehicleAdded called with: " << vehicleId;
};

void views::VehiclesRepositoryView::handleVehicleRemoved(const long long vehicleId) {
    qDebug() << "VehiclesRepositoryView handleVehicleRemoved called with: " << vehicleId;
};

void views::VehiclesRepositoryView::handleVehicleUpdated(const long long vehicleId) {

    qDebug() << "VehiclesRepositoryView handleVehicleUpdated called with: " << vehicleId;

    models::Vehicle* vehicle = vehicleRepository->searchVehicleById(vehicleId);

    qDebug() << "VehiclesRepositoryView vehicle: " << vehicle->toQString();

    for (unsigned int row = 0; row < table->rowCount(); ++row) {

        QTableWidgetItem* idItem = table->item(row, 1);

        if (idItem == nullptr) {
            continue;
        };

        bool ok = false;
        const long long currentId = idItem->text().toLongLong(&ok);

        if (!ok || currentId != vehicleId) {
            continue;
        };

        table->item(row, 0)->setText(vehicle->getVehicleTypeIdAsQString());
        table->item(row, 1)->setText(vehicle->getVehicleIdAsQString());
        table->item(row, 2)->setText(vehicle->getBrand());
        table->item(row, 3)->setText(vehicle->getModel());
        table->item(row, 4)->setText(vehicle->getPricePerDayAsQString());
        table->item(row, 5)->setText(vehicle->getIsRentedAsQString());

        return;

    };

    qDebug() << "Vehicle row not found in table";

};

void views::VehiclesRepositoryView::handleUpdateVehicle(
    const models::VehicleData& data
) {
    vehicleRepository->addVehicle(data);
};

void views::VehiclesRepositoryView::handleSelectionChanged() {

    int row = table->currentRow();

    if (row < 0) {
        return;
    };

    auto item = table->item(row, 1);

    if (!item) {
        return;
    };

    const QString vehicleIdQString = item->text();

    bool ok = false;

    const long long vehicleIdLongLong = vehicleIdQString.toLongLong(&ok);

    if (!ok) {
        qDebug() << "Error: Failed to convert vehicle id QString to long long, no vehicle selected";
        return;
    };

    auto vehicle = vehicleRepository->searchVehicleById(vehicleIdLongLong);

    emit vehicleSelected(vehicle->getVehicleData());

};
