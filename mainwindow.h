#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "staff.h"
#include <QMainWindow>
#include <QPrinter>
#include <QtGui>
#include <QDebug>
#include <QSqlDatabase>

namespace Ui {
class MainWindow;
} QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_tri_3_clicked();

    void on_tri_clicked();

    void on_tri_2_clicked();

    void on_PDF_clicked();

   void tablewidgetdisplay();


   void on_effectuer_clicked();

   void on_modifier_clicked();

   //void cellchanged ();

  // void on_mailing_clicked();

   void on_start_s_clicked();

private:
    Ui::MainWindow *ui;
    void readdisplaytable();
     Staff S;
};

#endif // MAINWINDOW_H
