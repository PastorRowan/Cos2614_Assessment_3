
#include "views/VehicleDataView.h"
#include "models/Vehicle.h"
#include "views/CarDataView.h"
#include "views/MotorcycleDataView.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>

views::VehicleDataView::VehicleDataView(
    QWidget *parent
):
    QWidget(parent),
    optionalVehicleData({}) {

    vBoxLayout = new QVBoxLayout(this);

    vehicleFormWidget = new QWidget(this);
    vehicleFormLayout = new QFormLayout(vehicleFormWidget);

    vehicleTypeIdLabel = new QLabel(this);
    vehicleIdLabel = new QLabel(this);
    brandField = new QLineEdit(this);
    modelField = new QLineEdit(this);
    pricePerDayField = new QLineEdit(this);
    isRentedLabel = new QLabel(this);

    carDataView = new views::CarDataView(this);
    carDataView->hide();
    motorcycleDataView = new views::MotorcycleDataView(this);
    motorcycleDataView->hide();

    saveChangesButton = new QPushButton(this);
    saveChangesButton->setText("Save Changes");

    vehicleFormWidget->setLayout(vehicleFormLayout);
    vehicleFormLayout->addRow("TYPE_ID: ", vehicleTypeIdLabel);
    vehicleFormLayout->addRow("VEHICLE_ID: ", vehicleIdLabel);
    vehicleFormLayout->addRow("BRAND: ", brandField);
    vehicleFormLayout->addRow("MODEL: ", modelField);
    vehicleFormLayout->addRow("PRICE_PER_DAY: ", pricePerDayField);
    vehicleFormLayout->addRow("IS_RENTED: ", isRentedLabel);

    vBoxLayout->addWidget(vehicleFormWidget);
    vBoxLayout->addWidget(carDataView);
    vBoxLayout->addWidget(motorcycleDataView);
    vBoxLayout->addWidget(saveChangesButton);

    QObject::connect(
        brandField,
        &QLineEdit::textChanged,
        this,
        &views::VehicleDataView::handleChangeBrandField
    );

    QObject::connect(
        modelField,
        &QLineEdit::textChanged,
        this,
        &views::VehicleDataView::handleChangeModelField
    );

    QObject::connect(
        pricePerDayField,
        &QLineEdit::textChanged,
        this,
        &views::VehicleDataView::handleChangepPricePerDayField
    );

    QObject::connect(
        saveChangesButton,
        &QPushButton::clicked,
        this,
        &views::VehicleDataView::handleSaveChanges
    );

};

void views::VehicleDataView::setVehicleData(
    const models::VehicleData& vehicleData
) {

    optionalVehicleData = vehicleData;

    switch (vehicleData.vehicleTypeId) {

        case models::VehicleTypeId::car: {
            const auto& carData = static_cast<const models::CarData&>(vehicleData);
            carDataView->setCarData(carData);
            carDataView->show();

            motorcycleDataView->hide();
            motorcycleDataView->setMotorcycleData({});
            break;
        };

        case models::VehicleTypeId::motorCycle: {
            const auto& motorcycleData = static_cast<const models::MotorcycleData&>(vehicleData);

            motorcycleDataView->setMotorcycleData(motorcycleData);
            motorcycleDataView->show();

            carDataView->hide();
            carDataView->setCarData({});
            break;
        };

        default: {
            optionalVehicleData.reset();
            carDataView->hide();
            carDataView->setCarData({});
            motorcycleDataView->hide();
            motorcycleDataView->setMotorcycleData({});
            break;
        };

    };

    refreshFields();

};

void views::VehicleDataView::refreshFields() {

    bool hasVehicle = optionalVehicleData.has_value();

    vehicleFormWidget->setEnabled(hasVehicle);

    if (!hasVehicle) {
        vehicleTypeIdLabel->setText("");
        vehicleIdLabel->setText("");
        brandField->clear();
        modelField->clear();
        pricePerDayField->clear();
        isRentedLabel->setText("");
    } else {
        // I am sorry
        const models::VehicleData& vehicleData = optionalVehicleData.value();
        vehicleTypeIdLabel->setText(QString::number(static_cast<int>(vehicleData.vehicleTypeId)));
        vehicleIdLabel->setText(QString::number(vehicleData.vehicleId));
        brandField->setText(vehicleData.brand);
        modelField->setText(vehicleData.model);
        pricePerDayField->setText(QString::number(vehicleData.pricePerDay));
        isRentedLabel->setText(vehicleData.isRented ? "Yes" : "No");
    };

};

void views::VehicleDataView::handleVehicleSelected(
    const models::VehicleData& vehicleData
) {
    qDebug() << "handleVehicleSelected is running with vehicle id: " << vehicleData.vehicleId;
    setVehicleData(vehicleData);
};

void views::VehicleDataView::handleChangeBrandField(
    const QString& text
) {
    if (!optionalVehicleData.has_value()) {
        return;
    };
    optionalVehicleData->brand = text;
};

void views::VehicleDataView::handleChangeModelField(
    const QString& text
) {
    if (!optionalVehicleData.has_value()) {
        return;
    };
    optionalVehicleData->model = text;
};

void views::VehicleDataView::handleChangepPricePerDayField(
    const QString& text
) {
    if (!optionalVehicleData.has_value()) {
        return;
    };
    bool ok = false;
    const double value = text.toDouble(&ok);
    if (!ok) {
        return;
    };
    optionalVehicleData->pricePerDay = value;
}; 

void views::VehicleDataView::handleSaveChanges() {

    qDebug() << "handleSaveChanges is running";

    if (!optionalVehicleData.has_value()) {
        return;
    };

    switch (optionalVehicleData->vehicleTypeId) {

        case models::VehicleTypeId::car: {

            auto carData = carDataView->getVehicleData();

            if (!carData.has_value()) {
                return;
            };

            carData->vehicleId = optionalVehicleData->vehicleId;
            carData->vehicleTypeId = optionalVehicleData->vehicleTypeId;
            carData->brand = optionalVehicleData->brand;
            carData->model = optionalVehicleData->model;
            carData->pricePerDay = optionalVehicleData->pricePerDay;
            carData->isRented = optionalVehicleData->isRented;

            models::Car debugCar(nullptr, *carData);

            qDebug() << debugCar.toQString();

            emit updateVehicle(*carData);

            break;

        };

        case models::VehicleTypeId::motorCycle: {

            auto motorcycleData = motorcycleDataView->getVehicleData();

            if (!motorcycleData.has_value()) {
                return;
            };

            motorcycleData->vehicleId = optionalVehicleData->vehicleId;
            motorcycleData->vehicleTypeId = optionalVehicleData->vehicleTypeId;
            motorcycleData->brand = optionalVehicleData->brand;
            motorcycleData->model = optionalVehicleData->model;
            motorcycleData->pricePerDay = optionalVehicleData->pricePerDay;
            motorcycleData->isRented = optionalVehicleData->isRented;

            models::Motorcycle debugMotorcycle(nullptr, *motorcycleData);

            qDebug() << debugMotorcycle.toQString();

            emit updateVehicle(*motorcycleData);

            break;

        };

        default:
            break;
    };

};
