#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "usertablemodel.h"
#include "settingswindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void settingsWindowShow();

private:
    Ui::MainWindow *ui;

    UserTableModel *m_usersAtTaskModel;
    UserTableModel *m_usersInAlarm;
    SettingsWindow *m_settingsWindow;
};

#endif // MAINWINDOW_H
