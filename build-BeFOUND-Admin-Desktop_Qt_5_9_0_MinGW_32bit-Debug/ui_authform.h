/********************************************************************************
** Form generated from reading UI file 'authform.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTHFORM_H
#define UI_AUTHFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_AuthForm
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *loginEdit;
    QDialogButtonBox *buttonBox;
    QLineEdit *passwordEdit;
    QLabel *label_2;
    QSpacerItem *verticalSpacer;
    QLabel *errorLabel;

    void setupUi(QDialog *AuthForm)
    {
        if (AuthForm->objectName().isEmpty())
            AuthForm->setObjectName(QStringLiteral("AuthForm"));
        AuthForm->resize(325, 155);
        formLayout = new QFormLayout(AuthForm);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label = new QLabel(AuthForm);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        loginEdit = new QLineEdit(AuthForm);
        loginEdit->setObjectName(QStringLiteral("loginEdit"));

        formLayout->setWidget(1, QFormLayout::FieldRole, loginEdit);

        buttonBox = new QDialogButtonBox(AuthForm);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(5, QFormLayout::FieldRole, buttonBox);

        passwordEdit = new QLineEdit(AuthForm);
        passwordEdit->setObjectName(QStringLiteral("passwordEdit"));
        passwordEdit->setEchoMode(QLineEdit::Password);

        formLayout->setWidget(2, QFormLayout::FieldRole, passwordEdit);

        label_2 = new QLabel(AuthForm);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        verticalSpacer = new QSpacerItem(20, 16777215, QSizePolicy::Minimum, QSizePolicy::Expanding);

        formLayout->setItem(4, QFormLayout::FieldRole, verticalSpacer);

        errorLabel = new QLabel(AuthForm);
        errorLabel->setObjectName(QStringLiteral("errorLabel"));
        errorLabel->setEnabled(true);
        errorLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(3, QFormLayout::FieldRole, errorLabel);


        retranslateUi(AuthForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), AuthForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AuthForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(AuthForm);
    } // setupUi

    void retranslateUi(QDialog *AuthForm)
    {
        AuthForm->setWindowTitle(QApplication::translate("AuthForm", "Dialog", Q_NULLPTR));
        label->setText(QApplication::translate("AuthForm", "\320\233\320\276\320\263\320\270\320\275", Q_NULLPTR));
        label_2->setText(QApplication::translate("AuthForm", "\320\237\320\260\321\200\320\276\320\273\321\214", Q_NULLPTR));
        errorLabel->setText(QApplication::translate("AuthForm", "\320\235\320\265\320\277\321\200\320\260\320\262\320\270\320\273\321\214\320\275\321\213\320\271 \320\273\320\276\320\263\320\270\320\275 \320\270\320\273\320\270 \320\277\320\260\321\200\320\276\320\273\321\214", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AuthForm: public Ui_AuthForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTHFORM_H
