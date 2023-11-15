#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include"login.h"
#include<QString>
#include<QObject>
#include <iostream>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QDebug>
#include <QDialog>
#include <QMessageBox>
#include <QIntValidator>
#include<QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>

using namespace std;
contrat::contrat(){
    nc=" ";
    id_c=" ";
    id_v=" ";
    cin=0;
    dep=0;
    ret=0;
}
contrat::contrat(QString nc,QString id_c,QString id_v,int cin,int dep ,int ret){

    this->nc=nc;
    this->id_c=id_c;
    this->id_v=id_v;
    this->cin=cin;
    this->dep=dep;
    this->ret=ret;
}

bool contrat::ajouter(){
    QSqlQuery query;
    QString res =QString::number(cin);
    QString res2 =QString::number(dep);
    QString res3 =QString::number(ret);
    query.prepare("insert into CONTRAT(nc,id_c,id_v,cin,dep,ret)""values(:nc,:id_c,:id_v,:cin,:dep,:ret)");
query.bindValue(":nc",nc);
query.bindValue(":id_c",id_c);
query.bindValue(":id_v",id_v);
query.bindValue(":cin",res);
query.bindValue(":dep",res2);
query.bindValue(":ret",res3);
return query.exec();
}
bool contrat::supprimer(int cin){
QSqlQuery query;
query.prepare("Delete from CONTRAT where cin=:cin ");
query.bindValue(":cin",cin);
return query.exec();
}
QSqlQueryModel *contrat::afficher(){

QSqlQueryModel *model=new QSqlQueryModel();
model->setQuery("select nc,id_c,id_v,cin,dep,ret from CONTRAT");
model->setHeaderData(0,Qt::Horizontal,QObject::tr("nc"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("id_c"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("id_v"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("cin"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("dep"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("ret"));

return model;
}
bool contrat::modifier(QString id_c)
{
    QSqlQuery query;
    query.prepare("UPDATE CONTRAT SET nc=:nc , id_c=:id_c , id_v= :id_v , cin= :cin, dep= :dep, ret=:ret WHERE id_c=:id_c");

    query.bindValue(":nc",nc);
    query.bindValue(":id_c",id_c);
    query.bindValue(":id_v",id_v);
    query.bindValue(":cin",cin);
    query.bindValue(":dep",dep);
    query.bindValue(":ret",ret);

    return query.exec();
}
QSqlQueryModel* contrat::trie(QString croissance, QString critere)
{
    QSqlQueryModel* modal = new QSqlQueryModel();
    QSqlQuery query;

    QString sqlQuery = "SELECT * FROM CONTRAT ORDER BY %1 %2";
    sqlQuery = sqlQuery.arg(critere).arg(croissance);

    query.prepare(sqlQuery);
    if (query.exec()) {
        modal->setQuery(query);
    }

    return modal;
}

QSqlQueryModel* contrat::chercher(const QString& nc, const QString& id_c, const int& cin) {
    QSqlQueryModel *model = new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT * FROM CONTRAT WHERE nc=:nc OR id_c=:id_c OR cin=:cin");
    query.bindValue(":nc",nc);
     query.bindValue(":id_c",id_c);
      query.bindValue(":cin",cin);

    if (query.exec()) {
        model->setQuery(query);
        return model;
    } else {
        delete model; // Clear memory if an error occurs
        return nullptr;
    }
}
bool contrat::idExiste(QString id_c) {
    QSqlQuery query;
    query.prepare("SELECT id_c FROM CONTRAT WHERE id_c = :id");
    query.bindValue(":id_c", id_c);

    if (query.exec() && query.next()) {
        // Si la requête est exécutée avec succès et qu'elle retourne au moins une ligne, l'ID existe
        return true;
    } else {
        // Si la requête échoue ou ne retourne aucune ligne, l'ID n'existe pas
        return false;
    }
}
/*QHash<QString, int> contrat::getstat()
{
    QHash<QString, int> getstat;

    // Récupérez la liste des élèves depuis votre base de données
    // Par exemple, vous pouvez utiliser votre fonction afficher() pour obtenir une liste de tous les clients.
    QSqlQueryModel* model = afficher();

    // Calculez l'âge de chaque élève et mettez à jour la répartition par âge
    QDateTime now = QDateTime::currentDateTime();
    for (int row = 0; row < model->rowCount(); ++row) {
        int fidelite = model->data(model->index(row, 5)).toInt(); // Supposons que la date de naissance est dans la colonne 3

        // Classifiez l'âge dans des groupes
        QString qteGroup;
        if (nb== 9) {
            qteGroup = "silver";
        } else if (nb == 14) {
            qteGroup = "preniuem";
        } else if (nb == 50) {
            qteGroup = "gold";
        } else {
            qteGroup = "VIP";
        }

        // Mettez à jour la répartition par âge
        if (getstat.contains(qteGroup)) {
            getstat[qteGroup]++;
        } else {
            getstat[qteGroup] = 1;
        }
    }
      return getstat;
  }*/

contrat contrat::findBycode(int cin)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM CONTRAT WHERE cin = :cin");
    q.bindValue(":cin", cin);

    if (q.exec() && q.next()) {
         QString nc = q.value("nc").toString();
        QString id_c = q.value("id_c").toString();
        QString id_v= q.value("id_v").toString();
        int cin = q.value("cin").toInt();
        int dep = q.value("dep").toInt();
        int ret = q.value("ret").toInt();
        return contrat(nc,id_c, id_v , cin,dep,ret);
    }

    return contrat();
}
void contrat::imprimer(int cin)
{
    QString id_c;
    int y0 = 2000;
    contrat cl = findBycode(cin);

    QString pdfFileName = QString::number(cl.Getcin()) + "_" + cl.Getnc() + "_" + cl.Getid_c() + ".pdf";

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setFullPage(QPrinter::A4);
    printer.setOutputFileName(pdfFileName);

    QPainter painter(&printer);
    painter.setFont(QFont("Verdana", 30));
    painter.drawText(200, 1000, "Fiche d'un client ");

    painter.setFont(QFont("Verdana", 12));
    y0 += 250;
    painter.drawText(400, y0, "vous etes les bienvenues dans  : ECO_MOVERS");

    y0 += 500;

    QFont titleFont("Verdana", 12, QFont::Bold);
    titleFont.setUnderline(true);
    titleFont.setCapitalization(QFont::AllUppercase);
    painter.setFont(titleFont);

    painter.setPen(QColor(Qt::darkRed)); // Set color to dark blue

    QStringList subtitles = {
        "NC",
        "ID_C",
        "ID_V",
        "CIN",
        "DEP",
        "RET",
    };

    QStringList contents = {
        QString::number(cl.Getcin()),
        cl.Getnc(),
        cl.Getid_c(),
        cl.Getid_v(),
        QString::number(cl.Getdep()),
        QString::number(cl.Getret()),
    };

    for (int i = 0; i < subtitles.size(); ++i)
    {
        painter.drawText(400, y0, subtitles[i] + " :");
        painter.setFont(QFont("Verdana", 12)); // Set content font to normal
        painter.drawText(4000, y0, contents[i]);
        painter.setFont(titleFont); // Reset font to subtitle style
        y0 += 250;
    }

    painter.end();
}
