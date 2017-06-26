#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class SettingsWindow;
}

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QWidget *parent = 0);
    ~SettingsWindow();

public slots:
    void accept();

signals:
    void signalAccept();

private:
    Ui::SettingsWindow *ui;
};

#endif // DIALOG_H
