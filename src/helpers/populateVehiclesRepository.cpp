
#include "VehiclePersistence/populateVehiclePersistence.h"
#include "VehiclePersistence/VehiclePersistence.h"

#include <QDebug>

void populateVehiclePersistence(VehiclePersistence* VehiclePersistence) {

    try {

        // Clears the internal list and truncates the files
        VehiclePersistence->clear();

        // Cars
        VehiclePersistence->addCar("Toyota", "Corolla", 450.0, 4, 5);
        VehiclePersistence->addCar("Volkswagen", "Golf GTI", 680.0, 4, 5);
        VehiclePersistence->addCar("BMW", "320i", 950.0, 4, 5);
        VehiclePersistence->addCar("Mercedes-Benz", "C200", 1100.0, 4, 5);
        VehiclePersistence->addCar("Audi", "A4", 1000.0, 4, 5);
        VehiclePersistence->addCar("Honda", "Civic", 520.0, 4, 5);
        VehiclePersistence->addCar("Mercedes-Benz", "CLK320", 750.0, 4, 5);
        VehiclePersistence->addCar("Hyundai", "i30", 430.0, 4, 5);
        VehiclePersistence->addCar("Kia", "Sportage", 690.0, 4, 5);
        VehiclePersistence->addCar("Nissan", "Navara", 820.0, 4, 5);

        // Motorcycles
        VehiclePersistence->addMotorcycle("Honda", "CBR500R", 350.0, 500);
        VehiclePersistence->addMotorcycle("Yamaha", "MT-07", 420.0, 689);
        VehiclePersistence->addMotorcycle("Kawasaki", "Ninja 650", 450.0, 649);
        VehiclePersistence->addMotorcycle("Suzuki", "GSX-R750", 550.0, 750);
        VehiclePersistence->addMotorcycle("Ducati", "Monster", 800.0, 937);
        VehiclePersistence->addMotorcycle("BMW", "S1000RR", 1200.0, 999);
        VehiclePersistence->addMotorcycle("KTM", "390 Duke", 320.0, 373);
        VehiclePersistence->addMotorcycle("Triumph", "Street Triple", 700.0, 765);
        VehiclePersistence->addMotorcycle("Harley-Davidson", "Iron 883", 650.0, 883);
        VehiclePersistence->addMotorcycle("Royal Enfield", "Interceptor 650", 380.0, 648);

        // Rent a few vehicles
        VehiclePersistence->rentVehicleById("2");
        VehiclePersistence->rentVehicleById("5");
        VehiclePersistence->rentVehicleById("11");
        VehiclePersistence->rentVehicleById("14");
        VehiclePersistence->rentVehicleById("18");

        qDebug() << "Successfully populated vehicles fille";

    } catch (const std::exception& e) {
        qCritical() << "Failed to populate vehicles file:" << e.what();
    } catch (...) {
        qCritical() << "Failed to populate vehicles file: Unknown exception.";
    };

};
