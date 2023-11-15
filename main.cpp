#include "mainwindow.h"
#include "connection.h"
#include <QApplication>
#include <QMessageBox>
#include "contrat.h"
#include <QDebug>
#include<iostream>
#include "login.h"
using namespace std;

//AAPLICATION DESKTOP POUR GESTION DES CLIENTS
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Login L;
    Connection c;
    contrat cl;
    qDebug();
    bool test=c.createconnect();
    MainWindow w;
    if(test)
    {L.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


    return a.exec();
}
