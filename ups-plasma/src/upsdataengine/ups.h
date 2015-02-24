#ifndef UPS_H
#define UPS_H
#include <QString>
#include <QObject>
#include <QStringList>
#include <functional>
#include <QMap>
class Ups : public QObject
{
    Q_OBJECT

public:
    Ups(const QString hostName, const QString upsName, int port);

    ~Ups();
    void updateFromService();

    QString batteryCharge() const { return _batteryCharge; }
    QString batteryVoltage() const { return _batteryVoltage; }
    QString upsStatus() const { return _upsStatus; }
    QString inputVoltage() const { return _inputVoltage; }
    QString outputVoltage() const { return _outputVoltage; }
    QString upsLoad() const { return _upsLoad; }
    QString upsType() const { return _upsType; }
    QString inputFrequency() const { return _inputFrequency; }

private:
    QString _hostName;
    QString _upsName;
    QString _password;
    QString _userName;
    int _port;

    QString _batteryCharge;
    QString _batteryVoltage;
    QString _upsStatus;
    QString _inputVoltage;
    QString _outputVoltage;
    QString _upsLoad;
    QString _upsType;
    QString _inputFrequency;

    QStringList const _variablesToCheck;

    //functions delegates
    std::function<void(const QString)> bt = [this](const QString x){this->_batteryCharge = x;};
    std::function<void(const QString)> bv = [this](const QString x){this->_batteryVoltage= x;};
    std::function<void(const QString)> us = [this](const QString x){this->_upsStatus = x;};
    std::function<void(const QString)> iv = [this](const QString x){this->_inputVoltage = x;};
    std::function<void(const QString)> ov = [this](const QString x){this->_outputVoltage = x;};
    std::function<void(const QString)> ul = [this](const QString x){this->_upsLoad  = x;};
    std::function<void(const QString)> ut = [this](const QString x){this->_upsType  = x;};
    std::function<void(const QString)> ifr = [this](const QString x){this->_inputFrequency  = x;};

    QMap<QString,decltype(bt)> _valuesSetters;
};

#endif // UPS_H
