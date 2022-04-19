#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "staff.h"
#include "QMessageBox"
#include <QApplication>
#include <QIntValidator>
#include <QSqlQuery>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPrinter>
#include <QFile>
#include<QFileDialog>
#include <QPrintDialog>
#include<QPdfWriter>
#include <QtPrintSupport/QPrinter>
#include <QTextStream>
#include <iostream>
#include <string>
#include "myserver.h"
#include "Dialog.h"
#include "newStaff.h"
#include<QSqlQuery>
using namespace std;
QString days ="";
bool card ;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->le_id->setValidator( new QIntValidator(0, 999999, this));
    ui->le_salaire->setValidator( new QIntValidator(0, 999999, this));
    ui->le_nbh->setValidator( new QIntValidator(0, 48, this));
 ui->tabstaff->setModel(S.afficher());
 ui->le_id_supp->setValidator( new QIntValidator(0, 999999, this));
 ui->setupUi(this);
 int ret=A.connect_arduino(); // lancer la connexion à arduino
 switch(ret){
 case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
     break;
 case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
    break;
 case(-1):qDebug() << "arduino is not available";
 }
  QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
  //le slot update_label suite à la reception du signal readyRead (reception des données).


}



MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pb_ajouter_clicked()
{

int id_staff=ui->le_id->text().toInt();
QString nom=ui->le_nom->text();
QString prenom=ui->le_prenom->text();
QString email=ui->le_email->text();
int nb_heurs=ui->le_nbh->text().toInt();
int  salaire=ui->le_salaire->text().toInt();
QString fonction=ui->le_fonction->text();

Staff S(nom,prenom,id_staff,nb_heurs,salaire,email,fonction);
bool test=S.ajouter();
if (test )
{QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("ajout effectuer. \n"
                        "click to exit"),QMessageBox::Cancel);
    ui->tabstaff->setModel(S.afficher());

}
else
    QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr ("ajout non effectuer. \n"
                                        "click to exit"),QMessageBox::Cancel);



}

void MainWindow::on_pb_supprimer_clicked()
{

Staff id_staff; id_staff.setid(ui->le_id_supp->text().toInt());
bool test=id_staff.supprimer(id_staff.getid());
if (test )
{QMessageBox::information(nullptr,QObject::tr("OK"),
            QObject::tr("suppresion effectuer. \n"
                        "click to exit"),QMessageBox::Cancel);
    ui->tabstaff->setModel(S.afficher());
}
else
    QMessageBox ::critical(nullptr,QObject::tr("not ok"),
                           QObject::tr ("suppresion non effectuer. \n"
                                        "click to exit"),QMessageBox::Cancel);



}


void MainWindow::on_pb_modifier_clicked()
{
        QString nom= ui->le_nommodif->text();
        QString prenom= ui->le_prenommodif->text();
        int nb_heurs = ui->le_nbhmodif->text().toInt();
        int id_staff = ui->le_idmodif->text().toInt();
        int salaire = ui->le_salairemodif->text().toInt();
        QString email= ui->le_emailmodif->text();
        QString fonction= ui->le_fonctionmodif->text();

      Staff S2(nom,prenom,id_staff,nb_heurs,salaire,email,fonction);
      bool test=S2.modifier(id_staff);
      if(test)
     {

          ui->tabstaff->setModel(S.afficher());
     QMessageBox::information(nullptr, QObject::tr("modifier un staff"),
                       QObject::tr("staff modifié.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

     }
       else
           QMessageBox::critical(nullptr, QObject::tr("modifier un staff"),
                       QObject::tr("Erreur !.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);

     }

void MainWindow::on_tri_2_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by nb_heurs ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tabstaff->setModel(model);

}
void MainWindow::on_tri_clicked()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by salaire ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tabstaff->setModel(model);
}
void MainWindow::on_tri_3_clicked()
{

    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select* from STAFF order by fonction ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id-staff"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("fonction"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("nb_heurs"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("salaire"));


     ui->tabstaff->setModel(model);

}

void MainWindow::on_PDF_clicked()
{
    QSqlDatabase DRY_CLEANER;
                QTableView tablemateriel;
                QSqlQueryModel * Modal=new  QSqlQueryModel();

                QSqlQuery qry;
                 qry.prepare("SELECT * FROM EMPLOIS ");
                 qry.exec();
                 Modal->setQuery(qry);
                 tablemateriel.setModel(Modal);


                 DRY_CLEANER.close();

                 QString strStream;
                 QTextStream out(&strStream);


                 const int rowCount = tablemateriel.model()->rowCount();
                 const int columnCount =  tablemateriel.model()->columnCount();

                 const QString strTitle ="Document";


                 out <<  "<html>\n"
                         "<img src='C:/Users/LENOVO/Documents/login/images/bg.png' height='120' width='120'/>"
                     "<head>\n"
                         "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                     <<  QString("<title>%1</title>\n").arg(strTitle)
                     <<  "</head>\n"
                     "<body bgcolor=#ffffff link=#5000A0>\n"
                    << QString("<h3 style=\" font-size: 50px; font-family: Arial, Helvetica, sans-serif; color: #e80e32; font-weight: lighter; text-align: center;\">%1</h3>\n").arg("Liste des materiels")
                    <<"<br>"

                    <<"<table border=1 cellspacing=0 cellpadding=2 width=\"100%\">\n";
                 out << "<thead><tr bgcolor=#f0f0f0>";
                 for (int column = 0; column < columnCount; column++)
                     if (!tablemateriel.isColumnHidden(column))
                         out << QString("<th>%1</th>").arg(tablemateriel.model()->headerData(column, Qt::Horizontal).toString());
                 out << "</tr></thead>\n";

                 for (int row = 0; row < rowCount; row++) {
                     out << "<tr>";
                     for (int column = 0; column < columnCount; column++) {
                         if (!tablemateriel.isColumnHidden(column)) {
                             QString data = tablemateriel.model()->data(tablemateriel.model()->index(row, column)).toString().simplified();
                             out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                         }
                     }
                     out << "</tr>\n";
                 }
                 out <<  "</table>\n"
                         "<br><br>"
                         <<"<br>"
                         <<"<table border=1 cellspacing=0 cellpadding=2>\n";

                     out << "<thead><tr bgcolor=#f0f0f0>";

                         out <<  "</table>\n"

                     "</body>\n"
                     "</html>\n";

                 QTextDocument *document = new QTextDocument();
                 document->setHtml(strStream);

                 QPrinter printer;
                 QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
                 if (dialog->exec() == QDialog::Accepted) {

                     document->print(&printer);
                 }

                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setPaperSize(QPrinter::A4);
                 printer.setOutputFileName("/tmp/emplois.pdf");
                 printer.setPageMargins(QMarginsF(15, 15, 15, 15));

                 delete document;

}

void MainWindow::tablewidgetdisplay()
{
  QTableWidget * emplois_2 =  new QTableWidget (this);
  emplois_2->setRowCount(2);
  emplois_2->setColumnCount(7);
  this ->setCentralWidget(emplois_2);
}


void MainWindow::on_effectuer_clicked()
{




   QSqlQuery query;
        query.prepare("SELECT * FROM EMPLOIS");
       query.exec();
        int i=0;
    QString s;

        while (query.next())
        {// s=query.value(0).toString();
           // cout<<s.toStdString()<<"freifhreiu";
            ui->emplois_2->setItem(i,0,new QTableWidgetItem(query.value(0).toString()));
            ui->emplois_2->setItem(i,1,new QTableWidgetItem(query.value(1).toString()));
            ui->emplois_2->setItem(i,2,new QTableWidgetItem(query.value(2).toString()));
            ui->emplois_2->setItem(i,3,new QTableWidgetItem(query.value(3).toString()));
            ui->emplois_2->setItem(i,4,new QTableWidgetItem(query.value(4).toString()));
            ui->emplois_2->setItem(i,5,new QTableWidgetItem(query.value(5).toString()));
            ui->emplois_2->setItem(i,6,new QTableWidgetItem(query.value(6).toString()));


            i++;
        }

       /* ui->emplois_2->cellChanged(0,1);

        query.prepare("INSERT INTO emplois (lun) "
                      "VALUES (:lun");
        query.bindValue(":lun", lun);

        QTableWidgetItem *item =ui->emplois_2->currentItem();
        QString lun= item->text();
       query.exec();
         cout<<lun.toStdString();


        QString text = ui->emplois_2->item(0,0)->text();
        cout<<text.toStdString();*/


}



void MainWindow::on_modifier_clicked()
{QSqlQuery query;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<7;j++)
        {
    ui->emplois_2->cellChanged(i,j);
    QString text = ui->emplois_2->item(i,j)->text();
    cout<<text.toStdString();
        }
    }
    QTableWidgetItem *item =ui->emplois_2->currentItem();
    QString lun= item->text();
    query.prepare("update INTO emplois (lun) "
                  "VALUES (:lun)");
    query.bindValue(":lun", lun);

   query.exec();

     cout<<lun.toStdString();

}



void MainWindow::on_start_s_clicked()
{
    myserver server;
    server.startserver();

}


void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

    days=days+date.toString()+"|";
    ui->les_jours->setText(days);


}


void MainWindow::update_label()
{
    data=A.read_from_arduino();
    Dialog *dialog;
    newStaff *newStaff;
    newStaff =new newStaff(this);
    dialog=new Dialog(this);
    query.exec("PRAGMA UID(STAFF)");
    while (query.next()) {
        if (query.next==data);
    }
    if(card==true){
        dialog->show(); // si les données reçues de arduino via la liaison série sont égales à 1
    // alors afficher ON

        ui->presence->setText("employer present");

                                } // si les données reçues de arduino via la liaison série sont égales à 1

        else
        ui->presence->setText("employer absent");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher ON
}
