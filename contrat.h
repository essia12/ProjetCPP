#ifndef contrat_H
#define contrat_H
#include<QString>
#include <QSqlQuery>
#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QSqlError>
#include<QSqlQueryModel>
#include<iostream>
#include <QDate>

using namespace std;
class contrat {
    public:
        contrat();
        contrat(QString,QString,QString,int,int,int);

        //virtual ~contrat();


        QString Getnc() { return nc; }
        void Setnc(QString val) { nc = val; }
        QString Getid_c() { return id_c; }
        void Setid_c(QString val) { id_c = val; }
        QString Getid_v() { return id_v; }
        void Setid_v(QString val) { id_v = val; }
        int Getcin() { return cin; }
        void Setcin(int val) { cin = val; }
        int Getdep() { return dep; }
        void Setdep(int val) { dep =val; }
        int Getret() { return ret; }
        void Setret(int val) { ret = val; }

        QString nc;
        QString id_c;
        QString id_v;
        int dep;
        int ret;
        //crud

        bool ajouter();
        static QSqlQueryModel*afficher();
        static bool supprimer(int);
        bool modifier(QString);
        static QSqlQueryModel* trie(QString croissance, QString critere);
        static QSqlQueryModel* chercher(const QString& nc, const QString& id_c, const int& cin);
        static QHash<QString, int> getstat();
         bool idExiste(QString);
         static void imprimer(int tel);
         static contrat findBycode(int cin);


    protected:

    private:
        int cin;
};

#endif
