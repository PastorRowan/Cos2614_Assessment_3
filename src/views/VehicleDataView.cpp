
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
#include <QLocale>
#include <QDoubleValidator>
#include <limits>

/**
 * Constructs a VehicleDataView widget
 *
 * Initializes the user interface, creates the controls used to edit common
 * vehicle properties, creates the car- and motorcycle-specific subviews, and
 * connects all user interface events to their corresponding slots
 *
 * parent The parent widget
 */
views::VehicleDataView::VehicleDataView(
    QWidget *parent
):
    QWidget(parent) {

    vBoxLayout = new QVBoxLayout(this);

    vehicleFormWidget = new QWidget(this);
    vehicleFormLayout = new QFormLayout(vehicleFormWidget);

    vehicleTypeIdLabel = new QLabel(this);

    vehicleIdLabel = new QLabel(this);

    brandField = new QLineEdit(this);

    modelField = new QLineEdit(this);

    pricePerDayField = new QLineEdit(this);
    auto* pricePerDayFieldValiator =
        new QDoubleValidator(
            0,
            std::numeric_limits<double>::max(),
            2,
            this
        );
    QLocale locale(QLocale::C);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    pricePerDayFieldValiator->setLocale(locale);
    pricePerDayField->setValidator(pricePerDayFieldValiator);

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
    vehicleFormLayout->addRow("PRICE_PER_DAY: R", pricePerDayField);
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

    setVehicleData(nullptr);

};

/**
 * Returns the currently displayed vehicle data
 *
 * A deep copy of the internal vehicle data is returned to prevent external
 * code from modifying the widget's internal state
 *
 * Returns a shared pointer to an immutable copy of the current vehicle data,
 * or nullptr if no vehicle is currently displayed
 */
std::shared_ptr<const models::VehicleData> views::VehicleDataView::getVehicleData() const {
    if (!vehicleData) {
        return nullptr;
    };
    return vehicleData->clone();
};

/**
 * Sets the vehicle displayed by the widget
 *
 * Creates an internal copy of the supplied vehicle data, displays the
 * appropriate vehicle-specific editor based on the vehicle type, and updates
 * all user interface fields
 *
 * If an unsupported vehicle type is supplied, the widget is cleared
 *
 * vehicleDataP - The vehicle data to display
 */
void views::VehicleDataView::setVehicleData(
    std::shared_ptr<const models::VehicleData> vehicleDataP
) {

    if (vehicleDataP == nullptr) {
        vehicleData = nullptr;
        carDataView->hide();
        carDataView->setCarData(nullptr);
        motorcycleDataView->hide();
        motorcycleDataView->setMotorcycleData(nullptr);
        refreshFields();
        return;
    };

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
            carDataView->setCarData(nullptr);
            motorcycleDataView->hide();
            motorcycleDataView->setMotorcycleData(nullptr);
            break;
        };

    };

    refreshFields();

};

/**
 * Determines whether the widget currently contains vehicle data
 *
 * Returns true if a vehicle is loaded; otherwise false
 */
bool views::VehicleDataView::hasVehicle() const {
    return (vehicleData != nullptr);
};

/**
 * Sets the text displayed on the confirm button
 *
 * text - The new button text
 */
void views::VehicleDataView::setConfirmButtonText(const QString text) {
    confirmButton->setText(text);
};

/**
 * Refreshes the displayed user interface fields
 *
 * Synchronizes the user interface with the current vehicle data
 * If no vehicle is loaded, all editable fields are cleared and disabled
 */
void views::VehicleDataView::refreshFields() {

    bool hasVehicleVar = hasVehicle();

    setEnabled(hasVehicleVar);

    if (!hasVehicleVar) {
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

/**
 * Handles vehicle selection events
 *
 * Displays the supplied vehicle within the widget
 *
 * vehicleDataP - The selected vehicle data
 */
void views::VehicleDataView::handleVehicleSelected(
    std::shared_ptr<const models::VehicleData> vehicleDataP
) {
    qDebug() << "handleVehicleSelected is running with vehicle id: " << vehicleDataP->vehicleId;
    setVehicleData(vehicleDataP);
};

/**
 * Handles changes to the brand field
 *
 * Updates the internal vehicle data when the brand text changes
 *
 * text - The new brand
 */
void views::VehicleDataView::handleChangeBrandField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->brand = text;
};

/**
 * Handles changes to the model field
 *
 * Updates the internal vehicle data when the model text changes
 *
 * text - The new model
 */
void views::VehicleDataView::handleChangeModelField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->model = text;
};

/**
 * Handles changes to the rental price field
 *
 * Converts the entered text to a double and updates the internal vehicle data
 * if the conversion succeeds
 *
 * text - The new rental price
 */
void views::VehicleDataView::handleChangepPricePerDayField(
    const QString text
) {
    if (!hasVehicle()) {
        return;
    };
    bool ok = false;
    const double value = pricePerDayField->validator()->locale().toDouble(text, &ok);
    if (!ok) {
        return;
    };
    vehicleData->pricePerDay = value;
};

/**
 * Handles changes to the rental status
 *
 * Updates the rental status using the value associated with the selected
 * combo box item
 *
 * index - The selected combo box index
 */
void views::VehicleDataView::handleChangeIsRentedComboBox(
    int index
) {
    if (!hasVehicle()) {
        return;
    };
    vehicleData->isRented = isRentedComboBox->itemData(index).toBool();
};

/**
 * Handles confirmation of the edited vehicle data
 *
 * Creates an immutable copy of the current vehicle data and emits the
 * confirmVehicle() signal so that the updated data can be processed by other
 * application components
 */
void views::VehicleDataView::handleConfirm() {

    qDebug() << "handleConfirm is running";

    if (!hasVehicle()) {
        return;
    };

    std::shared_ptr<const models::VehicleData> vehicleDataImmutable = vehicleData->clone();

    emit confirmVehicle(vehicleDataImmutable);

};
