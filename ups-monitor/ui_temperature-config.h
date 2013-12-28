/********************************************************************************
** Form generated from reading UI file 'temperature-config.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPERATURE_2D_CONFIG_H
#define UI_TEMPERATURE_2D_CONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_config
{
public:
    QVBoxLayout *vboxLayout;
    QLabel *label;
    QTreeView *treeView;
    QHBoxLayout *hboxLayout;
    QLabel *label_2;
    QDoubleSpinBox *intervalSpinBox;
    QSpacerItem *spacerItem;

    void setupUi(QWidget *config)
    {
        if (config->objectName().isEmpty())
            config->setObjectName(QString::fromUtf8("config"));
        config->resize(383, 323);
        config->setStyleSheet(QString::fromUtf8(""));
        vboxLayout = new QVBoxLayout(config);
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        label = new QLabel(config);
        label->setObjectName(QString::fromUtf8("label"));

        vboxLayout->addWidget(label);

        treeView = new QTreeView(config);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setRootIsDecorated(false);
        treeView->setUniformRowHeights(true);
        treeView->setSortingEnabled(true);

        vboxLayout->addWidget(treeView);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        label_2 = new QLabel(config);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        hboxLayout->addWidget(label_2);

        intervalSpinBox = new QDoubleSpinBox(config);
        intervalSpinBox->setObjectName(QString::fromUtf8("intervalSpinBox"));
        intervalSpinBox->setDecimals(1);
        intervalSpinBox->setMinimum(0.1);
        intervalSpinBox->setMaximum(525600);
        intervalSpinBox->setValue(2);

        hboxLayout->addWidget(intervalSpinBox);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);


        vboxLayout->addLayout(hboxLayout);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(treeView);
        label_2->setBuddy(intervalSpinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(config);

        QMetaObject::connectSlotsByName(config);
    } // setupUi

    void retranslateUi(QWidget *config)
    {
        label->setText(QApplication::translate("config", "&Available temperatures:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("config", "Update &interval:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(config);
    } // retranslateUi

};

namespace Ui {
    class config: public Ui_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPERATURE_2D_CONFIG_H
