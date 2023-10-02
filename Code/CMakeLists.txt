cmake_minimum_required(VERSION 3.5)

project(DrStrange VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        databaseController.h
        UserLogIn.h
        UserLoginModel.h
        mainwindow.h
        mainwindow.ui
        PatientsModel.h
        Resources/Resources.qrc
        doctormainwindow.h
        doctormainwindow.cpp
        doctormainwindow.ui
        hospitaladminmain.h
        hospitaladminmain.cpp
        hospitaladminmain.ui
        systemadminmain.h
        systemadminmain.cpp
        systemadminmain.ui
        UserSystemAdminModel.h
        patientupdate.cpp
        patientupdate.h
        patientupdate.ui
        appointments.h
        appointments.cpp
        appointments.ui
        hospitalAdminModel.h
        DoctorModel.h
        CheckValidEmail.h
        CheckValidPassword.h
        CheckValidPhone.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DrStrange
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DrStrange APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DrStrange SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DrStrange
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DrStrange PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Sql)

set_target_properties(DrStrange PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS DrStrange
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DrStrange)
endif()
