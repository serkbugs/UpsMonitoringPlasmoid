cmake_minimum_required(VERSION 3.0)
project(upsdataenginecpp)
SET( CMAKE_AUTOMOC ON )
#SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/Test" )



# try Qt5 first, and prefer that if found
find_package(Qt5Core QUIET)
IF (Qt5Core_FOUND)
#    find_package(Qt5Widgets REQUIRED)
#    find_package(Qt5Xml REQUIRED)
    find_package(Qt5Network REQUIRED)
#    find_package(Qt5Sql REQUIRED)
    find_package(Qt5Test REQUIRED)


    set(QT_QTTEST_LIBRARY ${Qt5Test_LIBRARIES})

    set(QT_LIBRARIES
        ${Qt5Core_LIBRARIES}
#        ${Qt5Widgets_LIBRARIES}
#        ${Qt5Xml_LIBRARIES}
        ${Qt5Network_LIBRARIES}
#        ${Qt5Sql_LIBRARIES}
#        ${QTPRINT_LIBRARIES}
#        ${QTDBUS_LIBRARIES}
#        ${QT_PLATFORM_SPECIFIC_LIBRARIES}
    )

    include_directories(
        ${Qt5Core_INCLUDE_DIRS}
#        ${Qt5Widgets_INCLUDE_DIRS}
#        ${Qt5Xml_INCLUDE_DIRS}
        ${Qt5Network_INCLUDE_DIRS}
#        ${Qt5Sql_INCLUDE_DIRS}
    )

ELSE()
    # No Qt5 found, try Qt4
    find_package(Qt4 COMPONENTS QtMain QtCore QtNetwork REQUIRED)
    INCLUDE( UseQt4 )
    include_directories(${QT_INCLUDES})
    macro(qt_wrap_cpp)
        qt4_wrap_cpp(${ARGN})
    endmacro()
    macro(qt_wrap_ui)
        qt4_wrap_ui(${ARGN})
    endmacro()
    macro(qt_add_resources)
        qt4_add_resources(${ARGN})
    endmacro()
ENDIF()

enable_testing ()
add_subdirectory (src)
add_subdirectory (test)
