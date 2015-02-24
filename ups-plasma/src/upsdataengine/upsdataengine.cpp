#include "upsdataengine.h"
#include <Plasma/DataContainer>
#include "ups.h"

UpsDataEngine::UpsDataEngine(QObject *parent, const QVariantList &args)
    : Plasma::DataEngine(parent, args)
{
    // We ignore any arguments - data engines do not have much use for them
    Q_UNUSED(args)

    setMinimumPollingInterval(1000);

    _valuesGetters.insert("UPSLoad", ul);
    _valuesGetters.insert("UPSBatteryCharge", bt);
    _valuesGetters.insert("UPSBatteryVoltage", bv);
    _valuesGetters.insert("UPSInputVoltage", iv);
    _valuesGetters.insert("UPSOutputVoltage", ov);


    updateStaticData(QString("UPSLoad"),QString("%"), (int)0, (int)100,QString("Ups Load"));
    updateStaticData(QString("UPSBatteryCharge"), QString("%"), 0, 100, QString("Battery Charge"));
    updateStaticData(QString("UPSBatteryVoltage"),QString("V"), 0, 15, QString("Battery Voltage"));
    updateStaticData(QString("UPSInputVoltage"), QString("V"), 0, 300, QString("Ups Input Voltage"));
    updateStaticData(QString("UPSOutputVoltage"),QString("V"), 0, 300, QString("Ups Output Voltage"));
}

UpsDataEngine::~UpsDataEngine()
{

}

QStringList UpsDataEngine::sources() const
{
    QStringList lst = QStringList()
            << QString("UPSLoad")
            << QString("UPSBatteryCharge")
            << QString("UPSBatteryVoltage")
            << QString("UPSInputVoltage")
            << QString("UPSOutputVoltage");
    return lst;
}


void UpsDataEngine::updateStaticData(const QString &source, const QString &units, int min, int max, const QString &name)
{
    setData(source, I18N_NOOP("units"), QVariant(units));
    setData(source, I18N_NOOP("min"), QVariant(min));
    setData(source, I18N_NOOP("max"), QVariant(max));
    setData(source, I18N_NOOP("name"), QVariant(name));
}

void UpsDataEngine::updateValue(const QString &source, QVariant value)
{
    setData(source, I18N_NOOP("value"), value);
}

bool UpsDataEngine::sourceRequestEvent(const QString &name){
    return updateSourceEvent(name);
}


bool UpsDataEngine::updateSourceEvent(const QString &source){
    Ups ups(QString("localhost"), QString("myups"), 3493);
    ups.updateFromService();
    QMap<QString,decltype(bt)>::iterator it;
    for(it=_valuesGetters.begin(); it != _valuesGetters.end(); ++it){
        updateValue(it.key(), QVariant(it.value()(ups)));
    }

    return true;
}


// This does the magic that allows Plasma to load
// this plugin.  The first argument must match
// the X-Plasma-EngineName in the .desktop file.
// The second argument is the name of the class in
// your plugin that derives from Plasma::DataEngine
K_EXPORT_PLASMA_DATAENGINE(upsdata, UpsDataEngine)

// this is needed since UpsDataEngine is a QObject
#include "upsdataengine.moc"
