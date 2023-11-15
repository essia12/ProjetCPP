#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>

#include"mainwindow.h"


namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void on_pushButton_Login_clicked();

private:
    Ui::Login *ui;
    QMainWindow *mainwindow;

};

#endif // LOGIN_H

