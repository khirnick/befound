#include "authform.h"
#include "ui_authform.h"

#include <QSettings>
#include "auth.h"

AuthForm::AuthForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);
    QSettings settings;
    ui->loginEdit->setText(settings.value("login").toString());
}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::show()
{
    ui->errorLabel->hide();
    QDialog::show();
}

void AuthForm::authorisationFail()
{
    ui->errorLabel->setText("<font color=\"red\">Неправильный логин или пароль</font>");
    ui->errorLabel->show();
    QDialog::show();
}

void AuthForm::accept()
{
    QSettings settings;
    settings.setValue("login", ui->loginEdit->text());
    Auth &auth = Auth::getInstance();
    auth.auth(ui->loginEdit->text(), ui->passwordEdit->text());
}
