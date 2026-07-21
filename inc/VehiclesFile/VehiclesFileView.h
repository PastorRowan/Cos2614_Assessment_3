
#pragma once

#include "VehiclesFile/VehiclesFile.h"

#include <QWidget>
#include <QTableWidget>

class VehiclesFileView : public QWidget {

    private:

        VehiclesFile& vehiclesFile;
        QTableWidget* table;

    public:

        explicit VehiclesFileView(
            VehiclesFile& vehiclesFileRef,
            QWidget* parent = nullptr
        );

        ~VehiclesFileView();

        void destroyTable();

        void refresh();

};
