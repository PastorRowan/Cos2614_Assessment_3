
#include "views/VehicleDataView.h"
#include "models/Vehicle.h"
#include "views/CarDataView.h"
#include "views/MotorcycleDataView.h"

#include <QVBoxLayout>
#include <QWidget>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>
#include <QDoubleValidator>
#include <limits>

views::VehicleDataView::VehicleDataView(
    QWidget *parent
):
    QWidget(parent),
    vehicleData(nullptr) {

    vBoxLayout = new QVBoxLayout(this);

    vehicleFormWidget = new QWidget(this);
    vehicleFormLayout = new QFormLayout(vehicleFormWidget);

    vehicleTypeIdLabel = new QLabel(this);

    vehicleIdLabel = new QLabel(this);

    brandField = new QLineEdit(this);

    modelField = new QLineEdit(this);

    pricePerDayField = new QLineEdit(this);
    pricePerDayField->setValidator(
        new QDoubleValidator(
            0,
            std::numeric_limits<double>::max(),
            2
        )
    );

    isRentedComboBox = new QComboBox(this);
    isRentedComboBox->addItem("No", false);
    isRentedComboBox->addItem("Yes", true);

    carDataView = new views::CarDataView(this);
    carDataView->hide();
    motorcycleDataView = new views::MotorcycleDataView(this);
    motorcycleDataView->hide();

    confirmButton = new QPushButton(this);
    confirmButton->setText("confirm");

    vehicleFormWidget->setLayout(vehicleFormLayout);
    vehicleFormLayout->addRow("TYPE_ID: ", vehicleTypeIdLabel);
    vehicleFormLayout->addRow("VEHICLE_ID: ", vehicleIdLabel);
    vehicleFormLayout->addRow("BRAND: ", brandField);
    vehicleFormLayout->addRow("MODEL: ", modelField);
    vehicleFormLayout->addRow("PRICE_PER_DAY: ", pricePerDayField);
    vehicleFormLayout->addRow("IS_RENTED: ", isRentedComboBox);

    vBoxLayout->addWidget(vehicleFormWidget);
    vBoxLayout->addWidget(carDataView);
    vBoxLayout->addWidget(motorcycleDataView);
    vBoxLayout->addWidget(confirmButton);

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
        isRentedComboBox,
        &QComboBox::currentIndexChanged,
        this,
        &views::VehicleDataView::handleChangeIsRentedComboBox
    );

    QObject::connect(
        confirmButton,
        &QPushButton::clicked,
        this,
        &views::VehicleDataView::handleConfirm
    );

};

const std::shared_ptr<const models::VehicleData> views::VehicleDataView::getVehicleData() const {
    if (!vehicleData) {
        return nullptr;
    };
    return vehicleData->clone();
};

void views::VehicleDataView::setVehicleData(
    const std::shared_ptr<const models::VehicleData> vehicleDataP
) {

    this->vehicleData = vehicleDataP->clone();

    switch (vehicleData->vehicleTypeId) {

        case models::VehicleTypeId::car: {
            carDataView->setCarData(
                std::static_pointer_cast<models::CarData>(vehicleData)
            );
            carDataView->show();

            motorcycleDataView->hide();
            motorcycleDataView->setMotorcycleData(nullptr);
            break;
        };

        case models::VehicleTypeId::motorCycle: {
            motorcycleDataView->setMotorcycleData(
                std::static_pointer_cast<models::MotorcycleData>(vehicleData)
            );
            motorcycleDataView->show();

            carDataView->hide();
            carDataView->setCarData(nullptr);
            break;
        };

        default: {
            vehicleData = nullptr;
            carDataView->hide();
            carDataView->setCarData({});
            motorcycleDataView->hide();
            motorcycleDataView->setMotorcycleData({});
            break;
        };

    };

    refreshFields();

};

bool views::VehicleDataView::hasVehicle() const {
    return (vehicleData != nullptr);
};

void views::VehicleDataView::setConfirmButtonText(const QString text) {
    confirmButton->setText(text);
};

void views::VehicleDataView::refreshFields() {;

    vehicleFormWidget->setEnabled(hasVehicle());

    if (!hasVehicle()) {
        vehicleTypeIdLabel->clear();
        vehicleIdLabel->clear();
        brandField->clear();
        modelField->clear();
        pricePerDayField->clear();
        isRentedComboBox->setCurrentIndex(-1);
        return;
    };

    vehicleTypeIdLabel->setText(vehicleData->getVehicleTypeIdAsQString());
    vehicleIdLabel->setText(vehicleData->getVehicleIdAsQString());
    brandField->setText(vehicleData->brand);
    modelField->setText(vehicleData->model);
    pricePerDayField->setText(vehicleData->getPricePerDayAsQString());

    int index = isRentedComboBox->findData(vehicleData->isRented);
    isRentedComboBox->setCurrentIndex(index);

};

void views::VehicleDataView::handleVehicleSelected(
    const std::shared_ptr<const models::VehicleData> vehicleDataP
) {
    qDebug() << "handleVehicleSelected is running with vehicle id: " << vehicleDataP->vehicleId;
    setVehicleData(vehicleDataP);
};

void views::VehicleDataView::handleChangeBrandField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->brand = text;
};

void views::VehicleDataView::handleChangeModelField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->model = text;
};

void views::VehicleDataView::handleChangepPricePerDayField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    bool ok = false;
    const double value = text.toDouble(&ok);
    if (!ok) {
        return;
    };
    vehicleData->pricePerDay = value;
};

void views::VehicleDataView::handleChangeIsRentedComboBox(
    int index
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->isRented = isRentedComboBox->itemData(index).toBool();
};

void views::VehicleDataView::handleConfirm() {

    qDebug() << "handleConfirm is running";

    if (!hasVehicle()) {
        return;
    };

    const std::shared_ptr<const models::VehicleData> vehicleDataImmutable = vehicleData->clone();

    emit confirmVehicle(vehicleDataImmutable);

};
