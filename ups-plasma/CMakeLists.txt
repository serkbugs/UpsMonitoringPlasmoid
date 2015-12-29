project(upsdataenginecpp)
#cmake_minimum_required(VERSION 3.0)
cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
SET( CMAKE_AUTOMOC ON )

find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR})
#SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Test" )

find_package(KF5 REQUIRED COMPONENTS
    Plasma
    JsEmbed
    Crash
    I18n
    CoreAddons
#    DocTools
#    Runner
#    NotifyConfig
#    Su
#    NewStuff
#    Wallet
#    KCMUtils
#    IdleTime
#    Declarative
#    TextWidgets
#    KDELibs4Support
#    GlobalAccel
#    DBusAddons
)
#find_package(KF5NetworkManagerQt)
#set_package_properties(KF5NetworkManagerQt PROPERTIES DESCRIPTION "Qt wrapper for NetworkManager API"
#                       TYPE OPTIONAL
#                       PURPOSE "Needed by geolocation data engine."
#                      )
#find_package(KF5XmlRpcClient REQUIRED)

# WARNING PlasmaQuick provides unversioned CMake config
#find_package(KF5 REQUIRED COMPONENTS PlasmaQuick)
#find_package(KF5 REQUIRED COMPONENTS SysGuard)
#find_package(KF5 REQUIRED COMPONENTS Package)
#find_package(KF5 5.1 REQUIRED COMPONENTS Baloo)
#find_package(KF5TextEditor)
#find_package(KWinDBusInterface CONFIG REQUIRED)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
#include(ECMPackageConfigHelpers)
include(ECMMarkNonGuiExecutable)
include(CMakePackageConfigHelpers)
include(WriteBasicConfigVersionFile)
include(CheckIncludeFiles)
include(FeatureSummary)
include(ECMOptionalAddSubdirectory)
include(ECMQtDeclareLoggingCategory)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
#    Quick
    QuickWidgets
    Concurrent
    Test
    Script
    Network
    Xml
)


set(QT_QTTEST_LIBRARY ${Qt5Test_LIBRARIES})

set(QT_LIBRARIES
    ${Qt5Core_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Xml_LIBRARIES}
    ${Qt5Network_LIBRARIES}
#    ${QTPRINT_LIBRARIES}
#    ${QTDBUS_LIBRARIES}
    ${QT_PLATFORM_SPECIFIC_LIBRARIES}
)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Xml_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS}
)


enable_testing ()
add_subdirectory (src)
add_subdirectory (test)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
