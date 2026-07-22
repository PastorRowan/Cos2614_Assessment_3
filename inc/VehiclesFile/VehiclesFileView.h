
#pragma once

#include "VehiclesFile/VehiclesFile.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>

class VehiclesFileView : public QWidget {

    private:

        VehiclesFile& vehiclesFile;
        QHBoxLayout *centralHBox;
        QWidget *content;
        QVBoxLayout *contentVBox;
        QTableWidget *table;

    public:

        explicit VehiclesFileView(
            VehiclesFile& vehiclesFileRef,
            QWidget* parent = nullptr
        );

        ~VehiclesFileView();

        void destroyTable();

        void refreshTable();

};
