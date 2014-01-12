project(plasma_applet_sm_temperature)

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
set (CMAKE_AUTOMOC ON)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR} )

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})

# lib

#set(lib_SRCS
#    monitoricon.cpp
#    applet.cpp
#    plotter.cpp
#)


#add_library(plasma_applet-system-monitor SHARED ${lib_SRCS})
#target_link_libraries(plasma_applet-system-monitor ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
#set_target_properties(plasma_applet-system-monitor PROPERTIES VERSION ${GENERIC_LIB_VERSION} SOVERSION ${GENERIC_LIB_SOVERSION} )


# UPS Monitor

set(ups_SRCS
    applet.cpp
    plotter.cpp
    ups.cpp
)


kde4_add_ui_files(ups_SRCS ups-config.ui)
add_library(plasma_applet_ups_monitor MODULE ${ups_SRCS})
target_link_libraries(plasma_applet_ups_monitor ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS} ${KDE4_KUNITCONVERSION_LIBS})

# Install
#install(TARGETS
#    plasma_applet-system-monitor
#    ${INSTALL_TARGETS_DEFAULT_ARGS})
install(TARGETS
    plasma_applet_ups_monitor
    DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES
    plasma_applet_ups_monitor.desktop
    DESTINATION ${SERVICES_INSTALL_DIR})

