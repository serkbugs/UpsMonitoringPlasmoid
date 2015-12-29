#!/bin/sh

#cp ./ups-plasma/build/lib/plasma_engine_upsdata.so /usr/lib64/kde4
#cp ./ups-plasma/src/upsdataengine/plasma-engine-upsdata.desktop /usr/share/kde4/services

#copy applet
#cp ./ups-plasma/build/lib/libplasma_applet_ups_monitor.so /usr/lib64/kde4
#cp ./ups-plasma/src/upsplasmoid/plasma-applet-ups-monitor.desktop /usr/share/kde4/services


#data engine 
cp ./ups-plasma/build/lib/plasma_engine_upsdata.so /usr/lib64/qt5/plugins/plasma/dataengine
cp ./ups-plasma/src/upsdataengine/plasma-engine-upsdata.desktop /usr/share/kservices5
