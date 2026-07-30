
#include "views/VehiclesRepositoryView.h"
#include "models/VehicleRepository.h"

#include <QObject>
#include <QWidget>
#include <memory>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

/**
 * Constructs a VehiclesRepositoryView widget
 *
 * Initializes the table used to display the vehicle repository, configures
 * its layout and columns, populates it with the current repository contents,
 * and connects repository and table signals to their corresponding slots
 *
 * parent - The parent widget
 * vehicleRepositoryP - The vehicle repository displayed by this view
 */
views::VehiclesRepositoryView::VehiclesRepositoryView(
    QWidget *parent,
    models::VehicleRepository* vehicleRepositoryP
):
    QWidget(parent),
    vehicleRepository(vehicleRepositoryP) {

    centralHBox = new QHBoxLayout(this);
    contentVBox = new QVBoxLayout();
    table = new QTableWidget(this);

    centralHBox->addStretch();
    centralHBox->addLayout(contentVBox);
    centralHBox->addStretch();

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setFixedHeight(300);
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

/**
 * Searches the table for a vehicle by its identifier
 *
 * Performs a linear search through the table rows and returns the row index
 * corresponding to the specified vehicle ID
 *
 * vehicleId The unique identifier of the vehicle
 * Returns the matching row index, or -1 if no matching row exists
 */
int views::VehiclesRepositoryView::searchRowById(
    const long long vehicleId
) {

    for (int row = 0; row < table->rowCount(); ++row) {

        QTableWidgetItem* idItem = table->item(row, 1);

        if (idItem == nullptr) {
            continue;
        };

        bool ok = false;
        const long long currentId = idItem->text().toLongLong(&ok);

        if (ok && currentId == vehicleId) {
            return row;
        };

    };

    return -1;

};

/**
 * Removes all rows from the table
 *
 * Clears all table items and resets the row count to zero
 */
void views::VehiclesRepositoryView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

/**
 * Rebuilds the table from the vehicle repository
 *
 * Clears the current table contents and repopulates the table using the
 * vehicles stored in the associated repository
 */
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

/**
 * Handles repository change notifications
 *
 * This slot is invoked whenever the repository emits the
 * vehiclesChanged() signal
 */
void views::VehiclesRepositoryView::handleVehiclesChanged() {
    qDebug() << "handleVehiclesChanged called";
};

/**
 * Handles notifications that a vehicle has been added
 *
 * Retrieves the newly added vehicle from the repository and appends it to
 * the table
 *
 * vehicleId - The unique identifier of the newly added vehicle
 */
void views::VehiclesRepositoryView::handleVehicleAdded(
    const long long vehicleId
) {
    qDebug() << "VehiclesRepositoryView handleVehicleAdded called with: " << vehicleId;

    models::Vehicle* vehicle = vehicleRepository->searchVehicleById(vehicleId);

    if (vehicle == nullptr) {
        qDebug() << "Failed to find vehicle in vehicle repository with vehicle id: " << vehicleId;
        return;
    };

    const int rowIndex = table->rowCount();

    table->insertRow(rowIndex);

    table->setItem(rowIndex, 0, new QTableWidgetItem(vehicle->getVehicleTypeIdAsQString()));
    table->setItem(rowIndex, 1, new QTableWidgetItem(vehicle->getVehicleIdAsQString()));
    table->setItem(rowIndex, 2, new QTableWidgetItem(vehicle->getBrand()));
    table->setItem(rowIndex, 3, new QTableWidgetItem(vehicle->getModel()));
    table->setItem(rowIndex, 4, new QTableWidgetItem(vehicle->getPricePerDayAsQString()));
    table->setItem(rowIndex, 5, new QTableWidgetItem(vehicle->getIsRentedAsQString()));

};

/**
 * Handles notifications that a vehicle has been removed
 *
 * This slot is invoked whenever the repository emits the
 * vehicleRemoved() signal
 *
 * vehicleId - The unique identifier of the removed vehicle
 */
void views::VehiclesRepositoryView::handleVehicleRemoved(
    const long long vehicleId
) {
    qDebug() << "VehiclesRepositoryView handleVehicleRemoved called with: " << vehicleId;
};

/**
 * Handles notifications that a vehicle has been updated
 *
 * Retrieves the updated vehicle from the repository and refreshes the
 * corresponding row in the table
 *
 * vehicleId - The unique identifier of the updated vehicle
 */
void views::VehiclesRepositoryView::handleVehicleUpdated(
    const long long vehicleId
) {

    qDebug() << "VehiclesRepositoryView handleVehicleUpdated called with: " << vehicleId;

    models::Vehicle* vehicle = vehicleRepository->searchVehicleById(vehicleId);

    if (vehicle == nullptr) {
        qDebug() << "Failed to find vehicle in vehicle repository with vehicle id: " << vehicleId;
        return;
    };

    int rowIndex = searchRowById(vehicleId);

    if (rowIndex <= -1) {
        qDebug() << "Failed to find vehicle in table with vehicle id: " << vehicleId;
        return;
    };

    table->item(rowIndex, 0)->setText(vehicle->getVehicleTypeIdAsQString());
    table->item(rowIndex, 1)->setText(vehicle->getVehicleIdAsQString());
    table->item(rowIndex, 2)->setText(vehicle->getBrand());
    table->item(rowIndex, 3)->setText(vehicle->getModel());
    table->item(rowIndex, 4)->setText(vehicle->getPricePerDayAsQString());
    table->item(rowIndex, 5)->setText(vehicle->getIsRentedAsQString());

};

/**
 * Handles requests to add or update a vehicle
 *
 * Forwards the supplied vehicle data to the associated repository
 *
 * vehicleData - The vehicle data to process
 */
void views::VehiclesRepositoryView::handleUpdateVehicle(
    std::shared_ptr<const models::VehicleData> vehicleData
) {
    vehicleRepository->addVehicle(*vehicleData);
};

/**
 * Handles changes to the selected table row
 *
 * Determines the selected vehicle, creates an immutable snapshot of its
 * current data, and emits the vehicleSelected() signal
 */
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

    auto vehicleDataSnapshot =
        std::shared_ptr<const models::VehicleData>(
            vehicle->getVehicleData().clone()
        );

    emit vehicleSelected(vehicleDataSnapshot);

};
