#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QDialog>

namespace Ui {
class AuthForm;
}

class AuthForm : public QDialog
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = 0);
    ~AuthForm();

public slots:
    void show();
    void authorisationFail();
    void accept();

private:
    Ui::AuthForm *ui;
};

#endif // AUTHFORM_H
