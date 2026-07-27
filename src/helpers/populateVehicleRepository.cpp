
#include "helpers/populateVehicleRepository.h"
#include "models/models.h"

#include <QDebug>

void helpers::populateVehicleRepository(models::VehicleRepository* vehicleRepository) {

    try {

        // Clears the internal list and truncates the files
        vehicleRepository->clear();

        // Cars
        /*
        vehicleRepository->addVehicle(models::CarData("Toyota", "Corolla", 450.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Volkswagen", "Golf GTI", 680.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("BMW", "320i", 950.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Mercedes-Benz", "C200", 1100.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Audi", "A4", 1000.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Honda", "Civic", 520.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Mercedes-Benz", "CLK320", 750.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Hyundai", "i30", 430.0, 4, 5));
        vehicleRepository->addVehicle(models::CarData("Kia", "Sportage", 690.0, 4, 5));
        */
        vehicleRepository->addVehicle(models::CarData("Nissan", "Navara", 820.0, 4, 5));

        // Motorcycles
        /*
        vehicleRepository->addVehicle(models::MotorcycleData("Honda", "CBR500R", 350.0, 500));
        vehicleRepository->addVehicle(models::MotorcycleData("Yamaha", "MT-07", 420.0, 689));
        vehicleRepository->addVehicle(models::MotorcycleData("Kawasaki", "Ninja 650", 450.0, 649));
        vehicleRepository->addVehicle(models::MotorcycleData("Suzuki", "GSX-R750", 550.0, 750));
        vehicleRepository->addVehicle(models::MotorcycleData("Ducati", "Monster", 800.0, 937));
        vehicleRepository->addVehicle(models::MotorcycleData("BMW", "S1000RR", 1200.0, 999));
        vehicleRepository->addVehicle(models::MotorcycleData("KTM", "390 Duke", 320.0, 373));
        vehicleRepository->addVehicle(models::MotorcycleData("Triumph", "Street Triple", 700.0, 765));
        vehicleRepository->addVehicle(models::MotorcycleData("Harley-Davidson", "Iron 883", 650.0, 883));
        */
        vehicleRepository->addVehicle(models::MotorcycleData("Royal Enfield", "Interceptor 650", 380.0, 648));

        // Rent a few vehicles
        vehicleRepository->rentVehicleById(2);
        vehicleRepository->rentVehicleById(5);
        vehicleRepository->rentVehicleById(11);
        vehicleRepository->rentVehicleById(14);
        vehicleRepository->rentVehicleById(18);

        qDebug() << "Successfully populated vehicles fille";

    } catch (const std::exception& e) {
        qCritical() << "Failed to populate vehicles file:" << e.what();
    } catch (...) {
        qCritical() << "Failed to populate vehicles file: Unknown exception.";
    };

};
