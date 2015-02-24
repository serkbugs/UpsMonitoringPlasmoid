#include "UpsTests.h"
#include <QtTest/QtTest>
#include <QtNetwork>
#include <nutclient.h>
#include <functional>

using namespace nut;
using namespace std;
typedef void (*Function)(const QString);
//typedef f (std::function<void(const QString)>>);

UpsTests::UpsTests(QObject *parent)
    : QObject(parent)
{

}
QString UpsTests::testStr() const
{
    return _testStr;
}

void UpsTests::setTestStr(const QString &testStr)
{
    _testStr = testStr;
}



void UpsTests::testUpsObjectCreation()
{
    std::function<void(const QString)> f0 = [this](const QString x){this->_testStr = x;};
    //QMap<QString,std::function<void(const QString)>> map;
    QMap<QString,decltype(f0)> map;


    map.insert(QString("0"), f0);

    qDebug() << "_testStr before: " << _testStr;
    map.value("0")(QString("2"));
    qDebug() << "_testStr after: " << _testStr;


            QCOMPARE(1,1);
    const int Timeout = 5 * 1000;

    QTcpSocket socket;
    socket.connectToHost("localhost", 3493);
    if (!socket.waitForConnected(Timeout)) {
        //emit error(socket.error(), socket.errorString());
        return;
    }



    QByteArray data;
    QString value;

    bool written;
    qint64 state = socket.write(QString("USERNAME %1\r\n").arg("master").toLatin1());
    socket.flush();

    written = socket.waitForReadyRead(Timeout);
    qDebug() << "read username: " << written;
    qDebug() << "state: " << state;
    qDebug() << "bytesAvailable: " << socket.bytesAvailable();

    QByteArray  recvBuffer;
    qint64 dataAvailable=socket.bytesAvailable();
    qint64 lengthInputData;

    if (recvBuffer.size() < (dataAvailable+1) )
        recvBuffer.resize(dataAvailable+1);

    if ((lengthInputData = socket.read(recvBuffer.data(),dataAvailable)) == -1)
    {
        qDebug() << "Error reading data";
    }

    recvBuffer[(int)lengthInputData]='\0';

    qDebug() << "data" << recvBuffer;
    //socket.readLine();

    socket.write(QString("PASSWORD %1\r\n").arg("5c581e2fb2").toLatin1());
    socket.flush();
    written = socket.waitForReadyRead(Timeout);
    qDebug() << "read PASSWORD: " << written;
    qDebug() << QString("PASSWORD %1\r\n").arg("5c581e2fb2");
    socket.readLine();


    socket.write(QString("GET VAR %1 ups.status\r\n").arg("myups").toLatin1());
    socket.flush();
    data = socket.readLine();
    value = QString(data);

    qDebug()<< "Returned: " << data;
    qDebug() <<QString("GET VAR #{%1} ups.status\r\n").arg("myups");
    qDebug() << "Is open: " << socket.isOpen();
    qDebug() << "Bytes available: " << socket.bytesAvailable();


    TcpClient client("localhost");
    client.connect();
    set<std::string> devices = client.getDeviceNames();
    set<string>::iterator it;

    for(it=devices.begin();it != devices.end(); ++it ){
        string name = *it;
        qDebug() << "Name :" << QString::fromUtf8(name.c_str());
    }


    Device device = client.getDevice("myups");

    set<Variable> variables = device.getVariables();
    set<Variable>::iterator vit;

    for(vit=variables.begin(); vit != variables.end(); ++vit){
        Variable variable = *vit;
        qDebug() << "*****************************";
        qDebug() << "Parameter name:" << QString::fromUtf8(variable.getName().c_str());


       vector<string> values = variable.getValue();
       vector<string>::iterator valit;       
       qDebug() << "----- Parameter values -----";
       for(valit = values.begin(); valit != values.end(); ++valit){
            string value = *valit;
            qDebug() << "value: " << QString::fromUtf8(value.c_str());
       }

    }
}


QTEST_MAIN(UpsTests)
#include "moc_UpsTests.cpp"
