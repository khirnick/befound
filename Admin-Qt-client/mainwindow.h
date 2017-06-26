#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "usertablemodel.h"
#include "settingswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QTimer *m_timer;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void settingsWindowShow();
    void setSettings();
    void sendRequest();
    void updateUsers(QList<Globals::User> users);

private:
    Ui::MainWindow *ui;

    UserTableModel *m_usersAtTaskModel;
    UserTableModel *m_usersInAlarm;
    SettingsWindow *m_settingsWindow;
};

#endif // MAINWINDOW_H
