
#include "views/views.h"
#include "VehiclesFile/VehiclesFile.h"

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QDebug>

views::VehiclesFileView::VehiclesFileView(
    QWidget* parent,
    VehiclesFile& vehiclesFileRef
):
    QWidget(parent),
    vehiclesFile(vehiclesFileRef) {

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

    QObject::connect(
        &vehiclesFile,
        &VehiclesFile::vehiclesChanged,
        this,
        &VehiclesFileView::handleVehiclesChanged
    );

    QObject::connect(
        &vehiclesFile,
        &VehiclesFile::vehicleAdded,
        this,
        &VehiclesFileView::handleVehicleAdded
    );

    QObject::connect(
        &vehiclesFile,
        &VehiclesFile::vehicleRemoved,
        this,
        &VehiclesFileView::handleVehicleRemoved
    );

    QObject::connect(
        &vehiclesFile,
        &VehiclesFile::vehicleUpdated,
        this,
        &VehiclesFileView::handleVehicleUpdated
    );

    QObject::connect(
        table,
        &QTableWidget::itemSelectionChanged,
        this,
        &VehiclesFileView::handleSelectionChanged
    );

};

views::VehiclesFileView::~VehiclesFileView() {
    destroyTable();
};

void views::VehiclesFileView::destroyTable() {
    table->clearContents();
    table->setRowCount(0);
};

void views::VehiclesFileView::refreshTable() {

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

void views::VehiclesFileView::handleVehiclesChanged() {
    qDebug() << "handleVehiclesChanged called";
};

void views::VehiclesFileView::handleVehicleAdded(const QString vehicleId) {
    qDebug() << "handleVehicleAdded called with: " << vehicleId;
};

void views::VehiclesFileView::handleVehicleRemoved(const QString vehicleId) {
    qDebug() << "handleVehicleRemoved called with: " << vehicleId;
};

void views::VehiclesFileView::handleVehicleUpdated(const QString vehicleId) {
    qDebug() << "handleVehicleUpdated called with: " << vehicleId;
};

void views::VehiclesFileView::handleSelectionChanged() {

    int row = table->currentRow();

    if (row < 0) {
        return;
    };

    QString vehicleId = table->item(row, 1)->text();

    emit vehicleSelected(vehicleId);

};
