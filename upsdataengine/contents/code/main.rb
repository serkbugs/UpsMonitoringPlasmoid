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
    end

    #   sources method
    #   Used by applets to request what data source the DataEngine has
    def sources
      sources = %w(ups_info)
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

      if source == 'ups_info'
        @ups.fill_parms()
        setData(source, I18N_NOOP("UPSLoad"), i18n(@ups.upsLoad))
        setData(source, I18N_NOOP("UPSBatteryCharge"), i18n(@ups.batteryCharge))
        setData(source, I18N_NOOP("UPSBatteryVoltage"), i18n(@ups.batteryVoltage))
        setData(source, I18N_NOOP("UPSInputVoltage"), i18n(@ups.inputVoltage))
        setData(source, I18N_NOOP("UPSOutputVoltage"), i18n(@ups.outputVoltage))
      end

      return true
    end
  end
end
