#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "databasemanager.h"
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gbCreateContact->hide();
    ui->gbUpdateContact->hide();
    ui->gbDeleteContact->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnCreate_clicked()
{
    ui->gbCreateContact->show();
    ui->gbUpdateContact->hide();
    ui->gbDeleteContact->hide();
}


void MainWindow::on_btnUpdate_clicked()
{
    ui->gbCreateContact->hide();
    ui->gbUpdateContact->show();
    ui->gbDeleteContact->hide();
}


void MainWindow::on_btnDelete_clicked()
{
    ui->gbCreateContact->hide();
    ui->gbUpdateContact->hide();
    ui->gbDeleteContact->show();
}


void MainWindow::on_btnSaveContact_clicked()
{



}


void MainWindow::on_btnSaveContactCreate_clicked()
{
    qDebug() << "In Save Record";
    QString Name = ui->txtNameCreate->text();
    QString Contact = ui->txtContactCreate->text();
    QString City = ui->txtCityCreate->text();
    QString Country = ui->txtCountryCreate->text();

    DataBaseManager &db = DataBaseManager::instance();
    db.openDatabase();


    QSqlQuery query;
    query.prepare("insert into contact (Name, Contact, City, Country) values (:Name, :Contact, :City, :Country)");
    query.bindValue(":Name", Name);
    query.bindValue(":Contact", Contact);
    query.bindValue(":City", City);
    query.bindValue(":Country", Country);

    if(!query.exec())
    {
        qDebug() << "Error in executing query.";
        return;
    }

    qDebug() << query.lastQuery();

    ui->lblinfo->setText("Contact added!");
    db.closeDatabase();
}


void MainWindow::on_btnFind_clicked()
{
     qDebug() << "Find records";
    QSqlQuery query;

    DataBaseManager &db = DataBaseManager::instance();
    db.openDatabase();

    if(ui->rdoName->isChecked())
    {
        qDebug() << "Find records by name";
        QString name = ui->txtValue->text();
        QString matchingPattern = "%" + name + "%";
        query.prepare("select * from contact where Name like :matchingPattern");
        query.bindValue(":matchingPattern", matchingPattern);
    }
    else if(ui->rdoContact->isChecked())
    {
        qDebug() << "Find records by contact";
        QString contact = ui->txtValue->text();
        QString matchingPattern = "%" + contact + "%";
        query.prepare("select * from contact where Contact like :matchingPattern");
        query.bindValue(":matchingPattern", matchingPattern);
    }
    else if(ui->rdoCity->isChecked())
    {
         qDebug() << "Find records by city";
        QString city = ui->txtValue->text();
        QString matchingPattern = "%" + city + "%";
        query.prepare("select * from contact where City like :matchingPattern");
        query.bindValue(":matchingPattern", matchingPattern);
    }
    else
    {
        qDebug() << "Find records by name";
        QString name = ui->txtValue->text();
        QString matchingPattern = "%" + name + "%";
        query.prepare("select * from contact where Name like :matchingPattern");
        query.bindValue(":matchingPattern", matchingPattern);
    }


    if(!query.exec())
    {
        qDebug() << "Error in executing query...";
        return;
    }

    qDebug() << "query is : " << query.lastQuery();

    ui->tblWidgetRecords->clearContents();
    ui->tblWidgetRecords->setRowCount(0);

    ui->tblWidgetRecords->setColumnCount(4);
    ui->tblWidgetRecords->setRowCount(query.size());
    QStringList header;
    header << "Name" << "Contact" << "City" << "Country";
    ui->tblWidgetRecords->setHorizontalHeaderLabels(header);
    int row = 0;

    while(query.next())
    {
        qDebug() << query.value(0).toString() << " " << query.value(1).toString() << " "<< query.value(2).toString() << " "<<query.value(3).toString();
        ui->tblWidgetRecords->insertRow(row);
        ui->tblWidgetRecords->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        ui->tblWidgetRecords->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        ui->tblWidgetRecords->setItem(row, 2, new QTableWidgetItem(query.value(2).toString()));
        ui->tblWidgetRecords->setItem(row, 3, new QTableWidgetItem(query.value(3).toString()));

        row++;
    }

    db.closeDatabase();

}

