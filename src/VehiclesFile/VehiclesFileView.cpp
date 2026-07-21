
#include "VehiclesFile/VehiclesFileView.h"

#include <QWidget>

VehiclesFileView::VehiclesFileView(
    VehiclesFile& vehiclesFileRef,
    QWidget* parent = nullptr
): QWidget(parent), vehiclesFile(vehiclesFileRef) {

};
