
#include "dialogues/DeleteVehicleDialogue.h"

#include <QObject>
#include <memory>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QDebug>

dialogues::DeleteVehicleDialogue::DeleteVehicleDialogue(
    QWidget *parent
):
    QDialog(parent) {

    vBoxLayout = new QVBoxLayout(this);

    title = new QLabel(this);
    title->setText("Do you want to delete Vehicle:");
    title->setAlignment(Qt::AlignCenter);

    vehicleDetailsLabel = new QLabel(this);
    vehicleDetailsLabel->setText("No vehicle chosen");

    warningLabel = new QLabel(this);
    warningLabel->setText("This action cannot be undone.");

    bottomButtonBarWidget = new QWidget(this);

    bottomButtonBarLayout = new QHBoxLayout(bottomButtonBarWidget);

    noButton = new QPushButton(bottomButtonBarWidget);
    noButton->setText("No");

    yesButton = new QPushButton(bottomButtonBarWidget);
    yesButton->setText("Yes");

    bottomButtonBarLayout->addWidget(noButton);
    bottomButtonBarLayout->addWidget(yesButton);

    vBoxLayout->addWidget(title);
    vBoxLayout->addWidget(vehicleDetailsLabel);
    vBoxLayout->addWidget(warningLabel);
    vBoxLayout->addWidget(bottomButtonBarWidget);
    vBoxLayout->addStretch();

    QObject::connect(
        noButton,
        &QPushButton::clicked,
        this,
        &dialogues::DeleteVehicleDialogue::handleDismiss
    );

    QObject::connect(
        yesButton,
        &QPushButton::clicked,
        this,
        &dialogues::DeleteVehicleDialogue::handleDelete
    );

};

void dialogues::DeleteVehicleDialogue::setVehicleData(
    std::shared_ptr<const models::VehicleData> vehicleDataP
) {
    vehicleData = vehicleDataP;
    vehicleDetailsLabel->setText(
        QString(
            "TYPE: %1\n"
            "VEHICLE_ID: %2\n"
            "BRAND: %3\n"
            "MODEL: %4\n"
            "PRICE_PER_DAY: R%5\n"
            "IS_RENTED: %6"
        )
        .arg(models::vehicleTypeIdToPrettyQString(vehicleData->vehicleTypeId))
        .arg(vehicleData->getVehicleIdAsQString())
        .arg(vehicleData->brand)
        .arg(vehicleData->model)
        .arg(vehicleData->getPricePerDayAsQString())
        .arg(vehicleData->getIsRentedAsQString())
    );
};

bool dialogues::DeleteVehicleDialogue::hasVehicle() const {
    return (vehicleData != nullptr);
};

/**
 * Opens the dialog and prevent interaction with the rest of the GUI
 *
 * Displays the dialog and blocks until the user accepts or rejects it
 */
void dialogues::DeleteVehicleDialogue::open() {
    if (!hasVehicle()) {
        qDebug() << "dialogues::DeleteVehicleDialogue::open was called while dialogue had no vehicle";
        return;
    };
    exec();
};

void dialogues::DeleteVehicleDialogue::handleDismiss() {
    reject();
};

void dialogues::DeleteVehicleDialogue::handleDelete() {
    emit deleteVehicle(vehicleData->vehicleId);
    accept();
};
