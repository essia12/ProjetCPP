#include "login.h"
#include "ui_login.h"
#include<QMessageBox>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);


}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_Login_clicked()
{
QString username = ui->lineEdit_username->text();
QString password = ui->lineEdit_password->text();

if(username == "esya" && password == "esya") {
QMessageBox::information(this,"Login","Username and passord is correct");
hide();
mainwindow = new MainWindow(this);
mainwindow->show();
}
else {
QMessageBox::warning(this,"Login","Username and password is not correct");
}
}
