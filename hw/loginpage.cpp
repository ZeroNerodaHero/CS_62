#include "loginpage.h"
#include "ui_loginpage.h"

loginPage::loginPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginPage)
{
    ui->setupUi(this);

    connect(ui->loginButton,&QPushButton::clicked,[this](){
        ui->errorBox->setText("FAILED TO LOGIN...or smthing else");
        emit emitLogin(QString(ui->loginText->text()));
    });
}

void loginPage::hide(){
    setVisible(false);
}
void loginPage::show(){
    setVisible(true);
}


loginPage::~loginPage()
{
    delete ui;
}
