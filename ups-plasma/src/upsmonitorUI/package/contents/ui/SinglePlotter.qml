/*
 *   Copyright 2015 Marco Martin <mart@kde.org>
 *
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons


KQuickAddons.Plotter {
    id: plotter
    property string sensorName: model.friendlyName

    Layout.fillWidth: true
    Layout.fillHeight: true
    //FIXME: doesn't seem to properly fill otherwise
    Layout.preferredHeight: parent.height
    horizontalGridLineCount: 0

    function formatLabel(data) {
        return i18n("%1 %2", data.value, data.units);
    }

    dataSets: [
        KQuickAddons.PlotData {
            color: theme.highlightColor
        }
    ]

    PlasmaComponents.Label {
        anchors {
            left: parent.left
            top: parent.top
        }
        text: plotter.sensorName
    }

    PlasmaComponents.Label {
        id: speedLabel
        anchors.fill: parent
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    Connections {
        target: model.dataSource
        onNewData: {
            if (sourceName.indexOf(decodeURIComponent(model.source)) != 0) {
                return;
            }

            var data = model.dataSource.data[decodeURIComponent(model.source)];

            if (data === undefined || data.value === undefined) {
                return;
            }

            plotter.addSample([data.value]);

            var min = data.min;
            var max = data.max;
            //print(min);
            //print(max);
            if(min !== undefined){
                plotter.rangeMin = min;
            }

            if(max !== undefined){
                plotter.rangeMax = max;
            }

            speedLabel.text = formatLabel(data);
        }
    }
}

