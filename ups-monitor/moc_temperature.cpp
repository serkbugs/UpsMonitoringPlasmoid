/****************************************************************************
** Meta object code from reading C++ file 'temperature.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "temperature.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'temperature.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Temperature[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      39,   29,   12,   12, 0x0a,
      92,   85,   12,   12, 0x0a,
     137,   12,   12,   12, 0x08,
     159,  154,   12,   12, 0x08,
     180,   12,   12,   12, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Temperature[] = {
    "Temperature\0\0configChanged()\0name,data\0"
    "dataUpdated(QString,Plasma::DataEngine::Data)\0"
    "parent\0createConfigurationInterface(KConfigDialog*)\0"
    "configAccepted()\0name\0sourceAdded(QString)\0"
    "sourcesAdded()\0"
};

void Temperature::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Temperature *_t = static_cast<Temperature *>(_o);
        switch (_id) {
        case 0: _t->configChanged(); break;
        case 1: _t->dataUpdated((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const Plasma::DataEngine::Data(*)>(_a[2]))); break;
        case 2: _t->createConfigurationInterface((*reinterpret_cast< KConfigDialog*(*)>(_a[1]))); break;
        case 3: _t->configAccepted(); break;
        case 4: _t->sourceAdded((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sourcesAdded(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Temperature::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Temperature::staticMetaObject = {
    { &SM::Applet::staticMetaObject, qt_meta_stringdata_Temperature,
      qt_meta_data_Temperature, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Temperature::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Temperature::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Temperature::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Temperature))
        return static_cast<void*>(const_cast< Temperature*>(this));
    typedef SM::Applet QMocSuperClass;
    return QMocSuperClass::qt_metacast(_clname);
}

int Temperature::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    typedef SM::Applet QMocSuperClass;
    _id = QMocSuperClass::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
