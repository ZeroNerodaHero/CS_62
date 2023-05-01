#include "loggedform.h"
#include "ui_loggedform.h"
//why no vector + table widget

loggedForm::loggedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedForm)
{
    ui->setupUi(this);
    ui->friendTable->setColumnCount(1);
    ui->friendTable->setRowCount(5);

    populateTable(ui->friendTable,vector<int>(10,10));
    populateTable(ui->postTable,vector<int>(100,10));
}

loggedForm::~loggedForm()
{
    delete ui;
}

void loggedForm::hide(){
    setVisible(false);
}
void loggedForm::show(){
    setVisible(true);
}

void loggedForm::populateTable(QTableWidget *t, vector<int> data){
    t->setColumnCount(1);
    t->setRowCount(data.size());

    for(int i = 0; i < data.size(); i++){
        t->setItem(i,0,new QTableWidgetItem(QString(data[i])));
    }
}
