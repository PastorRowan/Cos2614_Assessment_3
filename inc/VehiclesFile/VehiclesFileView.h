
#pragma once

#include "VehiclesFile/VehiclesFile.h"

#include <QWidget>
#include <QGridLayout>

class VehiclesFileView : public QWidget {

    private:

        VehiclesFile& vehiclesFile;
        QGridLayout* gridLayout;

    public:

        explicit VehiclesFileView(
            VehiclesFile& vehiclesFileRef,
            QWidget* parent = nullptr
        );

};
