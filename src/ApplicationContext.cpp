
#include "Config.h"

#include "ApplicationContext.h"
#include "VehiclesFile/populateVehiclesFile.h"

#include <QObject>
#include <QWidget>

ApplicationContext::ApplicationContext(
    QWidget* parent
):
    QObject(parent),
    vehiclesFile(
        QString("/files/vehiclesQVector.txt"),
        QString("/files/currentVehicleId.txt"),
        this
    )
{

    #if POPULATE_VEHICLES_FILE
        populateVehicles(vehiclesFile);
    #endif

};

ApplicationContext::~ApplicationContext() {};
