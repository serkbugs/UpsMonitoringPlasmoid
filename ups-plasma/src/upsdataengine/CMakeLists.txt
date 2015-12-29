#project(upsdataenginecpp)
#find_package(ECM REQUIRED NO_MODULE)
#set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})
#include(KDEInstallDirs)
#include(KDECompilerSettings)
#include(KDECMakeSettings)
#include(FeatureSummary)

## Find the required Libaries
#find_package(Qt5 REQUIRED COMPONENTS Core Widgets Network)
#find_package(KF5 REQUIRED COMPONENTS CoreAddons Plasma)


set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11 -fPIE")

#add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
add_definitions (${QT_DEFINITIONS} ${KF5_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KF5_INCLUDES}
   )

# We add our source code here
set(upsdata_engine_SRCS
    upsdataengine.cpp
    ups.cpp
)

# Now make sure all files get to the right place
#kde4_add_plugin(plasma_engine_upsdata ${upsdata_engine_SRCS})
#add_library(plasma_engine_upsdata)



ADD_LIBRARY(
    plasma_engine_upsdata MODULE
    ${upsdata_engine_SRCS}
)

target_link_libraries(plasma_engine_upsdata
KF5::CoreAddons
KF5::Plasma
KF5::I18n
#KF5::Service
Qt5::Core
Qt5::Widgets
#Qt5::Network
nutclient
)



kcoreaddons_desktop_to_json(plasma_engine_upsdata plasma-engine-upsdata.desktop)

#install(TARGETS plasma_engine_upsdata
#        DESTINATION ${PLUGIN_INSTALL_DIR})

#install(FILES plasma-engine-upsdata.desktop
#        DESTINATION ${SERVICES_INSTALL_DIR})

install(TARGETS plasma_engine_upsdata DESTINATION ${KDE_INSTALL_PLUGINDIR}/plasma/dataengine)
install(FILES plasma-engine-upsdata.desktop DESTINATION ${KDE_INSTALL_KSERVICES5DIR} )


#ADD_LIBRARY(
#    upsdataenginecpp STATIC
#    ${upsdata_engine_SRCS}
#)
#TARGET_LINK_LIBRARIES(upsdataenginecpp)
