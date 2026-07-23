
#include "vehiclesFile/populateVehiclesFile.h"
#include "vehiclesFile/vehiclesFile.h"

#include <QDebug>

void populateVehiclesFile(VehiclesFile& vehiclesFile) {

    try {

        // Clears the internal list and truncates the files
        vehiclesFile.clear();

        // Cars
        vehiclesFile.addCar("Toyota", "Corolla", 450.0, 4, 5);
        vehiclesFile.addCar("Volkswagen", "Golf GTI", 680.0, 4, 5);
        vehiclesFile.addCar("BMW", "320i", 950.0, 4, 5);
        vehiclesFile.addCar("Mercedes-Benz", "C200", 1100.0, 4, 5);
        vehiclesFile.addCar("Audi", "A4", 1000.0, 4, 5);
        vehiclesFile.addCar("Honda", "Civic", 520.0, 4, 5);
        vehiclesFile.addCar("Mercedes-Benz", "CLK320", 750.0, 4, 5);
        vehiclesFile.addCar("Hyundai", "i30", 430.0, 4, 5);
        vehiclesFile.addCar("Kia", "Sportage", 690.0, 4, 5);
        vehiclesFile.addCar("Nissan", "Navara", 820.0, 4, 5);

        // Motorcycles
        vehiclesFile.addMotorcycle("Honda", "CBR500R", 350.0, 500);
        vehiclesFile.addMotorcycle("Yamaha", "MT-07", 420.0, 689);
        vehiclesFile.addMotorcycle("Kawasaki", "Ninja 650", 450.0, 649);
        vehiclesFile.addMotorcycle("Suzuki", "GSX-R750", 550.0, 750);
        vehiclesFile.addMotorcycle("Ducati", "Monster", 800.0, 937);
        vehiclesFile.addMotorcycle("BMW", "S1000RR", 1200.0, 999);
        vehiclesFile.addMotorcycle("KTM", "390 Duke", 320.0, 373);
        vehiclesFile.addMotorcycle("Triumph", "Street Triple", 700.0, 765);
        vehiclesFile.addMotorcycle("Harley-Davidson", "Iron 883", 650.0, 883);
        vehiclesFile.addMotorcycle("Royal Enfield", "Interceptor 650", 380.0, 648);

        // Rent a few vehicles
        vehiclesFile.rentVehicleById("2");
        vehiclesFile.rentVehicleById("5");
        vehiclesFile.rentVehicleById("11");
        vehiclesFile.rentVehicleById("14");
        vehiclesFile.rentVehicleById("18");

        qDebug() << "Successfully populated vehicles fille";

    } catch (const std::exception& e) {
        qCritical() << "Failed to populate vehicles file:" << e.what();
    } catch (...) {
        qCritical() << "Failed to populate vehicles file: Unknown exception.";
    };

};
