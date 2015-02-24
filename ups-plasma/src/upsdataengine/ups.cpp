#include "ups.h"
#include <QtNetwork>
#include <nutclient.h>
#include <QString>

using namespace  nut;
using namespace  std;

Ups::Ups(const QString hostName, const QString upsName, int port)
    :_variablesToCheck(
         QStringList()
            << "ups.status"
            << "battery.charge"
            << "battery.voltage"
            << "input.voltage"
            << "output.voltage"
            << "ups.load"
            << "device.type"
            << "input.frequency"
     )

{
    _hostName = hostName;
    _port = port;
    _upsName = upsName;

    _valuesSetters.insert("ups.status", us);
    _valuesSetters.insert("battery.charge", bt);
    _valuesSetters.insert("battery.voltage", bv);
    _valuesSetters.insert("input.voltage", iv);
    _valuesSetters.insert("output.voltage", ov);
    _valuesSetters.insert("ups.load", ul);
    _valuesSetters.insert("device.type", ut);
    _valuesSetters.insert("input.frequency", ifr);
}

Ups::~Ups()
{

}

void Ups::updateFromService()
{
    try
    {
        TcpClient client(this->_hostName.toUtf8().constData(), this->_port);
        client.connect();
        if(!client.isConnected()){

            qDebug() << QString("Cannot connect to host=%1 and port=%2").arg(this->_hostName, this->_port);
            return;
        }

        Device device = client.getDevice(this->_upsName.toUtf8().constData());
        if(!device){
            qDebug() << QString("Cannot get device with name=\"%1\"").arg(this->_upsName);
            return;
        }

        set<Variable> variables = device.getVariables();
        set<Variable>::iterator vit;
        for(vit=variables.begin(); vit != variables.end(); ++vit){
            Variable variable = *vit;

            if(variable)
            {
                QString varName = QString::fromUtf8(variable.getName().c_str());

                if(_valuesSetters.contains(varName))
                {
                    vector<string> values = variable.getValue();
                    vector<string>::iterator valit;

                    //qDebug() << "----- Parameter values -----";
                    QStringList valuesLst;
                    for(valit = values.begin(); valit != values.end(); ++valit){
                         string value = *valit;
                         valuesLst << QString::fromUtf8(value.c_str());
                         //qDebug() << "value: " << QString::fromUtf8(value.c_str());
                    }

                    QString outValue = valuesLst.join(",");
                    _valuesSetters[varName](outValue);
                }
            }
        }
    }
    catch(...){
        qDebug() << QString("Something is wrong with Nut TcpClient");
    }
}
