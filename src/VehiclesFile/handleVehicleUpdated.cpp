
#include "VehiclesFile/VehiclesFile.h"

void VehiclesFile::handleVehicleUpdated(const QString vehicleId) {
    emit vehicleUpdated(vehicleId);
};
