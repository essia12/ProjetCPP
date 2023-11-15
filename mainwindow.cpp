#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "contrat.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QIntValidator>
#include<QStandardItemModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMainWindow>
#include "login.h"
#include "ui_login.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    //ui->cin_2->setValidator(new QIntValidator(100, 99999999, this));
    //ui->nc_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input int
    //ui->id_c_2->setValidator(new QRegExpValidator(QRegExp("[a-zA-Z]+"), this)); // only input alphabetic characters
    ui->dep_2->setValidator(new QIntValidator(0, 999999, this)); // only input alphabetic characters
    ui->tableView->setModel(cl.afficher());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked() {
    QString nc = ui->nc_2->text();
    QString id_c = ui->id_c_2->text();
    QString id_v = ui->id_v_2->text();
    int cin = ui->cin_2->text().toInt();
    int dep = ui->dep_2->text().toInt();
    int ret = ui->ret_2->text().toInt();
    contrat cl(nc, id_c, id_v, cin, dep, ret);

    bool test = cl.ajouter();
    if (test) {
        ui->tableView->setModel(cl.afficher());
        QMessageBox::information(this, "OK", "Ajout avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "L'ajout n'a pas pu être effectué.");
    }
}

void MainWindow::on_pushButton_supp_clicked() {
    int cin = ui->cin_2->text().toInt();
    bool test = cl.supprimer(cin);

    if (test) {
        ui->tableView->setModel(cl.afficher());
        QMessageBox::information(this, "OK", "Suppression avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "La suppression n'a pas pu être effectuée.");
    }
}

void MainWindow::on_pushButton_2_clicked() {
    QString nc = ui->nc_2->text();
    QString id_c = ui->id_c_2->text();
    QString id_v = ui->id_v_2->text();
    int cin = ui->cin_2->text().toInt();
    int dep = ui->dep_2->text().toInt();
    int ret = ui->ret_2->text().toInt();

    contrat cl(nc, id_c, id_v, cin, dep,ret);

    bool test = cl.modifier(id_c);
    if (test) {
        ui->tableView->setModel(cl.afficher());
        QMessageBox::information(this, "OK", "Mise à jour avec succès.");
    } else {
        QMessageBox::critical(this, "Erreur", "La mise à jour n'a pas pu être effectuée.");
    }
}


void MainWindow::on_pushButton_chercher_clicked() {
    QString nc = ui->nc_2->text();
    QString id_c = ui->id_c_2->text();
    int cin = ui->cin_2->text().toInt();

    qDebug() << "Recherche avec nc :" << nc << "id_c :" << id_c << "cin :" << cin;

    QSqlQueryModel* searchResults = cl.chercher(nc, id_c, cin);

    if (searchResults) {
        qDebug() << "Résultats de la recherche : " << searchResults->rowCount();
        ui->tableView->setModel(searchResults);
    } else {
        qDebug() << "Aucun résultat trouvé.";
    }
}





/*void MainWindow::on_pushButton_statistique_clicked()
{
    // Créez un modèle de données pour le graphique circulaire
        QtCharts::QPieSeries *series = new QtCharts::QPieSeries();

        // Ajoutez des tranches (slices) pour chaque groupe d'âge
        // Vous devrez obtenir les données de votre base de données ici
        // Par exemple, supposons que vous ayez une fonction "getstat()" qui renvoie un QHash<QString, int>
        QHash<QString, int> Distribution = Client::getstat();

        for (const QString &Group : Distribution.keys()) {
            QtCharts::QPieSlice *slice = series->append(Group, Distribution.value(Group));
            // Vous pouvez personnaliser l'apparence de chaque tranche si vous le souhaitez
        }

        // Créez un graphique circulaire et configurez-le
        QtCharts::QChart *chart = new QtCharts::QChart();
        chart->addSeries(series);
        chart->setTitle("Répartition par Niveau");

        // Créez une vue de graphique pour afficher le graphique circulaire
        QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        // Affichez la vue du graphique dans une nouvelle fenêtre
        QMainWindow *chartWindow = new QMainWindow(this);
        chartWindow->setCentralWidget(chartView);
        chartWindow->resize(800, 600);
        chartWindow->show();
}*/

void MainWindow::on_radioButton_2_clicked()
{
    if(ui->comboBox->currentText() != "Choisir")
        ui->tableView->setModel(contrat::trie("ASC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(contrat::afficher());
}

void MainWindow::on_radioButton_clicked()
{
    if(ui->comboBox->currentText() != "Choisir")
      ui->tableView->setModel(contrat::trie("DESC",ui->comboBox->currentText()));
    else  ui->tableView->setModel(contrat::afficher());
}

void MainWindow::on_pushButton_refresh_clicked()
{
    ui->tableView->setModel(contrat::afficher());

}

void MainWindow::on_pushButton_pdf_clicked()
{
    qDebug() << "Clicked!!" ;
    int cin = ui->cin_2->text().toInt();
    contrat cl = contrat::findBycode(cin);
    if(cl.Getcin() != 0) {
        contrat::imprimer(cin);

        QMessageBox::information(nullptr, QObject::tr("PDF File created"),
                    QObject::tr("PDF File created.\n"
                                "Check your debug directory."), QMessageBox::Cancel);
    }
    else {
        QMessageBox::warning(this, "CLIENT Not Found", "The specified CLIENT was not found in the database.");
    }
}
