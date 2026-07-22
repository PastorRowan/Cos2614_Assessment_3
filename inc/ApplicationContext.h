
#pragma once

#include <QObject>
class QWidget;

#include "VehiclesFile/VehiclesFile.h"

class ApplicationContext : public QObject {

    Q_OBJECT

    private:

    public:

        VehiclesFile vehiclesFile;

        explicit ApplicationContext(
            QWidget *parent = nullptr
        );

        ~ApplicationContext();

};
