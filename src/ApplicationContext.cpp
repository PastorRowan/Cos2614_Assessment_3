
#include "ApplicationContext.h"

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

};

ApplicationContext::~ApplicationContext() {};
