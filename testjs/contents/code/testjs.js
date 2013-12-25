// -*- coding: iso-8859-1 -*-
/*
 *   Author: serk <serk@none.org>
 *   Date: ср дек 25 2013, 04:49:46
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
 
// Define our main layout
// Note: plasmoid is the global reference to our widget
mainLayout = new LinearLayout(plasmoid);
mainLayout.orientation = QtVertical
 
// Create and set a simple label; then add it



meter = new Meter()
meter.meterType = Meter.BarMeterHorizontal      
meter.maximum = 100
meter.value = 50
mainLayout.addItem(meter)

signal = new SignalPlotter()
signal.showTopBar = true
signal.showLabels = true
mainLayout.addItem(signal)

label = new Label()
label.text="Test"

