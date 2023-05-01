#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_loggedform.h"
#include <vector>

#include <QFile>
#include "loggedform.h"
#include "loginpage.h"

#include <QDebug>

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loggedInWidget = new loggedForm(this);
    loggedInWidget->hide();

    loginWidget = new loginPage(this);
    loginWidget->show();

    setCentralWidget(loginWidget);
    connect(loginWidget, &loginPage::emitLogin,this,&MainWindow::onEmitLogin);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onEmitLogin(QString str){
    qDebug() << str;
    if(str != "good") return;
    setCentralWidget(loginWidget);
    loginWidget->hide();
    loggedInWidget->show();
}

