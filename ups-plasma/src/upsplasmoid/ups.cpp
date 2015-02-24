 /*
 *   Copyright (C) 2007 Petri Damsten <damu@iki.fi>
 *   Copyright (C) 2008 Marco Martin <notmart@gmail.com>
 *   Copyright (C) 2010 Michel Lafon-Puyo <michel.lafonpuyo@gmail.com>
 *   Copyright (C) 2011 Elvis Stansvik <elvstone@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License version 2 as
 *   published by the Free Software Foundation
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

#include "ups.h"
#include <Plasma/Meter>
#include <Plasma/Containment>
#include <Plasma/Theme>
#include <KConfigDialog>
#include <KUnitConversion/Converter>
#include <KUnitConversion/Value>
#include <QGraphicsLinearLayout>
#include <QTimer>
#include <cmath>
#include "plotter.h"

using namespace KUnitConversion;



Ups::Ups(QObject *parent, const QVariantList &args)
    : SM::Applet(parent, args)
    , m_tempModel(0)
    //, m_rx(".*ups_info.*", Qt::CaseInsensitive)
{
    setHasConfigurationInterface(true);
    resize(215 + 20 + 23, 109 + 20 + 25);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
//    m_sourceTimer.setSingleShot(true);
//    connect(&m_sourceTimer, SIGNAL(timeout()), this, SLOT(sourcesAdded()));
}

Ups::~Ups()
{
}

void Ups::init()
{
    KGlobal::locale()->insertCatalog("plasma_applet_ups_monitor");
    setEngine(dataEngine(CUpsdataengine));
    setTitle(i18n("Ups"));

    /* At the time this method is running, not all source may be connected. */
    connect(engine(), SIGNAL(sourceAdded(QString)), this, SLOT(sourceChanged(QString)));
    connect(engine(), SIGNAL(sourceRemoved(QString)), this, SLOT(sourceChanged(QString)));

    foreach (const QString& source, engine()->sources()) {
      sourceChanged(source);
    }

    configChanged();
}


void Ups::sourceChanged(const QString& name)
{
    //qDebug() << "######## sourceChanged name: " << name;
    //qDebug() << "###### regexp captures: " << m_regexp.capturedTexts();

    //if (m_rx.indexIn(name) != -1) {
        m_sources.append(name);
    //}
}


void Ups::configChanged()
{
    //qDebug() << "#### configChanged m_hdds:" << m_hdds;

    KConfigGroup cg = config();
    QStringList default_sources = m_sources;

    // default to 2 seconds (2000 ms interval
    setInterval(cg.readEntry("interval", 2.0) * 1000.0);
    setSources(cg.readEntry(CUpsinfo, default_sources));

    connectToEngine();
}


void Ups::createConfigurationInterface(KConfigDialog *parent)
{
    QWidget *widget = new QWidget();
    ui.setupUi(widget);
    m_tempModel.clear();
    m_tempModel.setHorizontalHeaderLabels(QStringList() << i18n("Sensor"));
    QStandardItem *parentItem = m_tempModel.invisibleRootItem();

    foreach (const QString& source, m_sources) {

        QStandardItem *item1 = new QStandardItem(source);
        item1->setEditable(false);
        item1->setCheckable(true);

        // so be sure to use that.
        if (sources().contains(source)) {
            item1->setCheckState(Qt::Checked);
        }

        parentItem->appendRow(QList<QStandardItem *>() << item1);
    }

    ui.treeView->setModel(&m_tempModel);
    ui.treeView->resizeColumnToContents(0);
    ui.intervalSpinBox->setValue(interval() / 1000.0);
    ui.intervalSpinBox->setSuffix(i18nc("second", " s"));
    parent->addPage(widget, i18n("UPS"), "view-statistics");

    connect(parent, SIGNAL(applyClicked()), this, SLOT(configAccepted()));
    connect(parent, SIGNAL(okClicked()), this, SLOT(configAccepted()));
    connect(ui.treeView, SIGNAL(clicked(QModelIndex)), parent, SLOT(settingsModified()));
    connect(ui.intervalSpinBox, SIGNAL(valueChanged(QString)), parent, SLOT(settingsModified()));
}

void Ups::configAccepted()
{
    KConfigGroup cg = config();
    QStandardItem *parentItem = m_tempModel.invisibleRootItem();

    clear();

    for (int i = 0; i < parentItem->rowCount(); ++i) {
        QStandardItem *item = parentItem->child(i, 0);
        if (item) {
            if (item->checkState() == Qt::Checked) {
                appendSource(item->text());
            }
        }
    }
    cg.writeEntry(CUpsinfo, sources());
    uint interval = ui.intervalSpinBox->value();
    cg.writeEntry("interval", interval);

    emit configNeedsSaving();

}

bool Ups::addVisualization(const QString& source)
{
    Plasma::DataEngine *engine = dataEngine(CUpsdataengine);

    if (!engine) {
        return false;
    }

    SM::Plotter *plotter = new SM::Plotter(this);
    plotter->setTitle(source);
    plotter->setAnalog(mode() != SM::Applet::Panel);

    Plasma::DataEngine::Data data = engine->query(source);
    QString unit = data["units"].toString();
    double min = data["min"].toDouble();
    double max = data["max"].toDouble();

    plotter->setMinMax(min, max);
    plotter->setUnit(unit);

    appendVisualization(source, plotter);

    dataUpdated(source, data);
    setPreferredItemHeight(80);
    return true;
}

void Ups::dataUpdated(const QString& source,
                              const Plasma::DataEngine::Data &data)
{
    if (!sources().contains(source)) {
        return;
    }
    SM::Plotter *plotter = qobject_cast<SM::Plotter*>(visualization(source));
    QString temp;
    QString unit = data["units"].toString();
    double doubleValue = data["value"].toDouble();
    Value value = Value(doubleValue, unit);    

    value.round(1);
    if (plotter) {
        plotter->addSample(QList<double>() << value.number());
    }

    temp = value.toSymbolString();

    if (mode() == SM::Applet::Panel) {
        setToolTip(source,
                   QString("<tr><td>%1</td><td>%2</td></tr>").arg(source).arg(temp));
    }
}


K_EXPORT_PLASMA_APPLET(ups_monitor, Ups)

#include "ups.moc"
