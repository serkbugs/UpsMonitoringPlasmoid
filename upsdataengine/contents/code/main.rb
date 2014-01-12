# -*- coding: iso-8859-1 -*-
=begin
/*
 *   Author: serk <serk@none.org>
 *   Date: вт дек 24 2013, 01:22:36
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
=end

# Load QT and KDE Ruby bindings
require 'plasma_applet'
require 'socket'
require 'timeout'

module Upsdataengine
  
  class Ups
    attr_accessor :batteryCharge
    attr_accessor :batteryVoltage
    attr_accessor :upsStatus
    attr_accessor :inputVoltage
    attr_accessor :outputVoltage
    attr_accessor :upsLoad
    attr_accessor :upsType

    def initialize(host="localhost", ups="myups")
      @host = host
      @ups = ups
      self.fill_parms
    end

    def fill_parms()
      begin
        soc = nil
        timeout(30) do
          soc = TCPSocket.new @host,3493
        end
      rescue Errno::ECONNREFUSED
      rescue Errno::EHOSTUNREACH || Errno::ENETUNREACH
      rescue SocketError
      rescue TimeoutError
      else
        soc.write("USERNAME master\r\n");
        soc.readline
        soc.write("PASSWORD 5c581e2fb2\r\n");
        soc.readline
        soc.write("GET VAR #{@ups} ups.status\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.upsStatus = $1

        soc.write("GET VAR #{@ups} battery.charge\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.batteryCharge = $1

        #battery.voltage
        soc.write("GET VAR #{@ups} battery.voltage\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.batteryVoltage = $1

        #input.voltage
        soc.write("GET VAR #{@ups} input.voltage\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.inputVoltage = $1
        #output.voltage
        soc.write("GET VAR #{@ups} output.voltage\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.outputVoltage = $1
        #ups.load
        soc.write("GET VAR #{@ups} ups.load\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.upsLoad = $1
        #ups.type
        soc.write("GET VAR #{@ups} device.type\r\n")
        soc.readline; $_ =~ /.*\s"(.*)"$/;
        self.upsType = $1

        soc.write("LOGOUT\r\n")
        soc.close
      end
    end
  end

# Declare our main class as PlasmaScripting::DataEngine subclass
class Main < PlasmaScripting::DataEngine

    #   Constructor, forward initialization to its superclass
    #   Note: try to NOT modify this constructor; all the setup code
    #   should be placed in the init method.
    def initialize(parent, args = nil)
      super(parent)
    end

    #   Init method
    #   Put here all the code needed to initialize our plasmoid
    def init
      setMinimumPollingInterval(1000)

      begin
        @ups = Ups.new(host='localhost', ups='myups')
      end

      updateStaticData('UPSLoad', '%', 0, 100, 'Ups Load')

      updateStaticData('UPSBatteryCharge', '%', 0, 100, 'Battery Charge')

      updateStaticData('UPSBatteryVoltage','V', 0, 15, 'Battery Voltage')

      updateStaticData('UPSInputVoltage', 'V', 0, 300, 'Ups Input Voltage')

      updateStaticData('UPSOutputVoltage','V', 0, 300, 'Ups Output Voltage')


    end

    #   sources method
    #   Used by applets to request what data source the DataEngine has
    def sources
      sources = %w(UPSLoad UPSBatteryCharge UPSBatteryVoltage UPSInputVoltage UPSOutputVoltage)
      return sources
    end

    #   sourceRequestEvent method
    #   Called when an applet access the DataEngine and request for
    #   a specific source (name)
    def sourceRequestEvent(name)
      return updateSourceEvent(name)
    end

    #   updateSourceEvent method
    #   The main function for a DataEngine
    def updateSourceEvent(source)
      # Add custom code here

      @ups.fill_parms()
      case source
        when 'UPSLoad'
          updateValue(source, @ups.upsLoad)
        when 'UPSBatteryCharge'
          updateValue(source, @ups.batteryCharge)
        when "UPSBatteryVoltage"
          updateValue(source, @ups.batteryVoltage)
        when 'UPSInputVoltage'
          updateValue(source, @ups.inputVoltage)
        when 'UPSOutputVoltage'
          updateValue(source, @ups.outputVoltage)
      end

      return true
    end

    def updateStaticData(source, units, min, max, name)
        setData(source, I18N_NOOP('units'), units)
        setData(source, I18N_NOOP('min'), min)
        setData(source, I18N_NOOP('max'), max)
        setData(source, I18N_NOOP('name'), name)
    end

    def updateValue (source, value)
      setData(source, I18N_NOOP('value'), value)
    end


  end
end
