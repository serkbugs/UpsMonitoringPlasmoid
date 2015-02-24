#project(upsdataenginecpp)

# Find the required Libaries
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions -std=c++11")

add_definitions (${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

# We add our source code here
set(upsdata_engine_SRCS
    upsdataengine.cpp
    ups.cpp
)

# Now make sure all files get to the right place
kde4_add_plugin(plasma_engine_upsdata ${upsdata_engine_SRCS})

target_link_libraries(plasma_engine_upsdata
                      ${KDE4_KDECORE_LIBS}
                      ${KDE4_PLASMA_LIBS}
                      ${QT_QTNETWORK_LIBRARY}
                      nutclient
)

install(TARGETS plasma_engine_upsdata
        DESTINATION ${PLUGIN_INSTALL_DIR})

install(FILES plasma-engine-upsdata.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})


ADD_LIBRARY(
    upsdataenginecpp STATIC
    ${upsdata_engine_SRCS}
)
TARGET_LINK_LIBRARIES(upsdataenginecpp)
