#include "loggedform.h"
#include "ui_loggedform.h"
//why no vector + table widget
#include <QDebug>

loggedForm::loggedForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loggedForm)
{
    ui->setupUi(this);
    ui->friendTable->setColumnCount(1);
    ui->friendTable->setRowCount(5);

    ui->userFind->disconnect();
    connect(ui->findFriendButton,&QPushButton::clicked,[this](){
        emit friendSearch(ui->userFind->text().toStdString());
    });

    connect(ui->friendTable,&QTableWidget::cellClicked,[this](int x,int y){
       qDebug() << "CLICK"<< x << " " << y;
       emit emitUserChange(frenList[x]);
    });

    connect(ui->suggestedFriends,&QTableWidget::cellClicked,[this](int x,int y){
       qDebug() << "CLICK"<< x << " " << y;
       emit emitUserChange(suggestFriends[x]);
    });

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

void loggedForm::populateTable(QTableWidget *t, vector<pair<int, QString> > data){
    t->setColumnCount(1);
    t->setRowCount(data.size());

    for(int i = 0; i < data.size(); i++){
        t->setItem(i,0,new QTableWidgetItem(data[i].second));
    }
}

void loggedForm::updateUser(
        User mainUser,
        User newUser,
       vector<pair<int, QString> > frens,
        QString posts,
        vector<pair<int, QString> > suggest){
    User current_user = newUser;

    if(mainUser.getId() != newUser.getId()){
        ui->header->setText(
            QString::fromStdString(current_user.getFname()+ " "+current_user.getLname()+"'s Profile"
        ));
        int userReturn = mainUser.getId();
        //disconnect(ui->return_button,&QPushButton::clicked,this,nullptr);
        ui->return_button->disconnect();
        connect(ui->return_button,&QPushButton::clicked,[this,userReturn](){
            qDebug() << "RETURN";
            emit emitUserChange(userReturn);
        });
        int addFrenId = newUser.getId();
        //disconnect(ui->addFren,&QPushButton::clicked,this,nullptr);
        ui->addFren->disconnect();
        connect(ui->addFren,&QPushButton::clicked,[this,addFrenId](){
            emit addFriend(addFrenId);
        });
        ui->return_button->show();
        ui->addFren->show();
    } else{
        ui->header->setText(
            QString::fromStdString("Your Profile"));
        ui->return_button->hide();
        ui->addFren->hide();
    }
    ui->name->setText(QString::fromStdString(current_user.getFname()+ " "+current_user.getLname()));
    ui->zip->setText(QString::number(current_user.getZip()));
    ui->id->setText(QString::number(current_user.getId()));
    ui->year->setText(QString::number(current_user.getBday()));
    ui->postBrowser->setText(posts);


    frenList.clear();
    for(auto it: frens) frenList.push_back(it.first);
    suggestFriends.clear();
    for(auto it: suggest) suggestFriends.push_back(it.first);

    populateTable(ui->friendTable,frens);
    populateTable(ui->suggestedFriends,suggest);
}

void loggedForm::updatePath(QString path){
    ui->userPathRet->setText(path);
}
