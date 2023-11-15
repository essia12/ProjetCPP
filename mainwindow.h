#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "contrat.h"
#include <QMainWindow>

#include "login.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_supp_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_chercher_clicked();
    //void on_pushButton_statistique_clicked();
    void on_radioButton_clicked();
    void on_radioButton_2_clicked();
    void on_pushButton_refresh_clicked();
    void on_pushButton_pdf_clicked();

private:
    Ui::MainWindow *ui;
    contrat cl;
};
#endif // MAINWINDOW_H
