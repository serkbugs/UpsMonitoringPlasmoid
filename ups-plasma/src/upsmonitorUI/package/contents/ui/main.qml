import QtQuick 2.0
import QtQuick.Layouts 1.1
import org.kde.plasma.plasmoid 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import org.kde.kquickcontrolsaddons 2.0 as KQuickAddons

Applet {
    id: root

    onSourceAdded: {
        var match = source.match(/^UPS(\w+)/);
        if (match) {
            root.addSource(source, match[1]);
        }
    }

    delegate: SinglePlotter {
        autoRange: false
        rangeMin: 0
        rangeMax: 100
        function formatLabel(data) {
            return i18n("%1 %2", Math.round(data.value*100)/100, data.units);
        }
    }
}
