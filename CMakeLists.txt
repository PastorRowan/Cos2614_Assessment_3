
cmake_minimum_required(VERSION 3.16...3.27)

project(VehicleRentalSystem)

configure_file(
    ${CMAKE_SOURCE_DIR}/Config.h.in
    ${CMAKE_BINARY_DIR}/generated/Config.h
)

option(POPULATE_VEHICLES_FILE "Populate vehicles with mock data" ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS

    inc/VehiclesFile/populateVehiclesFile.h
    inc/VehiclesFile/VehiclesFileView.h
    inc/VehiclesFile/VehiclesFile.h

    inc/dialogues/AddCarDialogue.h
    inc/dialogues/AddMotorcycleDialogue.h
    inc/dialogues/RentVehicleDialogue.h
    inc/dialogues/ReturnVehicleDialogue.h
    inc/dialogues/dialogues.h

    inc/vehicles/Car.h
    inc/vehicles/Motorcycle.h
    inc/vehicles/Vehicle.h
    inc/vehicles/vehicles.h

    inc/ApplicationContext.h

    inc/MainWindow.h

)

set(SOURCES

    src/dialogues/AddCarDialogue.cpp
    src/dialogues/AddMotorcycleDialogue.cpp
    src/dialogues/RentVehicleDialogue.cpp
    src/dialogues/ReturnVehicleDialogue.cpp

    src/vehicles/Car.cpp
    src/vehicles/Motorcycle.cpp
    src/vehicles/Vehicle.cpp

    src/VehiclesFile/populateVehiclesFile.cpp

    src/VehiclesFile/VehiclesFileView.cpp
    src/VehiclesFile/addCar.cpp
    src/VehiclesFile/addMotorcycle.cpp
    src/VehiclesFile/core.cpp
    src/VehiclesFile/fileIO.cpp
    src/VehiclesFile/rentVehicleById.cpp
    src/VehiclesFile/returnVehicleById.cpp
    src/VehiclesFile/searchVehicleById.cpp

    src/ApplicationContext.cpp

    src/MainWindow.cpp

)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(VehicleRentalSystem)

target_include_directories(VehicleRentalSystem PRIVATE
    inc
)

target_sources(VehicleRentalSystem PRIVATE
    main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(VehicleRentalSystem PRIVATE Qt6::Widgets)
