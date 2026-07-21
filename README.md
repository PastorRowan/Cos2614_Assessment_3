
# VehicleRentalSystem

> **Important:** For the best viewing experience, it is recommended to read this `README.md` directly on the GitHub repository where all Markdown formatting, screenshots, and rendered content are displayed correctly.

https://github.com/PastorRowan/Cos2614_Assessment_3

A Qt GUI based vehicle rental management system that allows you to enter cars and motorcycles into the system with persistent state.

---

## Features

- Add vehicle (Car or Motorcycle)
- Search vehicle by ID
- Display all vehicles
- Display available vehicles only
- Rent vehicle
- Return vehicle
- Persists application state between program runs

---

## Project Structure

```
project-root/
│
├── build/                     # Build output (ignored)
├── inc/                       # Header files
├── Scripts/                   # Helper scripts (e.g., build automation)
├── src/                       # Source files
|
├── .gitignore                 # Files and folders excluded from version control
├── CMakeLists.txt             # CMake build configuration
├── CMakePresets.json          # Optional CMake configuration presets
├── Cos2614_Assignment_1.pdf   # Assingment pdf
├── LICENSE                    # Project license
├── main.cpp                   # Application entry point
├── README.md                  # Project documentation
└── walkthrough.mp4            # Showcase how to use the app
```

---

## Getting Started

### Requirements

Ensure the following are installed:

- [ ] Qt compatible toolchain with C and C++ compiler (GCC, Clang, MSVC, etc)
- [ ] Qt 6.11.1 for specific toolchain installed
- [ ] CMake (3.16+ recommended)
- [ ] Ninja (Any build executor that CMake supports is fine)

Uncompress the compressed project file

### Modify the CMakePresets.json file to the correct values according to your setup
![Qt Creator File Menu](screenshots/CMakePresetsJsonExample.png)

### Option 1: Using Qt Creator (Recommended)

1. Open Qt Creator
2. Click ```File```
![Qt Creator File Menu](screenshots/Qt_creator_File.png)
3. Click ```Open File or Project```
![Qt Creator Open File or Project Menu](screenshots/Qt_creator_Open_File_Or_Project.png)
4. Open the project's ```CMakeLists.txt``` file in the project root directory
![Qt Creator open project CmakeLists.txt file](screenshots/Qt_creator_open_CMakeLists.png)
5. Click on ```Projects```
![Qt Creator Projects button](screenshots/Qt_creator_Projects.png)
6. In **Build & Run**, click on ```ConsoleCarRental```
![Qt Creator Projects button](screenshots/Qt_creator_Projects_ConsoleCarRental.png)
7. Click on ```Building and Running```
![Qt Creator Building and Running button](screenshots/Qt_creator_Building_and_Running.png)
8. Enable the setting **Default for "Run in terminal"** otherwise console input/output will not work
![Qt Creator Building and Running button](screenshots/Qt_creator_Run_in_terminal_Enabled.png)
9. Navigate back to the project in Qt Creator
![Qt Creator open project](screenshots/Qt_creator_open_project.png)
10. Build the project
![Qt Creator click Build Project](screenshots/Qt_creator_click_Build_Project.png)
11. Run the project
![Qt Creator click Build Project](screenshots/Qt_creator_click_Run.png)
12. The applicaton should now be running in the Qt Creator terminal
![Qt Creator click Run Project](screenshots/Qt_creator_terminal.png)

### Option 2: Build from Terminal (CMake):

1. Traverse to your project root

2. Generate Build Files using this command (remember to fill it in)
```
cmake -S . -B build -G "Build tool name" -DCMAKE_MAKE_PROGRAM="C:\Path\to\build\executor\program.executable_binary" -DCMAKE_C_COMPILER="C:\Path\to\toolchain's\C\compiler.executable_binary" -DCMAKE_CXX_COMPILER="C:\Path\to\toolchain's\C++\compiler.executable_binary" -DCMAKE_PREFIX_PATH="C:\Path\to\Qt\toolChainUsed"
```

For example, with the Windows operating system with mingw64 toolchain installed the build command would be:
```
cmake -S . -B build ^
-G "Ninja" ^
-DCMAKE_MAKE_PROGRAM="C:\ninja\ninja.exe" ^
-DCMAKE_C_COMPILER="C:\msys64\mingw64\bin\gcc.exe" ^
-DCMAKE_CXX_COMPILER="C:\msys64\mingw64\bin\g++.exe" ^
-DCMAKE_PREFIX_PATH="C:\Qt\6.11.1\mingw_64"
```

3. Build the Project
```
cmake --build build
```

4. Traverse to the build directory
```
cd build
```

All the commands together shoud look like this
![Terminal build](screenshots/Terminal_build_directory.png)

5. If on Windows, run ```windeployqt.exe ConsoleCarRental.exe``` to copy the dll files for Qt

For example, on Windows 11 you would run
```
"C:\Qt\6.11.1\mingw_64\bin\windeployqt.exe" ConsoleCarRental.exe
```

![Terminal build](screenshots/Terminal_ran_windeployqt.png)

6. Run the Application
```
ConsoleCarRental.exe
```

The application should now be running in the terminal
![Terminal running app](screenshots/Terminal_running_app.png)

---

## Notes
- Please watch the walkthrough video in the project root dir to see all of the functionality.
- Data is loaded on startup and saved during runtime.
- File paths are relative to the application working directory.
- File paths you use for your setup are dependant on your operating system and where the programs are located so I can only give examples.
- I have only tested the program on Windows 11 64 bit, I do not know whether the application will run on other operating systems.
