
#include "ApplicationContext.h"

#include <QObject>
#include <QWidget>

ApplicationContext::ApplicationContext(
    QWidget* parent
): QObject(parent) {

    bool ok = false;

    vehiclesFile = new VehiclesFile(
        QString("/files/vehiclesQVector.txt"),
        QString("/files/currentVehicleId.txt"),
        ok,
        this
    );

    if (!ok) {

    };

};
