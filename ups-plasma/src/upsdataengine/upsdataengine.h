#ifndef UPSDATAENGINE_H
#define UPSDATAENGINE_H
#include <Plasma/DataEngine>
#include <functional>
#include "ups.h"
#include <QString>
#include <string>

class UpsDataEngine : public Plasma::DataEngine        
{


private:
    void updateStaticData(const QString &source,const QString &units, int min, int max, const QString &name);
    void updateValue (const QString &source,QVariant value);

Q_OBJECT
public:
    UpsDataEngine(QObject* parent, const QVariantList& args);
    ~UpsDataEngine();
public:
    QStringList sources() const;

protected:
    bool sourceRequestEvent(const QString &source);
    bool updateSourceEvent(const QString &source);

    //functions delegates
    std::function<QString(const Ups&)> bt = [](const Ups& x)    { return x.batteryCharge(); };
    std::function<QString(const Ups&)> bv = [](const Ups& x)    {return x.batteryVoltage();};
    std::function<QString(const Ups&)> us = [](const Ups& x)    {return x.upsStatus();};
    std::function<QString(const Ups&)> iv = [](const Ups& x)    {return x.inputVoltage();};
    std::function<QString(const Ups&)> ov = [](const Ups& x)    {return x.outputVoltage();};
    std::function<QString(const Ups&)> ul = [](const Ups& x)    {return x.upsLoad();};
    std::function<QString(const Ups&)> ut = [](const Ups& x)    {return x.upsType();};
    std::function<QString(const Ups&)> ifr =[](const Ups& x)    {return x.inputFrequency();};

    QMap<QString,decltype(bt)> _valuesGetters;
};

#endif // UPSDATAENGINE_H
