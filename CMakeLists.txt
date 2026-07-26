
cmake_minimum_required(VERSION 3.16...3.27)

project(VehicleRentalSystem)

option(POPULATE_VEHICLES_FILE "Populate vehicles with mock data" ON)

configure_file(
    Config.h.in
    ${CMAKE_CURRENT_BINARY_DIR}/Config.h
)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_STANDARD 17)

set(HEADERS

    inc/dialogues/AddCarDialogue.h
    inc/dialogues/AddMotorcycleDialogue.h
    inc/dialogues/dialogues.h

    inc/helpers/ensurePathAndFileExist.h
    inc/helpers/helpers.h
    inc/helpers/populateVehicleRepository.h

    inc/models/Car.h
    inc/models/models.h
    inc/models/Motorcycle.h
    inc/models/Vehicle.h
    inc/models/VehicleRepository.h
    inc/models/Vehicles.h
    inc/models/VehiclesPersistence.h

    inc/views/CarView.h
    inc/views/MotorcycleView.h
    inc/views/VehiclesRepositoryView.h
    inc/views/VehicleView.h
    inc/views/views.h

    inc/MainWindow.h

)

set(SOURCES

    src/dialogues/AddCarDialogue.cpp
    src/dialogues/AddMotorcycleDialogue.cpp

    src/helpers/ensurePathAndFileExist.cpp
    src/helpers/populateVehicleRepository.cpp

    src/models/Car.cpp
    src/models/Motorcycle.cpp
    src/models/Vehicle.cpp
    src/models/VehicleIdGenerator.cpp
    src/models/VehicleRepository.cpp
    src/models/VehiclesPersistence.cpp

    src/views/CarView.cpp
    src/views/MotorcycleView.cpp
    src/views/VehiclesRepositoryView.cpp
    src/views/VehicleView.cpp

    src/MainWindow.cpp

)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

add_executable(VehicleRentalSystem)

target_include_directories(VehicleRentalSystem PRIVATE
    inc
    ${CMAKE_CURRENT_BINARY_DIR}
)

target_sources(VehicleRentalSystem PRIVATE
    main.cpp
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(VehicleRentalSystem PRIVATE Qt6::Widgets)
