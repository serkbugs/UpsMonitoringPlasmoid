#ifndef UPSTESTS_H
#define UPSTESTS_H

#include <QObject>

class UpsTests : public QObject
{
    Q_OBJECT
public:
    explicit UpsTests(QObject *parent = 0);

    QString testStr() const;
    void setTestStr(const QString &testStr);

private:
    QString _testStr;

private slots:
    //    void initTestCase ();
    void testUpsObjectCreation();
//    void cleanupTestCase();
};

#endif // UPSTESTS_H
