/********************************************************************************
** Form generated from reading UI file 'settingswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSWINDOW_H
#define UI_SETTINGSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_SettingsWindow
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QSpinBox *periodSpinBox;
    QLabel *label;
    QDialogButtonBox *buttonBox;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QLineEdit *ipEdit;
    QLabel *label_4;
    QSpinBox *portSpinBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SettingsWindow)
    {
        if (SettingsWindow->objectName().isEmpty())
            SettingsWindow->setObjectName(QStringLiteral("SettingsWindow"));
        SettingsWindow->resize(428, 134);
        formLayout = new QFormLayout(SettingsWindow);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_2 = new QLabel(SettingsWindow);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        periodSpinBox = new QSpinBox(SettingsWindow);
        periodSpinBox->setObjectName(QStringLiteral("periodSpinBox"));
        periodSpinBox->setMinimum(1);
        periodSpinBox->setMaximum(1000);

        formLayout->setWidget(2, QFormLayout::FieldRole, periodSpinBox);

        label = new QLabel(SettingsWindow);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        buttonBox = new QDialogButtonBox(SettingsWindow);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::FieldRole, buttonBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_3 = new QLabel(SettingsWindow);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout->addWidget(label_3);

        ipEdit = new QLineEdit(SettingsWindow);
        ipEdit->setObjectName(QStringLiteral("ipEdit"));

        horizontalLayout->addWidget(ipEdit);

        label_4 = new QLabel(SettingsWindow);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        portSpinBox = new QSpinBox(SettingsWindow);
        portSpinBox->setObjectName(QStringLiteral("portSpinBox"));
        portSpinBox->setMaximum(65535);

        horizontalLayout->addWidget(portSpinBox);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 16777215, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(3, QFormLayout::FieldRole, verticalSpacer);


        retranslateUi(SettingsWindow);
        QObject::connect(buttonBox, SIGNAL(accepted()), SettingsWindow, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SettingsWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(SettingsWindow);
    } // setupUi

    void retranslateUi(QDialog *SettingsWindow)
    {
        SettingsWindow->setWindowTitle(QApplication::translate("SettingsWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213", Q_NULLPTR));
        label_2->setText(QApplication::translate("SettingsWindow", "\320\236\320\261\320\275\320\276\320\262\320\273\321\217\321\202\321\214 \321\200\320\260\320\267 \320\262 (\321\201\320\265\320\272.)", Q_NULLPTR));
        label->setText(QApplication::translate("SettingsWindow", "\320\241\320\265\321\200\320\262\320\265\321\200", Q_NULLPTR));
        label_3->setText(QApplication::translate("SettingsWindow", "IP:", Q_NULLPTR));
        label_4->setText(QApplication::translate("SettingsWindow", "\320\237\320\276\321\200\321\202:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SettingsWindow: public Ui_SettingsWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSWINDOW_H
