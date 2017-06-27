#include "settingswindow.h"
#include "ui_settingswindow.h"

#include <QSettings>
#include "globals.h"

SettingsWindow::SettingsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsWindow)
{
    ui->setupUi(this);

    QSettings settings;
    ui->ipEdit->setText( settings.value("server/ip", Globals::defaultIP).toString() );
    ui->portSpinBox->setValue( settings.value("server/port", Globals::defaultPort).toInt() );
    ui->periodSpinBox->setValue( settings.value("server/updatePeriod", Globals::defaultUpdatePeriod).toInt() / 1000 );
}

SettingsWindow::~SettingsWindow()
{
    delete ui;
}

void SettingsWindow::accept()
{
    QSettings settings;

    settings.setValue("server/ip", ui->ipEdit->text());
    settings.setValue("server/port", ui->portSpinBox->value());
    settings.setValue("server/updatePeriod", ui->periodSpinBox->value() * 1000);

    close();
    emit signalAccept();
}
