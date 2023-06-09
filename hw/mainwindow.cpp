#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_loggedform.h"
#include <vector>

#include <QFile>
#include "loggedform.h"
#include "loginpage.h"
#include "/home/school/Downloads/CS_62/HW1Complete/Network.h"
#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    if(!net.readFriends("/home/school/Downloads/CS_62/HW1Complete/largeTest")){
        qDebug() << "read success";
    } else {
        qDebug() << "read fail";
    }
    if(!net.read_posts("/home/school/Downloads/CS_62/HW1Complete/posts")){
        qDebug() << "read posts ok";
    } else{
        qDebug() << "read posts not ok";
    }

    ui->setupUi(this);

    loggedInWidget = new loggedForm(this);
    loggedInWidget->hide();

    loginWidget = new loginPage(this);
    loginWidget->show();

    setCentralWidget(loginWidget);
    connect(loginWidget, &loginPage::emitLogin,this,&MainWindow::onEmitLogin);
    connect(loggedInWidget,&loggedForm::emitUserChange,this,&MainWindow::onEmitUserClick);
    connect(loggedInWidget,&loggedForm::friendSearch,[this](string name){
        int tmp = net.get_id(name);
        if(tmp == -1) {
            loggedInWidget->friendSearch("ERROR");
        } else {
            vector<int> s = net.shortest_path(loggedUser.getId(),tmp);
            QString ret = "";
            for(auto it: s){
                User tUser = net.get_user(it);
                ret.push_back(QString::fromStdString(tUser.getFname()+" "+tUser.getLname()+"->"));
            }
            loggedInWidget->updatePath(ret);
        }
    });
    connect(loggedInWidget,&loggedForm::addFriend,[this](int id){
        qDebug() << "ADD " <<id;
        User newFren = net.get_user(id);
        net.add_connection(loggedUser.getFname()+" "+loggedUser.getLname(),
            newFren.getFname()+" "+newFren.getLname());
        loggedInWidget->updateUser(
               loggedUser,
               current_user,genFrens(),
               QString::fromStdString(current_user.displayPosts(5)),
               genSuggest(),
               net);
    });
    connect(loggedInWidget,&loggedForm::updateNetwork,this,&MainWindow::onUpdateNetwork);
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onEmitLogin(QString str){
    int tmp = net.get_id(str.toStdString());

    if(tmp != -1){
        current_user = loggedUser = net.get_user(tmp);

        setCentralWidget(loginWidget);
        loginWidget->hide();
        loggedInWidget->show();

        loggedInWidget->updateUser(
               loggedUser,
               current_user,genFrens(),
               QString::fromStdString(current_user.displayPosts(5)),
               genSuggest(),
               net);
    }
}

void MainWindow::onEmitUserClick(int id){
    current_user = net.get_user(id);
    loggedInWidget->updateUser(
           loggedUser,
           current_user,genFrens(),
           QString::fromStdString(current_user.displayPosts(5)),
           genSuggest(),
           net);
}

void MainWindow::onUpdateNetwork(Network &net){
    this->net = net;
}

vector<pair<int,QString> >  MainWindow::genFrens(){
    vector<pair<int,QString> > ret;
qDebug() << (current_user.getConn().size());
    for(auto it: current_user.getConn()){
        User tmp = net.get_user(it);
        ret.push_back(make_pair(tmp.getId(),QString::fromStdString(tmp.getFname()+" "+tmp.getLname())));
    }
    return ret;
}
vector<pair<int,QString> >  MainWindow::genSuggest(){
    vector<pair<int,QString> > ret;
    int score = 0;
    vector<int> sug = net.suggest_friends(loggedUser.getId(),score);
    for(auto it: sug){
        User tmp = net.get_user(it);
        ret.push_back(make_pair(tmp.getId(),QString::fromStdString(tmp.getFname()+" "+tmp.getLname())));
    }
    return ret;
}

