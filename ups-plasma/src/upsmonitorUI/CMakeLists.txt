#find_package(ECM REQUIRED NO_MODULE)
# Needed by find_package(KF5Plasma) below.
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_MODULE_PATH})
# Locate plasma_install_package macro.
#find_package(KF5Plasma REQUIRED)

#add_subdirectory (plasmoid)

#set(upsdata_engine_UI_SRCS
#    ../plasmoid/contents/metadata.desktop
#)
#qt5_add_resources (QRC_SOURCES ${upsdata_engine_UI_SRCS2})
#source_group ("Desktop" FILES ${QRC_SOURCES})

# Add installatation target ("make install").
plasma_install_package(package org.kde.plasma.upsdata)
