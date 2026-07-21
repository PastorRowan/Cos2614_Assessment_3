
#pragma once

#include <QObject>
class QWidget;

#include "VehiclesFile/VehiclesFile.h"

class ApplicationContext : public QObject {

    Q_OBJECT

    private:

        VehiclesFile* vehiclesFile;

    public:

        explicit ApplicationContext(
            QWidget* parent = nullptr
        );

        ~ApplicationContext();

};
