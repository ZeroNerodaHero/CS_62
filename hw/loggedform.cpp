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

    ui->DirectMessageFrenSelect->setVisible(true);
    ui->DirectMessageMessageView->setVisible(false);
    ui->startDM->hide();

    ui->userFind->disconnect();
    connect(ui->findFriendButton,&QPushButton::clicked,[this](){
        emit friendSearch(ui->userFind->text().toStdString());
    });

    connect(ui->friendTable,&QTableWidget::cellClicked,[this](int x,int y){
       emit emitUserChange(frenList[x]);
    });

    connect(ui->suggestedFriends,&QTableWidget::cellClicked,[this](int x,int y){
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
        vector<pair<int, QString> > suggest,
        Network &net){
    User current_user = newUser;
    //maybe do a check? but doesn't matter
    store_mainUser = mainUser;
    displayDMcomponent(net);

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

        ui->userFind->hide();
        ui->findFriendButton->hide();
        ui->userPathRet->hide();
        ui->suggestedFriends->hide();
        ui->label->hide();
        ui->label_2->hide();
        ui->label_3->hide();

        ui->startDM->show();
        int startDMId=current_user.getId();
        qDebug() << "UserOpen" << startDMId;
        disconnect(ui->startDM,&QPushButton::clicked,nullptr,nullptr);
        connect(ui->startDM,&QPushButton::clicked,[this,startDMId,&net]{
            refreshDMComponent(startDMId,net);
            qDebug() << "UserClick" << startDMId;
        });
    } else{
        ui->header->setText(
            QString::fromStdString("Your Profile"));
        ui->return_button->hide();
        ui->addFren->hide();

        ui->userFind->show();
        ui->findFriendButton->show();
        ui->userPathRet->show();
        ui->suggestedFriends->show();

        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();

        ui->startDM->hide();
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

void loggedForm::displayDMcomponent(Network &net){
    store_mainUser = net.get_user(store_mainUser.getId());
    if(currentDMedUser == -1){
        ui->DirectMessageFrenSelect->setVisible(true);
        ui->DirectMessageMessageView->setVisible(false);

        vector<pair<int, QString> > DMdisplay;
        DMuser.clear();
        for(auto it: store_mainUser.getAllRelationDM()){
            qDebug() << "UPDATE RELATION" << it;
            DMuser.push_back(it);
            User frenUser = net.get_user(it);
            DMdisplay.push_back(make_pair(it,QString::fromStdString(frenUser.getFname()+" :: "+
                                                                    net.displayDM(store_mainUser.getFname()+" "+store_mainUser.getLname(),
                                                                                  frenUser.getFname()+" "+frenUser.getLname(),1))));
        }
        populateTable(ui->DirectMessageFrenSelect,DMdisplay);
        ui->DirectMessageFrenSelect->resizeColumnToContents(0);
        for (int row = 0; row < ui->DirectMessageFrenSelect->rowCount(); ++row) {
            ui->DirectMessageFrenSelect->setRowHeight(row, 50);
        }
        connect(ui->DirectMessageFrenSelect,&QTableWidget::cellClicked,[this,&net](int x,int y){
           disconnect(ui->DirectMessageFrenSelect,&QTableWidget::cellClicked,nullptr,nullptr);
           refreshDMComponent(DMuser[x],net);
        });
    } else{
        ui->DirectMessageFrenSelect->setVisible(false);
        ui->DirectMessageMessageView->setVisible(true);

        User frenUser = net.get_user(currentDMedUser);
        ui->DirectMessageMessageView->findChild<QTextBrowser *>("DMtextView")->setText(QString::fromStdString(
                    net.displayDM(store_mainUser.getFname()+" "+store_mainUser.getLname(),
                                  frenUser.getFname()+" "+frenUser.getLname(),currentLoadedDM
        )));

        connect(ui->DirectMessageMessageView->findChild<QPushButton *>("BackButton"),&QPushButton::clicked,[this,&net](){
            disconnect(ui->DirectMessageMessageView->findChild<QPushButton *>("BackButton"),&QPushButton::clicked,nullptr,nullptr);
            currentLoadedDM = 5;
            refreshDMComponent(-1,net);
        });

        connect(ui->DirectMessageMessageView->findChild<QPushButton *>("loadMore"),&QPushButton::clicked,[this,&net](){
            disconnect(ui->DirectMessageMessageView->findChild<QPushButton *>("loadMore"),&QPushButton::clicked,nullptr,nullptr);
            currentLoadedDM += 5;
            refreshDMComponent(currentDMedUser,net);
        });

        connect(ui->DirectMessageMessageView->findChild<QPushButton *>("SendButton"),&QPushButton::clicked,[this,&net](){
            disconnect(ui->DirectMessageMessageView->findChild<QPushButton *>("SendButton"),&QPushButton::clicked,nullptr,nullptr);
            User tmp = net.get_user(currentDMedUser);
            net.addDM(store_mainUser.getFname()+" "+store_mainUser.getLname(),
                      ui->DirectMessageMessageView->findChild<QLineEdit *>("newDMtext")->text().toStdString(),
                      0,tmp.getFname()+" "+tmp.getLname()
                      );
            ui->DirectMessageMessageView->findChild<QLineEdit *>("newDMtext")->setText(QString::fromStdString(""));
            qDebug() << "Send";
            qDebug() << "DEBUG CNT" << ++debugCnt;
            refreshDMComponent(currentDMedUser,net);
        });
    }
}
void loggedForm::refreshDMComponent(int newCur,Network &net){
    currentDMedUser = newCur;
    emit updateNetwork(net);
    displayDMcomponent(net);
}
