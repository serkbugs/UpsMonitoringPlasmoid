/*
 *   Copyright (C) 2007 Petri Damsten <damu@iki.fi>
 *   Copyright (C) 2010 Michel Lafon-Puyo <michel.lafonpuyo@gmail.com>
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

#ifndef UPS_HEADER
#define UPS_HEADER

#include <applet.h>
#include "ui_ups-config.h"
#include <Plasma/DataEngine>
#include <QStandardItemModel>
#include <QTimer>

class Ups : public SM::Applet
{

#define CUpsdataengine  (QString)"upsdata"
#define CMin (QString)"min"
#define CMax (QString)"max"
#define CValue (QString)"value"
#define CUnits (QString)"units"

#define CUpsinfo (QString)"upsinfo"

    Q_OBJECT
    public:
        Ups(QObject *parent, const QVariantList &args);
        ~Ups();

        virtual void init();

    public Q_SLOTS:
        void configChanged();
        void dataUpdated(const QString &name, const Plasma::DataEngine::Data &data);
        void createConfigurationInterface(KConfigDialog *parent);


    private Q_SLOTS:
        void configAccepted();        
        void sourceChanged(const QString &name);

    private:
        Ui::configUps ui;
        QStandardItemModel m_tempModel;
        QStringList m_sources;
        //QTimer m_sourceTimer;
        //QRegExp m_rx;

        bool addVisualization(const QString& source);
        bool isValidDevice(const QString& uuid, Plasma::DataEngine::Data* data);

};

#endif
