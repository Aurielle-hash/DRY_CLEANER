#ifndef CLIENT_H
#define CLIENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QDebug>
#include <QObject>
#include <QMessageBox>


class client
{
private:
    int id_clt;
    int id;
    QString nom;
    QString prenom;
    QString adresse;
    QString mail;
    int numtel;
    float acompte;
    float remise;

public:
    client();
    client(int, int, QString, QString, QString, QString, int);

    int getid_clt();
    int getid();
    QString getnom();
    QString getprenom();
    QString getadresse();
    QString getmail();
    int getnumtel();
    float getacompte();
    float getremise();

    void setid_clt(int);
    void setid(int);
    void setnom(QString);
    void setprenom(QString);
    void setadresse(QString);
    void setmail(QString);
    void setnumtel(int);
    void setacompte(float);
    void setremise(float);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(int);
    QSqlQueryModel* afficherValeur(QString);
    QSqlQueryModel* afficherValeurArticle(QString);
    QSqlQueryModel* trierA(QString);
    QSqlQueryModel* trierD(QString);
    QSqlQueryModel* rechercher(QString);
};

#endif // CLIENT_H
